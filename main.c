/*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "output.h"
#include "trace.h"
#include "simparameters.h"
#include "cleanup.h"
#include "packet_arrival.h"
#include "packet_transmission.h"
#include "cloud_server.h"
#include "main.h"

/*******************************************************************************/

int
main(void)
{
  /* Get the list of random number generator seeds defined in simparameters.h */
  unsigned random_seed;
  unsigned RANDOM_SEEDS[] = {RANDOM_SEED_LIST, 0};
  mobile_device_t mobile_devices_arr[NUMBER_OF_MOBILE_DEVICES] = { 0 };
  double job_execution_times[NUMBER_OF_MOBILE_DEVICES] = { 1, 1 };

  Simulation_Run_Ptr simulation_run;
  Simulation_Run_Data data;
  int i, j=0;

  /* Do a new simulation_run for each random number generator seed. */
  while ((random_seed = RANDOM_SEEDS[j++]) != 0) {

    /* Set the random generator seed. */
    random_generator_initialize(random_seed);

    /* Create a new simulation_run. This gives a clock and
       eventlist. Clock time is set to zero. */
    simulation_run = (Simulation_Run_Ptr) simulation_run_new();

    /* Add our data definitions to the simulation_run. */
    simulation_run_set_data(simulation_run, (void *) & data);

    /* Create and initalize the stations. */

    data.mobile_devices = mobile_devices_arr;

    /* Initialize various simulation_run variables. */
    // data.blip_counter = 0;
    data.arrival_count = 0;
    data.packets_uploaded = 0;
    data.packets_processed = 0;
    data.accumulated_delay = 0.0;
    data.random_seed = random_seed;
    
    /* Initialize the stations. */
    for(i=0; i<NUMBER_OF_MOBILE_DEVICES; i++) {
      (data.mobile_devices[i]).id = i;
      (data.mobile_devices[i]).fifoqueue = fifoqueue_new();
      // &(data.mobile_devices[i])->packet_count = 0;
      // &(data.mobile_devices[i])->accumulated_delay = 0.0;
      // &(data.mobile_devices[i])->mean_delay = 0;
    }


    /* Create and initialize the channel. */
    data.cloud_server = cloud_server_new();

    /* Schedule initial packet arrival. */
    schedule_packet_arrival_event(simulation_run, 
		    simulation_run_get_time(simulation_run) +
		    exponential_generator((double) 1/PACKET_ARRIVAL_RATE));

    /* Execute events until we are finished. */
    while(data.packets_processed < RUNLENGTH) {
      simulation_run_execute_event(simulation_run);
    }

    /* Print out some results. */
    output_results(simulation_run);

    /* Clean up memory. */
    cleanup(simulation_run);
  }

  /* Pause before finishing. */
  getchar();

  return 0;
}












