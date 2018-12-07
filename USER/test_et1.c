#include "include.h"

/*********************************************************************************
* Function: Test_ET1
* Description: ET1 test
* Input: none
* Output: none
* Return: none
* Call: external
*/

 // DJ code
 
void Test_ET1(void){
	TOTAL_DIS_NUM = 6;
	switch (DIS_NUM){
		case (0):
//			FPGA_DisPicture(0);
//			FPGA_Info_Set((uint8_t *)"HELLO WORLD");
//			FPGA_Project_Set((uint8_t *)"I LOVE CAROL");
			FPGA_Info_Visible(INFO_NONE);
			FPGA_DisPattern(129, 0, 0x02, 0xC8);
			break;
		case (1):
			FPGA_DisPattern(0, 255, 255, 255);
			break;
		case (2):
			FPGA_DisPattern(0, 255, 0, 0);
			break;
		case (3):
			FPGA_DisPattern(0, 0, 255, 0);
			break;
		case (4):
			FPGA_DisPattern(0, 0, 0, 255);			
			break;
		case (5):
			FPGA_DisPattern(0, 0, 0, 0);
			KEY_SLEEPIN();
			Delay_ms(300);
			break;
		default:
			FPGA_DisPattern(0, 0, 0, 0);
			break;
	}
//	Delay_ms(ET_DLY_LOCK * 300);
}
