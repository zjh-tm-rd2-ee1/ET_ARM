#include "include.h" 

/*********************************************************************************
* Function: Test_DEMO
* Description: DEMO test
* Input: none
* Output: none
* Return: none
* Call: external
*/
 void Test_DEMO(void)
 {
	TOTAL_DIS_NUM = 7;
 	switch (DIS_NUM) 
	{
		case (0): 		
			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
		  FPGA_DisPattern(0, 255, 0, 0);
			break;
		case (1): 
			FPGA_Info_Visible(INFO_NONE);
		  FPGA_DisPattern(0, 0, 255, 0);			
			break;
		case (2): 
			FPGA_DisPattern(0, 0, 0, 255);
			break;
		case (3): 
			FPGA_DisPattern(0, 0, 0, 0);
			break;
		case (4): 
			FPGA_DisPattern(0, 255, 255, 255);
			break;
		case (5): 
			FPGA_DisPattern(0, 128, 128, 128);
			break;
		case (6): 
			FPGA_DisPattern(0, 0, 0, 0);
			KEY_SLEEPIN(); 
			break;
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}
 }
