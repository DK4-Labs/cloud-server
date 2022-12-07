/*******************************************************************************/

#include "main.h"

/*******************************************************************************/

#ifndef _PACKET_TRANSMISSION_H_
#define _PACKET_TRANSMISSION_H_

/*******************************************************************************/

/*
 * Function prototypes
 */
void
transmission_arrival_event(Simulation_Run_Ptr, void *);

long int
schedule_transmission_arrival_event(Simulation_Run_Ptr, Time, void *);

void
transmission_start_event(Simulation_Run_Ptr, void *);

long int
schedule_transmission_start_event(Simulation_Run_Ptr, Time, void *);

void
transmission_end_event(Simulation_Run_Ptr, void *);

long int
schedule_transmission_end_event(Simulation_Run_Ptr, Time, void *);

/*******************************************************************************/

#endif /* packet_transmission.h */




