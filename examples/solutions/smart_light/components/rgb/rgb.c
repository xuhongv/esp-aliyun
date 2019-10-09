/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-01 12:35:32
 * @LastEditTime: 2019-10-09 17:15:25
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <sdkconfig.h>
#include "driver/ledc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rgb.h"
#define PWM_TARGET_DUTY 8192

void rgb_set_pwm(uint32_t r, uint32_t g, uint32_t b)
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, r * PWM_TARGET_DUTY / 100);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, g * PWM_TARGET_DUTY / 100);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, b * PWM_TARGET_DUTY / 100);

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
}

void rgb_set_blink()
{

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, PWM_TARGET_DUTY);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);

    vTaskDelay(100 / portTICK_PERIOD_MS); //调用延时函数
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, PWM_TARGET_DUTY);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);

    vTaskDelay(100 / portTICK_PERIOD_MS); //调用延时函数
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, PWM_TARGET_DUTY);

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
}

/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-01 12:35:32
 * @LastEditTime: 2019-10-01 12:49:24
 * @LastEditors: Please set LastEditors
 */

void init_pwm_rgb(int LEDC_IO_0, int LEDC_IO_1, int LEDC_IO_2)
{

    // enable ledc module
    periph_module_enable(PERIPH_LEDC_MODULE);

    // config the timer
    ledc_timer_config_t ledc_timer = {
        //set timer counter bit number
        .duty_resolution = LEDC_TIMER_13_BIT,
        //set frequency of pwm
        .freq_hz = 5000,
        //timer mode,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        //timer index
        .timer_num = LEDC_TIMER_0};
    ledc_timer_config(&ledc_timer);

    //config the channel
    ledc_channel_config_t ledc_channel = {
        //set LEDC channel 0
        .channel = LEDC_CHANNEL_0,
        //set the duty for initialization.(duty range is 0 ~ ((2**bit_num)-1)
        .duty = 100,
        //GPIO number
        .gpio_num = LEDC_IO_0,
        //GPIO INTR TYPE, as an example, we enable fade_end interrupt here.
        .intr_type = LEDC_INTR_FADE_END,
        //set LEDC mode, from ledc_mode_t
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        //set LEDC timer source, if different channel use one timer,
        //the frequency and bit_num of these channels should be the same
        .timer_sel = LEDC_TIMER_0};
    //set the configuration
    ledc_channel_config(&ledc_channel);

    //config ledc channel1
    ledc_channel.channel = LEDC_CHANNEL_1;
    ledc_channel.gpio_num = LEDC_IO_1;
    ledc_channel_config(&ledc_channel);
    //config ledc channel2
    ledc_channel.channel = LEDC_CHANNEL_2;
    ledc_channel.gpio_num = LEDC_IO_2;
    ledc_channel_config(&ledc_channel);
}