#include "include.h"

void ESD_Visual_Check(void) 
{ 
		TOTAL_DIS_NUM = 20; 
		switch (DIS_NUM) 
		{ 		
		case (0): //waku
		LCD_PWM(0x0FFF);
		FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
		FPGA_DisPattern(81, 0, 0x77, 0x41); 
		Delay_ms(300);
		SPEC_LEDA_MIN = SPEC_MIN_LEDA_NORMAL;
		SPEC_LEDA_MAX = SPEC_MAX_LEDA_NORMAL;	
		break; 	
		case (1): //dark
		FPGA_Info_Visible(INFO_NONE); 
		FPGA_DisPattern(0, 0,0,0); 
		Delay_ms(300);
		break; 
		case (2): //64 
		FPGA_DisPattern(0, 64,64,64);
		Delay_ms(3000);		
		break; 
		case (3): //127 ReverseScan 
		ScanBackward();
		FPGA_DisPattern(0,127,127,127);
		FPGA_Info_Visible(INFO_RGBVAL);
		Delay_ms(2000);
		break;
		case (4): //W
		FPGA_Info_Visible(INFO_NONE); 
		ScanForward();
		FPGA_DisPattern(0, 255,255, 255); 
		if (Pic_Load_Finish == SET || PIC_Load_BMP_ET((uint8_t *)"0.bmp") == ERROR){
			Delay_ms(ET_DLY_LOCK * 2700); 
		}
		break; 
		case(5):
		FPGA_DisPattern(36, 0, 0, 0); 
		Delay_ms(300);
		break; 
		case (6):
		FPGA_DisPattern(35, 0, 0, 0); 
		Delay_ms(300);
		break; 
		case (7): //Flicker 
		FPGA_DisPattern(22,127,0,0);
		Delay_ms(300);
		break; 
		case (8): //crosstalk
		FPGA_DisPattern(1, 127,127,127); 
		Delay_ms(300);
		break; 
		case (9): //crosstalk
		FPGA_DisPattern(7, 127,127,127); 
		Delay_ms(300);
		break; 
		case (10):
		FPGA_DisPattern(133, 255, 0, 0); 	//HUAWEI TP
		Delay_ms(300);
		break; 
		case (11): 
		FPGA_DisPattern(126, 0, 255, 0);	
		Delay_ms(300);
		break; 
		case (12):
		FPGA_DisPattern(126, 255,0,255); 
		Delay_ms(300);
		break; 
		case (13): 
		FPGA_DisPattern(0, 255, 0, 0);
		Delay_ms(300);
		break; 
		case (14):
		FPGA_DisPattern(0, 0,255,0); 
		Delay_ms(300);
		break; 
		case (15): 
		FPGA_DisPattern(0, 0,0,255); 
		Delay_ms(300);
		break;
		case (16):
		FPGA_DisPattern(125, 0,0,0); 
		Delay_ms(300);
		break; 
		case (17): //dot check 
		FPGA_DisPattern(24, 127,0,0); 
		Delay_ms(300);
		break;
		case (18): //pic
			if (Pic_Load == ERROR)
			{
				FPGA_Info_Visible(INFO_STR);
				FPGA_Info_Set((uint8_t *)"LOAD PIC FAIL.");
			}
			printf("\r\n Show Pic.\r\n");
			FPGA_DisPicture(0);	//picture
			Delay_ms(300);
		break;
		case (19):  
		LEDA_DIM();
		FPGA_DisPattern(0, 255,255,255); 
		Delay_ms(300);
		SPEC_LEDA_MIN = SPEC_MIN_LEDA_DIM;
		SPEC_LEDA_MAX = SPEC_MAX_LEDA_DIM;
		break;
		default: 
		FPGA_DisPattern(0, 0, 0, 0); 
		break;  
		}

}
/*********************************************************************************
* Function: Test_ESD
* Description: ESD test
* Input: none
* Output: none
* Return: none
* Call: external
*/

void Test_ESD(void)
{
	ESD_Visual_Check();
	ESD_Fail_Recover();
}
