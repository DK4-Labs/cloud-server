#include <stdio.h>
#include <math.h>
#include "trace.h"
#include "output.h"
#include "packet_upload.h"

/*******************************************************************************/

long int
schedule_upload_start_event(Simulation_Run_Ptr simulation_run,
				  Time event_time,
				  void * packet) 
{
  Event event;

  event.description = "Packet Uploading";
  event.function = upload_start_event;
  event.attachment = packet;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

void
upload_start_event(Simulation_Run_Ptr simulation_run, void * ptr)
{
    packet_t * this_packet;
    Simulation_Run_Data_Ptr data;

    this_packet = (packet_t *) ptr;
    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    schedule_upload_end_event(simulation_run,
            simulation_run_get_time(simulation_run) +
            this_packet->upload_time,
            (void *) this_packet);
}

long int
schedule_upload_end_event(Simulation_Run_Ptr simulation_run,
				Time event_time,
				void * packet)
{
  Event event;

  event.description = "Packet Uploaded";
  event.function = upload_end_event;
  event.attachment = packet;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

void
upload_end_event(Simulation_Run_Ptr simulation_run, void * packet)
{
    packet_t * this_packet, * next_packet;
    Fifoqueue_Ptr queue;
    Simulation_Run_Data_Ptr data;
    
    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    this_packet = (packet_t *) packet;

    data->packets_uploaded++;
    queue = (data->mobile_devices[(this_packet->mobile_device_id)]).fifoqueue;

    if (fifoqueue_get(queue) != packet)
    {
        printf("\nBADDDDDDDDDDY >:)\n");
        exit(1);
    }

    schedule_transmission_start_event(simulation_run, simulation_run_get_time(simulation_run), (void *) this_packet);

    if(fifoqueue_size(queue) > 0)
    {
        next_packet = (packet_t *) fifoqueue_get(queue);
        schedule_upload_start_event(simulation_run, simulation_run_get_time(simulation_run), (void *)next_packet);
    }
    
}