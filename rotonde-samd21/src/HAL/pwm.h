/*
 * pwm.h
 *
 * Created: 03/02/2016 17:09:42
 *  Author: GroundLayer
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "asf.h"

typedef struct tc_module pwm_instance;

pwm_instance HAL_pwn_init(uint32_t out_pin1, uint32_t out_mux1, uint32_t out_pin2, uint32_t out_mux2, Tc *const module);
enum status_code HAL_pwn_set(pwm_instance* pwm, int duty_cyle, int out_num);
void HAL_pwm_stop(pwm_instance* pwm);

#endif /* PWM_H_ */