#include "include.h"

/*********************************************************************************
* Function: Test_ET3
* Description: ET3 test
* Input: none
* Output: none
* Return: none
* Call: external
*/
 void Test_ET3(void)
 {
 	TOTAL_DIS_NUM = 4;
 	switch (DIS_NUM) 
	{
		case (0): 
			FPGA_Info_Visible(INFO_RGBVAL);
			ScanBackward();
 			FPGA_DisPattern(0, 127, 127, 127);	//gray
			Delay_ms(ET_DLY_LOCK * 2700);
			break;
		case (1): 		
			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
			ScanForward();	
 			FPGA_DisPattern(82, 0, 0, 0);//Black+R100-G70-B170-W70 , CH1-FPGA_DisPattern(82, 0, 0, 0)
			Delay_ms(ET_DLY_LOCK * 2700); 
			break;
		case (2): 
			FPGA_Info_Visible(INFO_NONE);
			FPGA_DisPattern(0, 255, 255, 255);	//white	
		  Delay_ms(ET_DLY_LOCK * 2700); 
			break;
		case (3): 
			FPGA_DisPattern(0, 0, 0, 0);
			KEY_SLEEPIN(); 		
			break;
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}
	Delay_ms(ET_DLY_LOCK * 300);
 }
