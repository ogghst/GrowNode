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

#ifdef __cplusplus
extern "C" {
#endif

//#include "esp_log.h"
#include "gn_commons.h"
#include "grownode_intl.h"

//static const char *TAG = "gn_commons";

inline size_t gn_common_leaf_event_mask_param(gn_leaf_event_handle_t evt,
		gn_leaf_param_handle_t param) {

	if (!evt || !param)
		return 1;

	gn_leaf_config_handle_intl_t _leaf_config =
			(gn_leaf_config_handle_intl_t) param->leaf_config;

	if (strcmp(evt->leaf_name, _leaf_config->name) == 0
			&& strcmp(evt->param_name, param->name) == 0)
		return 0;
	return 1;
}

#ifdef __cplusplus
}
#endif //__cplusplus

