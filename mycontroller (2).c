#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "sys/log.h"
#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#define LOG_MODULE "Controller"
#define LOG_LEVEL LOG_LEVEL_INFO
#define WITH_CONTROLLER_REPLY 0
#define UDP_SENSOR_PORT 8765
#define UDP_CONTROLLER_PORT 5678
static struct simple_udp_connection udp_connection;
int counter = 0;
float arr_data[30][3];
//----------------------------------------------------------------
PROCESS(controller_process, "Controller Process");
AUTOSTART_PROCESSES(&controller_process);
//----------------------------------------------------------------
// For each incoming datagram, the function above will be called with
// parameters that provide source/destination addresses and ports, and the payload.
static void udp_rx_callback(struct simple_udp_connection *c,
const uip_ipaddr_t *sender_addr,
uint16_t sender_port,
const uip_ipaddr_t *receiver_addr,
uint16_t receiver_port,
const uint8_t *data,
uint16_t datalen)
{
// "LOG_INFO" can be regarded as "printf"
// LOG_INFO("Receiving data from ");
// LOG_INFO_6ADDR(sender_addr);
// LOG_INFO("\n");
// Transfer "data" to "Sensor" class
struct Sensor sensor = *(struct Sensor*) data;
if(sensor.count < 30 && counter == 0)
{
	arr_data[sensor.count][0] += sensor.temperature;
	arr_data[sensor.count][1] += sensor.humidity;
	arr_data[sensor.count][2] += sensor.pressure;
}
else if(sensor.count >30 && counter == 0)
{
for(int i = 0 ; i < 30 ; i++)
{
LOG_INFO("#%u Temperature: %f, Humidity: %f, Pressure: %f\n", i,
arr_data[i][0],
arr_data[i][1], arr_data[i][2]);
}
counter ++;
}
#if WITH_CONTROLLER_REPLY
char str[32];
snprintf(str, sizeof(str), "Data Received");
simple_udp_sendto(&udp_connection, str, strlen(str), sender_addr);
#endif
}
//----------------------------------------------------------------
// The process thread of controller
PROCESS_THREAD(controller_process, ev, data) {
PROCESS_BEGIN();
NETSTACK_ROUTING.root_start();
// Register the UDP conntection with host port and remote port
simple_udp_register(&udp_connection, UDP_CONTROLLER_PORT, NULL,
UDP_SENSOR_PORT, udp_rx_callback);
PROCESS_END();
}
