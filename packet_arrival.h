
/*******************************************************************************/

#ifndef _PACKET_ARRIVAL_H_
#define _PACKET_ARRIVAL_H_

/*******************************************************************************/

/*
 * Function prototypes
 */

void
packet_arrival_event(Simulation_Run_Ptr, void *);

long int
schedule_packet_arrival_event(Simulation_Run_Ptr, Time);

/*******************************************************************************/

#endif /* packet_arrival.h */






