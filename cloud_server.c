#include "cloud_server.h"


cloud_server_t * cloud_server_new(void)
{
    cloud_server_t * new_cloud_server = (cloud_server_t *) xmalloc(sizeof(cloud_server_t));
    new_cloud_server->fifoqueue = fifoqueue_new();

    return new_cloud_server;
}
