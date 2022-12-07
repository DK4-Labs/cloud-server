
/*******************************************************************************/

#include <math.h>
#include <stdio.h>
#include "service_duration.h"
#include "upload_duration.h"
#include "packet_transmission.h"
#include "packet_arrival.h"

/*******************************************************************************/

long int
schedule_packet_arrival_event(Simulation_Run_Ptr simulation_run,
			      Time event_time)
{
  Event event;

  event.description = "Packet Arrival To Mobile Device";
  event.function = packet_arrival_event;
  event.attachment = NULL;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void
packet_arrival_event(Simulation_Run_Ptr simulation_run, void* dummy_ptr) 
{
  int random_mobile_device_id;
  mobile_device_t * device;
  packet_t * new_packet;
  Buffer_Ptr device_queue;
  Time now;
  Simulation_Run_Data_Ptr data;

  now = simulation_run_get_time(simulation_run);

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
  data->arrival_count++;

  /* Randomly pick the station that this packet is arriving to. Note
     that randomly splitting a Poisson process creates multiple
     independent Poisson processes.*/
  random_mobile_device_id = (int) floor(uniform_generator()*NUMBER_OF_MOBILE_DEVICES);
  device = &(data->mobile_devices[random_mobile_device_id]);
  device->arrival_count++;

  new_packet = (packet_t *) xmalloc(sizeof(packet_t));
  new_packet->arrive_time = now;
  new_packet->service_time = get_service_duration(random_mobile_device_id);
  new_packet->upload_time = get_upload_duration(random_mobile_device_id);
  new_packet->status = WAITING;
  new_packet->mobile_device_id = random_mobile_device_id;

  /* Put the packet in the buffer at that station. */
  device_queue = device->fifoqueue;
  fifoqueue_put(device_queue, (void *) new_packet);

  /* If this is the only packet at the station, transmit it (i.e., the
     ALOHA protocol). It stays in the queue either way. */
  if(fifoqueue_size(device_queue) == 1) {
    /* Transmit the packet. */
    schedule_upload_start_event(simulation_run, now, (void *) new_packet);
  }

  /* Schedule the next packet arrival. */
  schedule_packet_arrival_event(simulation_run, 
		now + exponential_generator((double) 1/PACKET_ARRIVAL_RATE));
}


