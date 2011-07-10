#ifndef _H_M3_profile
#define _H_M3_profile

#define M3_PROFILE_MAX_SECTIONS 256
#define M3_PROFILE_LEVEL 1

/* 
  ENVIRONMENT VARIABLES:
  M3_PROFILE_LEVEL
  if set to 0 then no profiling info will be printed.
  if set to 1 then profiling will be printed but only aggregate information if MPI is used.
  if set to 2 then profileing will be printed for every processor and aggregate statistics.
*/

void M3_ProfileInit( const char *titleString );
void M3_ProfileFinalize( void );
void M3_ProfileStart( int sectionID, const char *sectionName );
void M3_ProfileStop( int sectionID );


#endif
