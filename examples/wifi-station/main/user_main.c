#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"



#include "debug.h"
#include "wifi.h"

#define EXAMPLE_ESP_WIFI_SSID      "test"
#define EXAMPLE_ESP_WIFI_PASS      "kknd2019"

void app_main()
{
    initDEBUG("", '5', 921600, "DSA - Debug example");
    ESP_ERROR_CHECK(nvs_flash_init());

    initWIFI("HONOR","135792468");
}

