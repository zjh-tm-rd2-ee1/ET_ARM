#include "include.h"

/*********************************************************************************
* Function: Test_OQC1
* Description: OQC1 test
* Input: none
* Output: none
* Return: none
* Call: external
*/
 void Test_OQC1(void)
 {
 	TOTAL_DIS_NUM = 20;
 	switch (DIS_NUM) 
	{
		case (0): 
			FPGA_Info_Visible(INFO_RGBVAL);
			ScanBackward();
			FPGA_DisPattern(0, 127, 127, 127);
			Delay_ms(3000);
			break;
		case (1):
			FPGA_Info_Visible(INFO_VERSION|INFO_PROJECT_NO);
		  ScanForward();
		  FPGA_DisPattern(81, 0, 0x77, 0x41);	
		  Delay_ms(300); 
			break;
		case (2): 
			FPGA_Info_Visible(INFO_NONE);
			FPGA_DisPattern(82, 0, 0, 0);
			Delay_ms(3000); 
			break;
		case (3): 
			LEDA_DIM();
			FPGA_DisPattern(0, 255, 255, 255);	//low current white
		  Delay_ms(1500); 
			SPEC_LEDA_MIN = SPEC_MIN_LEDA_DIM;
      SPEC_LEDA_MAX = SPEC_MAX_LEDA_DIM;
			break;
		case (4): 
			LCD_PWM(0x0FFF);
			FPGA_DisPattern(94, 255, 0, 0);
			Delay_ms(1500);
			SPEC_LEDA_MIN = SPEC_MIN_LEDA_NORMAL;
      SPEC_LEDA_MAX = SPEC_MAX_LEDA_NORMAL;		
			break;
		case (5): 
			FPGA_DisPattern(0, 255, 255, 255);	//white
			if (Pic_Load_Finish == SET || PIC_Load_BMP_ET((uint8_t *)"0.bmp") == ERROR)
			{
				Delay_ms(ET_DLY_LOCK * 2700); 
			}
			break;
		case (6): 
			FPGA_DisPattern(24, 127, 127, 127);
			Delay_ms(1500);
			break;
		case (7): 
			FPGA_DisPattern(138, 0, 0, 0);	//flicker
			Delay_ms(300);
			break;
		case (8): 
			FPGA_DisPattern(0, 255, 0, 0);	//dotcheck
			Delay_ms(300);
			break;
		case (9): 
			if (Pic_Load == ERROR)
			{
				FPGA_Info_Visible(INFO_STR);
				FPGA_Info_Set((uint8_t *)"LOAD PIC FAIL.");
			}
			FPGA_DisPicture(0);	//picture
			Delay_ms(300);
			break;
		case (10): 
			FPGA_DisPattern(22, 127, 0, 0);
			Delay_ms(300); 
			break;
		case (11): 
			FPGA_DisPattern(1, 127, 0, 0);
			Delay_ms(300); 
			break;
		case (12): 
			FPGA_DisPattern(0, 0, 255, 0);
			Delay_ms(300);  
			break;
		case (13): 
			FPGA_DisPattern(0, 0, 0, 255);
			Delay_ms(300);
			break;
		case (14): 
			FPGA_DisPattern(17, 0, 0, 0); 	//bar
			Delay_ms(300);
			break;
		case (15): 
			FPGA_DisPattern(7, 127, 0, 0); 	//crosstalk
			Delay_ms(300); 
			break;
		case (16): 
			FPGA_DisPattern(133, 255, 0, 0); 	//HUAWEI TP
			Delay_ms(300); 
			break;
		case (17): 
			FPGA_DisPattern(136, 0, 0, 0); 	//HUAWEI S1
			Delay_ms(300);
			break;
		case (18): 
			FPGA_DisPattern(137, 0, 0, 0); 	//HUAWEI S1
			Delay_ms(300);
			break;
		case (19): 
			FPGA_DisPattern(0, 0, 0, 0);
			FPGA_Info_Visible(INFO_NONE);
			KEY_SLEEPIN(); 	
			break;
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}
	Delay_ms(ET_DLY_LOCK * 300);
 }
