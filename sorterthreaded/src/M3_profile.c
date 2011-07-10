#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include "M3_profile.h"
#ifdef USE_MPI
#include "mpi.h"
#endif




#ifdef USE_MPI 
#include "mpi.h"
#endif

#ifdef USE_PAPI
#include "papi.h"
#endif

#define M3_PROFILE_INIT 0
#define M3_PROFILE_FINALIZE 1
#define M3_PROFILE_START 2
#define M3_PROFILE_STOP 3


void M3_profile( int sectionID, const char *sectionName, int operationFlag );


void M3_ProfileInit( const char *titleString )
{
#pragma omp master
{
  static int firstCall = 1;
  if( firstCall )
  {
    M3_profile( 0, titleString, M3_PROFILE_INIT );
    firstCall = 0;
  }
}
}

void M3_ProfileFinalize( void )
{
#pragma omp master
{
  static int firstCall = 1;
  if( firstCall )
  {
    M3_profile( 0, NULL, M3_PROFILE_FINALIZE );
    firstCall = 0;
  }
}
}

void M3_ProfileStart( int sectionID, const char *sectionName )
{
#pragma omp master
{
  M3_profile( sectionID, sectionName, M3_PROFILE_START );
}
}

void M3_ProfileStop( int sectionID )
{
#pragma omp master
{
  M3_profile( sectionID, NULL, M3_PROFILE_STOP );
}
}

