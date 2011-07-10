#include "partition_wall.hpp"
#include "assert.h"
using namespace SorterThreadedHelper;

int main(int argc, char **argv) {
  PartitionWall pw0(0.0);
  PartitionWall pw1;

  pw1.set(1.0);
  assert(pw0 < pw1);
  pw1.set(0.0);
  assert(!(pw0 < pw1));
  pw1.set(-1.0);
  assert(!(pw0 < pw1));

  pw1.set(1.0, false);
  assert(pw0 < pw1);
  pw1.set(0.0, false);
  assert(!(pw0 < pw1));
  pw1.set(-1.0, false);
  assert(!(pw0 < pw1));

  pw1.set(1.0, true);
  assert(pw0 < pw1);
  pw1.set(0.0, true);
  assert(pw0 < pw1);
  pw1.set(-1.0, true);
  assert(pw0 < pw1);
}
