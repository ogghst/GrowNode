// Copyright 2021 Nicola Muratori (nicola.muratori@gmail.com)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef MAIN_GN_COMMONS_H_
#define MAIN_GN_COMMONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define GN_NODE_NAME_SIZE 32
#define GN_LEAF_NAME_SIZE 32
#define GN_LEAF_PARAM_NAME_SIZE 32

#include "esp_system.h"
#include "esp_event.h"
#include "gn_event_source.h"

typedef enum {
	GN_CONFIG_STATUS_NOT_INITIALIZED,
	GN_CONFIG_STATUS_INITIALIZING,
	GN_CONFIG_STATUS_ERROR,
	GN_CONFIG_STATUS_NETWORK_ERROR,
	GN_CONFIG_STATUS_SERVER_ERROR,
	GN_CONFIG_STATUS_OK
} gn_config_status_t;

typedef void *gn_leaf_config_handle_t;
typedef void *gn_node_config_handle_t;
typedef void *gn_config_handle_t;

typedef void* gn_display_container_t;

typedef struct {
	gn_event_id_t id;
	char leaf_name[GN_LEAF_NAME_SIZE];
	char param_name[GN_LEAF_PARAM_NAME_SIZE];
	void *data; /*!< Data associated with this event */
	int data_size; /*!< Length of the data for this event */
} gn_leaf_event_t;

typedef gn_leaf_event_t *gn_leaf_event_handle_t;

typedef struct {
	gn_event_id_t id;
	char node_name[GN_NODE_NAME_SIZE];
	void *data; /*!< Data associated with this event */
	int data_size; /*!< Length of the data for this event */
} gn_node_event_t;

typedef gn_node_event_t *gn_node_event_handle_t;

typedef void (*gn_leaf_task_callback)(gn_leaf_config_handle_t leaf_config);

typedef enum {
	GN_VAL_TYPE_STRING, GN_VAL_TYPE_BOOLEAN, GN_VAL_TYPE_DOUBLE,
} gn_val_type_t;

typedef union {
	char *s;
	bool b;
	double d;
} gn_val_t;

typedef struct {
	gn_val_type_t t;
	gn_val_t v;
} gn_param_val_t;

typedef gn_param_val_t *gn_param_val_handle_t;

struct gn_leaf_param {
	char *name;
	gn_param_val_handle_t param_val;
	gn_leaf_config_handle_t leaf_config;
	struct gn_leaf_param *next;
};

typedef struct gn_leaf_param gn_leaf_param_t;

typedef gn_leaf_param_t *gn_leaf_param_handle_t;

//typedef void* gn_leaf_context_handle_t;

size_t gn_common_leaf_event_mask_param(gn_leaf_event_handle_t evt,
		gn_leaf_param_handle_t param);


#ifdef __cplusplus
}
#endif //__cplusplus


#endif /* MAIN_GN_COMMONS_H_ */