void M3_profile( int sectionID, const char *sectionName, int operationFlag )
{
  static char *staticTitleString = NULL;
  static char **staticProfileName = NULL;
  static int64_t *staticNumCalls = NULL;
  static double *staticTotalTime = NULL;
  static double *staticStartTime = NULL;
#ifdef USE_PAPI
  static int64_t *staticFlopCount = NULL;
  static int64_t *staticFlipCount = NULL;
  static int64_t *staticFlopCounter = NULL;
  static int64_t *staticFlipCounter = NULL;
#endif
  static double staticInitTime = 0;
  static char staticInitDate[256]={0};
  static int staticProfileLevel = -1;

#ifdef USE_PAPI
#define M3_NUM_PAPI_EVENTS 2
  int papiEvents[M3_NUM_PAPI_EVENTS] = {PAPI_FP_OPS, PAPI_FP_INS};
  static long long int papiCounters[M3_NUM_PAPI_EVENTS] = {0};
#endif
  double finalTime;
  int64_t *agInt64 = NULL;
  double *agDouble = NULL;
  int64_t i, j;
  long int k;
  int myRank = -1;
  int numProc = 1;
  FILE *outFile;  
  char *tempPtr, fileName[256], tempString[256];
  char myHostname[256] = {0};
  double mpiTic;
  double mpiToc;
  struct timeval tic;
  struct timezone tz;
  time_t tt;
  long int pid;
  char pcontrolID[16] = {0};

  if( staticProfileLevel == -1 )
  {
    /* Look for environment variable.  */
    tempPtr = getenv("M3_PROFILE_LEVEL");
    if( tempPtr )
      staticProfileLevel = atoi( tempPtr );
    else
      staticProfileLevel = M3_PROFILE_LEVEL;
  }

  if( staticProfileLevel == 0 )
    return;



#ifdef USE_MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank );
  MPI_Comm_size(MPI_COMM_WORLD, &numProc );
#endif 

  sprintf(fileName, "M3_Profile():  profile ID out of range, must be between 0 and %i", M3_PROFILE_MAX_SECTIONS - 1);
  assert(sectionID >= 0 && sectionID < M3_PROFILE_MAX_SECTIONS);

  switch( operationFlag )
  {
    case M3_PROFILE_INIT:
      assert(staticProfileName == NULL &&
	     staticNumCalls == NULL && 
	     staticTotalTime == NULL && 
	     staticStartTime == NULL);
      if( sectionName && strlen(sectionName) )
      {
        staticTitleString = (char *)calloc( 4*(strlen(sectionName)/4 +1 ), sizeof(char) );
        assert(staticTitleString != NULL);
        strcpy(staticTitleString, sectionName );
      }

      staticProfileName = (char **)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(char*) );
      staticNumCalls = (int64_t *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(int64_t) );
      staticTotalTime = (double *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(double) );
      staticStartTime = (double *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(double) );
      assert(staticProfileName && staticNumCalls && staticTotalTime && staticStartTime);
#ifdef USE_PAPI
      staticFlopCount = (int64_t *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(int64_t));
      staticFlipCount = (int64_t *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(int64_t));
      staticFlopCounter = (int64_t *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(int64_t));
      staticFlipCounter = (int64_t *)calloc( M3_PROFILE_MAX_SECTIONS, sizeof(int64_t));
      assert(staticFlopCount && staticFlipCount);
      assert(staticFlopCounter && staticFlipCounter);
#endif

      gettimeofday(&tic, &tz);
#ifdef USE_MPI
      staticInitTime = MPI_Wtime( );
#else
      staticInitTime = tic.tv_sec + tic.tv_usec*1e-6;
#endif
      tt = tic.tv_sec;
      ctime_r(&tt, staticInitDate );

#ifdef USE_PAPI      
      PAPI_start_counters(papiEvents, M3_NUM_PAPI_EVENTS);
#endif

#ifdef USE_MPI
      if (myRank == 0) {
	mkdir( "m3_profile", S_IRWXU );
      }
#else
      mkdir( "m3_profile", S_IRWXU );
#endif

      break;
    case M3_PROFILE_FINALIZE:
      /* Check to see if it was initialized */
      if( staticProfileName == NULL ||
          staticNumCalls == NULL || 
          staticTotalTime == NULL )
      {
	/*        fprintf(stderr, "WARNING:  M3_Profile, finalized without initializing\n");  */
        break;
      }

      myHostname[255] = 0;
      gethostname(myHostname, 255);
      pid = (long int)getpid();  

      for( j = 0; j < 2; j++ )
      {
#ifdef USE_MPI
        if( j == 1 )
	{
          /* Get aggregate statistics */
          if( myRank == 0 )
	  {
            agInt64 = (int64_t*)calloc(M3_PROFILE_MAX_SECTIONS, sizeof(int64_t));
            agDouble = (double*)calloc(M3_PROFILE_MAX_SECTIONS, sizeof(double));
            assert( agInt64 && agDouble );
          }
          MPI_Reduce( staticNumCalls, agInt64, M3_PROFILE_MAX_SECTIONS, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD );
          if( myRank == 0 )
            memcpy( staticNumCalls, agInt64 , sizeof(int64_t)*M3_PROFILE_MAX_SECTIONS );
          
          MPI_Reduce( staticTotalTime, agDouble, M3_PROFILE_MAX_SECTIONS, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
          if( myRank == 0 )
            memcpy( staticTotalTime, agDouble , sizeof(double)*M3_PROFILE_MAX_SECTIONS );
#ifdef USE_PAPI
          MPI_Reduce( staticFlopCount, agInt64, M3_PROFILE_MAX_SECTIONS, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD );
          if( myRank == 0 )
            memcpy( staticFlopCount, agInt64, sizeof(int64_t)*M3_PROFILE_MAX_SECTIONS );
          MPI_Reduce( staticFlipCount, agInt64, M3_PROFILE_MAX_SECTIONS, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD );
          if( myRank == 0 )
            memcpy( staticFlipCount, agInt64, sizeof(int64_t)*M3_PROFILE_MAX_SECTIONS );
#endif
          if( myRank == 0 )
	  {
            free(agInt64);
            free(agDouble);
          }
          else
            break;
        }
#else
        /* If not using mpi, don't need to collect aggregate statistics */
        if( j == 1 )
          break;
#endif

        k = 60*lrint(staticInitTime/60);

        /* m3_profile_title_date.proc */
        if( staticTitleString )
        {
          tempPtr = strchr( staticTitleString, ' ');
          if(tempPtr)
            *tempPtr = '\0';

          sprintf( fileName, "m3_profile/m3_profile_%s_%li_%s_%li", staticTitleString, k, myHostname, pid);

          if(tempPtr)
            *tempPtr = ' ';
        }
        else
	{
          sprintf( fileName, "m3_profile/m3_profile_%li", k );          
        }

#ifdef USE_MPI
        if( j == 0 ) 
          sprintf( tempString, ".%i", myRank );
        else
          strcpy( tempString, ".all"); 
        
        strcat( fileName, tempString );
#endif

        
        if( ( staticProfileLevel == 2 ) ||
            ( staticProfileLevel == 1 && j == 0 && numProc == 1 ) || 
            ( staticProfileLevel == 1 && j == 1 ) )
	{
          /* Open the output file.  */ 
          outFile = fopen( fileName, "w");
          assert(outFile != NULL);

          /* Write a title */
          if( staticTitleString )
            fprintf(outFile, "M3_Profile:  %s\n\n", staticTitleString );
          else
            fprintf(outFile, "M3_Profile\n\n" );
          

          /* Write the init date, and the run time.  */
#ifdef USE_MPI
          fprintf(outFile, "Number of processors:  %i\n", numProc );
          finalTime = MPI_Wtime();
#else
          gettimeofday(&tic, &tz );
          finalTime = tic.tv_sec + tic.tv_usec*1e-6;
#endif
          fprintf( outFile, "Start date %s\n", staticInitDate );
          fprintf( outFile, "Run time in seconds:  %e\n\n", finalTime - staticInitTime );

          if( j == 1 )
            fprintf(outFile, "Aggregate statistics\n\n");

          for( i = 0; i < M3_PROFILE_MAX_SECTIONS; i++ )
          {
            if( staticNumCalls[i] )
            {
              fprintf(outFile, "-----------------------------\n");
              fprintf(outFile, "    Profile ID number:  %lli\n", i);
              if( staticProfileName[i] )
                fprintf(outFile, "    %s\n", staticProfileName[i] );
              fprintf(outFile, "      Total number of calls:          %lli\n", staticNumCalls[i]);
              fprintf(outFile, "      Total time (seconds):           %e\n", staticTotalTime[i]);
              fprintf(outFile, "      Mean time per call (seconds):   %e\n", staticTotalTime[i]/staticNumCalls[i]);
              fprintf(outFile, "      Mean time per task (seconds):   %e\n", staticTotalTime[i]/numProc );
              fprintf(outFile, "      Percent of wall clock           %.6f %%\n", staticTotalTime[i]/numProc/(finalTime - staticInitTime)*100 );
#ifdef USE_PAPI
              fprintf(outFile, "      Flop count:                     %lli\n", staticFlopCount[i]);
              fprintf(outFile, "      Flop rate:                      %.6e\n", staticFlopCount[i]/staticTotalTime[i]);
              fprintf(outFile, "      Flip count:                     %lli\n", staticFlipCount[i]);
              fprintf(outFile, "      Flip rate:                      %.6e\n", staticFlipCount[i]/staticTotalTime[i]);
#endif
              fprintf(outFile, "\n\n");
            }
          }

          fclose(outFile);
        }
      }


      /* Free up static memory */
      if( staticTitleString )
      {
        free(staticTitleString);
        staticTitleString = NULL;
      }

      if( staticProfileName )
      {
        for( i = 0; i < M3_PROFILE_MAX_SECTIONS; i++ )
          if( staticProfileName[i] )
            free( staticProfileName[i] );
        free(staticProfileName);
        staticProfileName = NULL;
      }

      if( staticNumCalls )
      {
        free( staticNumCalls );
        staticNumCalls = NULL;
      }
      
      if( staticTotalTime )
      {
        free( staticTotalTime );
        staticTotalTime = NULL;
      }

      if( staticStartTime )
      {
        free(staticStartTime );
        staticStartTime = NULL;
      }
#ifdef USE_PAPI
      if( staticFlopCount );
      {
        free(staticFlopCount);
        staticFlopCount = NULL;
      }
      if( staticFlipCount );
      {
        free(staticFlipCount);
        staticFlipCount = NULL;
      }
#endif

      break;
    case M3_PROFILE_START:
      if( staticProfileName == NULL ||
          staticNumCalls == NULL || 
          staticTotalTime == NULL )
      {
	/*        fprintf(stderr, "WARNING:  M3_Profile, called without initializing\n");  */
        break;
      }
      if( staticProfileName[sectionID] == NULL )
      {
        staticProfileName[sectionID] = (char*)calloc(4*(strlen(sectionName)/4 + 1), sizeof(char));
        assert(staticProfileName[sectionID] != NULL);
        strcpy(staticProfileName[sectionID], sectionName);
      }
#ifdef USE_MPI
#ifndef USE_PAPI
      sprintf( pcontrolID, "%i", sectionID);
      MPI_Pcontrol( 1, pcontrolID );
#endif
#endif
#ifdef USE_MPI
      staticStartTime[sectionID] = MPI_Wtime();
#else
      gettimeofday(&tic, &tz);
      staticStartTime[sectionID] = tic.tv_sec + tic.tv_usec*1e-6;
#endif
#ifdef USE_PAPI
      PAPI_accum_counters(papiCounters, M3_NUM_PAPI_EVENTS );
      staticFlopCounter[sectionID] = papiCounters[0];
      staticFlipCounter[sectionID] = papiCounters[1];
#endif
      break;
    case M3_PROFILE_STOP:
      if( staticProfileName == NULL ||
          staticNumCalls == NULL || 
          staticTotalTime == NULL )
      {
	/*        fprintf(stderr, "WARNING:  M3_Profile, called without initializing\n");  */
        break;
      }
#ifdef USE_MPI
#ifndef USE_PAPI
      sprintf( pcontrolID, "%i", sectionID);
      MPI_Pcontrol( -1, pcontrolID );
#endif
#endif
      staticNumCalls[sectionID]++;
#ifdef USE_MPI
      staticTotalTime[sectionID] += MPI_Wtime() - staticStartTime[sectionID];
#else
      gettimeofday(&tic, &tz);
      staticTotalTime[sectionID] += (tic.tv_sec + tic.tv_usec*1e-6) - staticStartTime[sectionID];
#endif
#ifdef USE_PAPI
      PAPI_accum_counters(papiCounters, M3_NUM_PAPI_EVENTS );
      staticFlopCount[sectionID] += papiCounters[0] - staticFlopCounter[sectionID];
      staticFlipCount[sectionID] += papiCounters[1] - staticFlipCounter[sectionID];
#endif
      break;
  }
}
