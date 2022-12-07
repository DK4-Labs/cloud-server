
/*
 * 
 * Simulation_Run of the ALOHA Protocol
 * 
 * Copyright (C) 2014 Terence D. Todd
 * Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 * 
 */

/**********************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

/**********************************************************************/

#include "simlib.h"
#include "simparameters.h"
// #include "channel.h"

/**********************************************************************/

typedef double Time;
typedef Fifoqueue_Ptr Buffer_Ptr;

/**********************************************************************/


typedef struct _mobile_device_
{
  int id;
  double accumulated_delay;
  int packets_processed;
  Buffer_Ptr fifoqueue;
  long int arrival_count;
  // double accumulated_delay;
  // double mean_delay;
} mobile_device_t;

typedef struct _cloud_server_
{
  Buffer_Ptr fifoqueue;
  // long int packet_count;
  // double accumulated_delay;
  // double mean_delay;
} cloud_server_t;

/**********************************************************************/

typedef enum {WAITING, UPLOADING, TRANSMITTING} Packet_Status;

typedef struct _packet_ 
{
  double arrive_time; 
  double service_time;  // Jb or Jg
  double upload_time;   // Ub or Ug
  int mobile_device_id;
  Packet_Status status;
} packet_t;

typedef struct _simulation_run_data_
{
  mobile_device_t * mobile_devices;
  cloud_server_t * cloud_server;
  // long int blip_counter;
  long int arrival_count;
  long int packets_uploaded;
  long int packets_processed;
  double accumulated_delay;
  unsigned random_seed;
} Simulation_Run_Data, * Simulation_Run_Data_Ptr;

/**********************************************************************/

/*
 * Function prototypes
 */

int
main(void);

/**********************************************************************/

#endif /* main.h */






