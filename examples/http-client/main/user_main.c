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
#include "http.h"

#define EXAMPLE_ESP_WIFI_SSID      "HONOR"
#define EXAMPLE_ESP_WIFI_PASS      "135792468"

void app_main()
{
    esp_err_t ret = nvs_flash_init();

    initDEBUG("", '5', 921600, "DSA - Debug example");
    initWIFI("HONOR","135792468");

    xTaskCreate(&http_test_task, "http_test_task", 8192, NULL, 5, NULL);
}


