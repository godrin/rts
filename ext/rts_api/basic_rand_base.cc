#include <basic_rand_base.h>
#include <stdlib.h>

float AGRandomizerBase::operator()(float f)
{
  return rand()/float(RAND_MAX);
}
int AGRandomizerBase::operator()(int i)
{
  return rand()%i;
}
