#include <stdio.h>
#include <math.h>
#include "trace.h"
#include "output.h"
#include "packet_transmission.h"


long int
schedule_transmission_arrival_event(Simulation_Run_Ptr simulation_run, Time event_time, void * packet)
{
  Event event;

  event.description = "Packet Arrives at Cloud Server";
  event.function = transmission_arrival_event;
  event.attachment = packet;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

void 
transmission_arrival_event(Simulation_Run_Ptr simulation_run, void * packet)
{
  packet_t * this_packet;
  Buffer_Ptr cloud_server_queue;
  Simulation_Run_Data_Ptr data;
  
  this_packet = (packet_t *) packet;
  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
  cloud_server_queue = data->cloud_server->fifoqueue;
  
  fifoqueue_put(cloud_server_queue, (void *) this_packet);
  if(fifoqueue_size(cloud_server_queue) == 1)
  {
    schedule_transmission_arrival_event(simulation_run, simulation_run_get_time(simulation_run), packet);
  }
}

long int
schedule_transmission_start_event(Simulation_Run_Ptr simulation_run, Time event_time, void * packet)
{
  Event event;

  event.description = "Cloud server services packet";
  event.function = transmission_start_event;
  event.attachment = packet;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

void
transmission_start_event(Simulation_Run_Ptr simulation_run, void * packet)
{
    packet_t * this_packet;
    // Buffer_Ptr cloud_server_queue;
    Simulation_Run_Data_Ptr data;

    this_packet = (packet_t *) packet;
    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    // cloud_server_queue = data->cloud_server->fifoqueue;

    schedule_transmission_end_event(simulation_run, simulation_run_get_time(simulation_run) + this_packet->service_time, packet);
}

long int
schedule_transmission_end_event(Simulation_Run_Ptr simulation_run, Time event_time, void * packet)
{
   Event event;
   
   event.description = "Cloud Server Finishes Transmission";
   event.function = transmission_end_event;
   event.attachment = packet;

   return simulation_run_schedule_event(simulation_run, event, event_time);
}

void 
transmission_end_event(Simulation_Run_Ptr simulation_run, void * packet)
{
    packet_t * this_packet, * next_packet;
    Simulation_Run_Data_Ptr data;
    mobile_device_t * device;
    Buffer_Ptr cloud_server_queue;
    double delay;
    
    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    this_packet = (packet_t *) packet;


    data->packets_processed++;
    device = &(data->mobile_devices[this_packet->mobile_device_id]);
    device->packets_processed++;

    delay = simulation_run_get_time(simulation_run) - 
        this_packet->arrive_time;
    device->accumulated_delay += delay;
    data->accumulated_delay += delay;

    cloud_server_queue = data->cloud_server->fifoqueue;
    if (fifoqueue_get(cloud_server_queue) != packet)
    {
        exit(1);
    }

    xfree((void *) this_packet);

    if (fifoqueue_size(cloud_server_queue) > 0)
    {
        next_packet = (packet_t *) fifoqueue_see_front(cloud_server_queue);
        schedule_transmission_start_event(simulation_run, simulation_run_get_time(simulation_run),next_packet);
    }
    
}
