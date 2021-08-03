#include "unity.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "grownode.h"
#include "grownode_intl.h"
#include "gn_mqtt_protocol.h"
#include "gn_pump.h"


//functions hidden to be tested
void _gn_mqtt_event_handler(void *handler_args, esp_event_base_t base,
		int32_t event_id, void *event_data);

void _gn_mqtt_build_leaf_parameter_command_topic(
		gn_leaf_config_handle_t _leaf_config, char *param_name, char *buf);

extern gn_config_handle_t config;
extern gn_node_config_handle_t node_config;

gn_leaf_config_handle_t pump_config;

TEST_CASE("gn_init_add_pump", "[pump]")
{
	config = gn_init();
	TEST_ASSERT(config != NULL);
	node_config = gn_node_create(config, "node");
	TEST_ASSERT_EQUAL_STRING("node", gn_get_node_config_name(node_config));
	TEST_ASSERT_EQUAL(gn_node_get_size(node_config),0);
	pump_config = gn_leaf_create(node_config, "pump",
		gn_pump_task, 4096);
	TEST_ASSERT_EQUAL(gn_node_get_size(node_config),1);
	esp_err_t ret = gn_node_start(node_config);
	TEST_ASSERT_EQUAL(ret, ESP_OK);

}

TEST_CASE("gn_leaf_create pump", "[pump]")
{
pump_config = gn_leaf_create(node_config, "pump",
	gn_pump_task, 4096);

TEST_ASSERT_EQUAL(gn_node_get_size(node_config),1);
TEST_ASSERT(pump_config != NULL);


}

/*
TEST_CASE("gn pump_send_on", "[pump]")
{

gn_leaf_event_t evt;

evt.id = GN_LEAF_PARAM_MESSAGE_RECEIVED_EVENT;
strncpy(evt.leaf_name, "pump", 5);
strncpy(evt.param_name, "status", 7);
char* data = "true";
evt.data = data;
evt.data_size = 4;

esp_err_t ret = gn_event_send_internal(config, &evt);
TEST_ASSERT_EQUAL(ret, ESP_OK);

}

TEST_CASE("gn pump_send_off", "[pump]")
{

gn_leaf_event_t evt;

evt.id = GN_LEAF_PARAM_MESSAGE_RECEIVED_EVENT;
strncpy(evt.leaf_name, "pump", 5);
strncpy(evt.param_name, "status", 7);
char* data = "false";
evt.data = data;
evt.data_size = 6;

esp_err_t ret = gn_event_send_internal(config, &evt);
TEST_ASSERT_EQUAL(ret, ESP_OK);

}

TEST_CASE("gn pump_send_pwm_500", "[pump]")
{

gn_leaf_event_t evt;

evt.id = GN_LEAF_PARAM_MESSAGE_RECEIVED_EVENT;
strncpy(evt.leaf_name, "pump", 5);
strncpy(evt.param_name, "power", 7);
char* data = "500";
evt.data = data;
evt.data_size = 4;

esp_err_t ret = gn_event_send_internal(config, &evt);
TEST_ASSERT_EQUAL(ret, ESP_OK);

}

TEST_CASE("gn pump_send_pwm_0", "[pump]")
{

gn_leaf_event_t evt;

evt.id = GN_LEAF_PARAM_MESSAGE_RECEIVED_EVENT;
strncpy(evt.leaf_name, "pump", 5);
strncpy(evt.param_name, "power", 7);
char* data = "0";
evt.data = data;
evt.data_size = 4;

esp_err_t ret = gn_event_send_internal(config, &evt);
TEST_ASSERT_EQUAL(ret, ESP_OK);

}
*/

TEST_CASE("gn_receive_status_0", "[pump]")
{

	esp_mqtt_event_handle_t event = (esp_mqtt_event_t*) malloc(sizeof(esp_mqtt_event_t));
	event->client = ((gn_config_handle_intl_t)config)->mqtt_client;
	esp_mqtt_event_id_t event_id = MQTT_EVENT_DATA;
	char* topic = malloc(100*sizeof(char));

	_gn_mqtt_build_leaf_parameter_command_topic(pump_config, "status", topic);

	char data[] = "0";
	event->topic = (char*)malloc(strlen(topic)*sizeof(char));
	event->data = (char*)malloc(strlen(data)*sizeof(char));
	event->topic_len = strlen(topic);
	event->data_len = strlen(data);

	strncpy(event->topic, topic, event->topic_len);
	strncpy(event->data, data, event->data_len);

	esp_event_base_t base = "base";
	void* handler_args = 0;

	_gn_mqtt_event_handler(handler_args, base, event_id, event);
	TEST_ASSERT(true);

	free(event);
	free(topic);
	free(event->topic);
	free(event->data);

}

