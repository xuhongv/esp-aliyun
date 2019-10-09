/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-01 12:35:38
 * @LastEditTime: 2019-10-09 17:15:42
 * @LastEditors: Please set LastEditors
 */
#ifndef _LIGHTRGB_H_
#define _LIGHTRGB_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void rgb_set_pwm(uint32_t r, uint32_t g, uint32_t b);

void init_pwm_rgb(int LEDC_IO_0, int LEDC_IO_1, int LEDC_IO_2);

void rgb_set_blink();

#endif