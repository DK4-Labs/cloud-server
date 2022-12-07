#include "service_duration.h"

/*******************************************************************************/

double
get_service_duration(int id)
{
  if(id == 0)
  {
    return ((double) SERVICE_GOOD);
  }
  else
  {
    return((double) SERVICE_BAD);
  }
}