TEST_CASE("gn_receive_status_1", "[pump]")
{

	esp_mqtt_event_handle_t event = (esp_mqtt_event_t*) malloc(sizeof(esp_mqtt_event_t));
	event->client = ((gn_config_handle_intl_t)config)->mqtt_client;
	esp_mqtt_event_id_t event_id = MQTT_EVENT_DATA;
	char* topic = malloc(100*sizeof(char));

	_gn_mqtt_build_leaf_parameter_command_topic(pump_config, "status", topic);

	char data[] = "1";
	event->topic = (char*)malloc(strlen(topic)*sizeof(char));
	event->data = (char*)malloc(strlen(data)*sizeof(char));
	event->topic_len = strlen(topic);
	event->data_len = strlen(data);

	strncpy(event->topic, topic, event->topic_len);
	strncpy(event->data, data, event->data_len);

	esp_event_base_t base = "base";
	void* handler_args = 0;

	_gn_mqtt_event_handler(handler_args, base, event_id, event);
	TEST_ASSERT(true);

	free(event);
	free(topic);
	free(event->topic);
	free(event->data);

}


TEST_CASE("gn_receive_power_0", "[pump]")
{

	esp_mqtt_event_handle_t event = (esp_mqtt_event_t*) malloc(sizeof(esp_mqtt_event_t));
	event->client = ((gn_config_handle_intl_t)config)->mqtt_client;
	esp_mqtt_event_id_t event_id = MQTT_EVENT_DATA;
	char* topic = malloc(100*sizeof(char));

	_gn_mqtt_build_leaf_parameter_command_topic(pump_config, "power", topic);

	char data[] = "0";
	event->topic = (char*)malloc(strlen(topic)*sizeof(char));
	event->data = (char*)malloc(strlen(data)*sizeof(char));
	event->topic_len = strlen(topic);
	event->data_len = strlen(data);

	strncpy(event->topic, topic, event->topic_len);
	strncpy(event->data, data, event->data_len);

	esp_event_base_t base = "base";
	void* handler_args = 0;

	_gn_mqtt_event_handler(handler_args, base, event_id, event);
	TEST_ASSERT(true);

	free(event);
	free(topic);
	free(event->topic);
	free(event->data);

}


TEST_CASE("gn_receive_power_128", "[pump]")
{

	esp_mqtt_event_handle_t event = (esp_mqtt_event_t*) malloc(sizeof(esp_mqtt_event_t));
	event->client = ((gn_config_handle_intl_t)config)->mqtt_client;
	esp_mqtt_event_id_t event_id = MQTT_EVENT_DATA;
	char* topic = malloc(100*sizeof(char));

	_gn_mqtt_build_leaf_parameter_command_topic(pump_config, "power", topic);

	char data[] = "128";
	event->topic = (char*)malloc(strlen(topic)*sizeof(char));
	event->data = (char*)malloc(strlen(data)*sizeof(char));
	event->topic_len = strlen(topic);
	event->data_len = strlen(data);

	strncpy(event->topic, topic, event->topic_len);
	strncpy(event->data, data, event->data_len);

	esp_event_base_t base = "base";
	void* handler_args = 0;

	_gn_mqtt_event_handler(handler_args, base, event_id, event);
	TEST_ASSERT(true);

	free(event);
	free(topic);
	free(event->topic);
	free(event->data);

}

TEST_CASE("gn_receive_power_500", "[pump]")
{

	esp_mqtt_event_handle_t event = (esp_mqtt_event_t*) malloc(sizeof(esp_mqtt_event_t));
	event->client = ((gn_config_handle_intl_t)config)->mqtt_client;
	esp_mqtt_event_id_t event_id = MQTT_EVENT_DATA;
	char* topic = malloc(100*sizeof(char));

	_gn_mqtt_build_leaf_parameter_command_topic(pump_config, "power", topic);

	char data[] = "500";
	event->topic = (char*)malloc(strlen(topic)*sizeof(char));
	event->data = (char*)malloc(strlen(data)*sizeof(char));
	event->topic_len = strlen(topic);
	event->data_len = strlen(data);

	strncpy(event->topic, topic, event->topic_len);
	strncpy(event->data, data, event->data_len);

	esp_event_base_t base = "base";
	void* handler_args = 0;

	_gn_mqtt_event_handler(handler_args, base, event_id, event);
	TEST_ASSERT(true);

	free(event);
	free(topic);
	free(event->topic);
	free(event->data);

}

