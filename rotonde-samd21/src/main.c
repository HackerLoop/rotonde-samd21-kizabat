#include <asf.h>

#include "HAL/usb.h"

#include "tasks/modules.h"
#include "tasks/stream.h"

#include "HAL/pwm.h"

int main (void)
{
	irq_initialize_vectors();
	cpu_irq_enable();
	
	system_init();
	sleepmgr_init();
	
	delay_init();
	
	HAL_usb_init();
	
	pwm_instance  pwm1, pwm2;
	pwm1 = HAL_pwn_init(PIN_PB02E_TC6_WO0 ,MUX_PB02E_TC6_WO0 ,PIN_PB03E_TC6_WO1, MUX_PB03E_TC6_WO1 , TC6 );
	pwm2 = HAL_pwn_init(PIN_PB10E_TC5_WO0 ,MUX_PB10E_TC5_WO0 ,PIN_PB11E_TC5_WO1, MUX_PB11E_TC5_WO1, TC5 );
	
	while(1){
	for(int i = 0 ; i < 100 ; i++){
	HAL_pwn_set(&pwm1, i, 0);
	HAL_pwn_set(&pwm1, i, 1);
	HAL_pwn_set(&pwm2, i, 0);
	HAL_pwn_set(&pwm2, i, 1);
	delay_ms(1000);
	}
	}

	
	module_in = xQueueCreate(MODULE_QUEUE_LENGTH , MODULE_QUEUE_ITEM_SIZE);
	module_out = xQueueCreate(MODULE_QUEUE_LENGTH , MODULE_QUEUE_ITEM_SIZE);
	
	if( module_in == NULL || module_out == NULL){
		/* The queue could not be created. */
		while(1);
	}
	
	// Create tasks
	xTaskCreate(&receiver_stream, (const char *)"receiver_stream", RECEIVER_STREAM_STACK_SIZE, NULL , RECEIVER_STREAM_PRIORITY , NULL);
	xTaskCreate(&sender_stream, (const char *)"sender_stream", SENDER_STREAM_STACK_SIZE, NULL , SENDER_STREAM_PRIORITY , NULL);
	xTaskCreate(&modules, (const char *)"modules", MODULES_STACK_SIZE, NULL , MODULES_PRIORITY , NULL);

	//Start FreeRTOS scheduler
	vTaskStartScheduler();

	/* Code should never get here */
	while (1) {
	}
}
