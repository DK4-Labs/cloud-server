/*******************************************************************************/

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/*******************************************************************************/

void output_results(Simulation_Run_Ptr this_simulation_run)
{
    Simulation_Run_Data_Ptr sim_data;

    sim_data = (Simulation_Run_Data_Ptr)simulation_run_data(this_simulation_run);
    printf("\n");
    printf("Random Seed = %d \n", sim_data->random_seed);
    printf("Total Mean Delay = %f \n ", sim_data->accumulated_delay / sim_data->packets_processed);
    for(int i = 0; i < NUMBER_OF_MOBILE_DEVICES; i++)
    {
        printf("Mean Delay of Mobile Device %d = %f \n", i,(sim_data->mobile_devices[i]).accumulated_delay / (sim_data->mobile_devices[i]).accumulated_delay);
    }
    // printf("Arrival Rate = %f \n", );

    //fprintf(*writeFile, "%.1f, %f, %f \n", sim_data->accumulated_delay / sim_data->number_of_packets_processed, (double)(sim_data->number_of_collisions + sim_data->number_of_packets_processed) / sim_data->number_of_packets_processed, PACKET_ARRIVAL_RATE);


}