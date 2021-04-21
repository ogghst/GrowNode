/*
 * gn_pump.h
 *
 *  Created on: 19 apr 2021
 *      Author: muratori.n
 */

#ifndef MAIN_GN_PUMP_H_
#define MAIN_GN_PUMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "grownode.h"
#include "gn_mqtt_protocol.h"

void gn_pump_init(gn_leaf_config_handle_t config);

void gn_pump_callback(gn_event_handle_t event, void* event_data);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* MAIN_GN_PUMP_H_ */
