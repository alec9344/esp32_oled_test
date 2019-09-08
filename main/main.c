/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "ssd1306.h"


#define OLED_BLOCK_HEIGHT 8

void app_main()
{
    printf("ESP32 OLED TEST\n");

	ssd1306_128x64_i2c_init();
	ssd1306_setFixedFont(ssd1306xled_font6x8);
	ssd1306_clearScreen();

	ssd1306_printFixed(0,  OLED_BLOCK_HEIGHT*1, "ESP32 OLED TEST", STYLE_NORMAL);
	ssd1306_printFixed(0,  OLED_BLOCK_HEIGHT*2, "Normal text", STYLE_NORMAL);
	ssd1306_printFixed(0, OLED_BLOCK_HEIGHT*3, "Bold text", STYLE_BOLD);
	ssd1306_printFixed(0, OLED_BLOCK_HEIGHT*4, "Italic text", STYLE_ITALIC);
	ssd1306_negativeMode();
	ssd1306_printFixed(0, OLED_BLOCK_HEIGHT*5, "Inverted bold", STYLE_BOLD);
	ssd1306_positiveMode();
	ssd1306_printFixed(0, OLED_BLOCK_HEIGHT*7, "Restarting in ", STYLE_NORMAL);

	char str[50];
	for (int i = 10; i >= 0; i--) {
		sprintf(str, "%d...", i);
		ssd1306_printFixed(6*strlen("Restarting in "), OLED_BLOCK_HEIGHT*7, str, STYLE_NORMAL);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		ssd1306_clearBlock(6*strlen("Restarting in "),7,ssd1306_lcd.width-6*strlen("Restarting in "), OLED_BLOCK_HEIGHT);
	}

    printf("Restarting now.\n");
    esp_restart();
}
