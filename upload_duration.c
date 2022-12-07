#include "service_duration.h"

/*******************************************************************************/

double
get_service_duration(int id)
{
  if(id == 0)
  {
    return ((double) UPLOAD_GOOD);
  }
  else
  {
    return((double) UPLOAD_BAD);
  }
}