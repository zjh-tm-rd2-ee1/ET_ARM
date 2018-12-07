#include "include.h" 

/*********************************************************************************
* Function: Test_RA
* Description: RA test, bist mode
* Input: none
* Output: none
* Return: none
* Call: external
*/
u32 CURRENT2DC(u32 current){
	//100%->20MA
	u32 dc=current*100/20;
	return dc;
}
void RA_LEDPWM(u32 current){
	u32 duty_cycle=CURRENT2DC(current);
	//u32 duty_cycle=50;
	while(1){
		u32 high_time = 20*duty_cycle/100;
		GPIO_SetBits(TEST17_GPIO_PORT, TEST17_PIN);
		Delay_us(high_time);
		GPIO_ResetBits(TEST17_GPIO_PORT, TEST17_PIN);
		Delay_us(20-high_time);
	}
}

void Test_RA(void)
{
//	FPGA_DisPattern(83, 127, 127, 127);
//	RA_LEDPWM(20);
	//RA_LEDPWM(17);
	//RA_LEDPWM(15);
	//RA_LEDPWM(13);
}
