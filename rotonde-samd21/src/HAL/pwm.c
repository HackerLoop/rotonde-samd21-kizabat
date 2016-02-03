/*
 * pwm.c
 *
 * Created: 03/02/2016 17:09:28
 *  Author: GroundLayer
 */ 

#include "HAL/pwm.h"

pwm_instance HAL_pwn_init(uint32_t out_pin1, uint32_t out_mux1, uint32_t out_pin2, uint32_t out_mux2, Tc *const module){
	
	pwm_instance pwm;
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	
	config_tc.counter_size    = TC_COUNTER_SIZE_8BIT;
	config_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_PWM;
	config_tc.counter_16_bit.compare_capture_channel[0] = 0;
	config_tc.clock_source = GCLK_GENERATOR_0;
	
	config_tc.pwm_channel[0].enabled = true;
	config_tc.pwm_channel[0].pin_out = out_pin1;
	config_tc.pwm_channel[0].pin_mux = out_mux1;
	config_tc.pwm_channel[1].enabled = true;
	config_tc.pwm_channel[1].pin_out = out_pin2;
	config_tc.pwm_channel[1].pin_mux = out_mux2;
	
	tc_init(&pwm, module, &config_tc);
	return pwm;
}

enum status_code HAL_pwn_set(pwm_instance* pwm, int duty_cyle, int out_num){
	tc_disable(pwm);
	uint32_t on_time = (uint32_t)( 255 * duty_cyle / 100);
	enum status_code result = tc_set_compare_value(pwm, out_num , on_time);
	tc_enable(pwm);
	return result;
}

void HAL_pwm_stop(pwm_instance* pwm){
	tc_disable(pwm);
}