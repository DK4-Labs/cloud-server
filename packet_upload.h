/******************************************************************************/

#ifndef _PACKET_UPLOAD_H_
#define _PACKET_UPLOAD_H_

/******************************************************************************/

#include "main.h"

/******************************************************************************/

/*
 * Function prototypes
 */

void
upload_start_event(Simulation_Run_Ptr,void *);

long int
schedule_upload_start_event(Simulation_Run_Ptr, Time, void *);

void
upload_end_event(Simulation_Run_Ptr, void *);

long int
schedule_upload_end_event(Simulation_Run_Ptr, Time, void*);


/******************************************************************************/

#endif /* packet_transmission.h */