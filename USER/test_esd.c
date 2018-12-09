#include "include.h"

//void ESD_Visual_Check(void) 
//{ 
//		TOTAL_DIS_NUM = 13; 
//		switch (DIS_NUM) 
//		{ 		
//		case (0): //waku
//		FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
//		FPGA_DisPattern(79, 0, 0x77, 0x41); 
//		break; 	
//		case (1): //dark
//		FPGA_Info_Visible(INFO_NONE); 
//		FPGA_DisPattern(0, 0,0,0); 
//		break; 
//		case (2): //W 
//		FPGA_DisPattern(0, 255,255, 255); 
//		break; 
//		case (3): //R 
//		FPGA_DisPattern(0, 255, 0, 0); 
//		break; 
//		case (4): //G 
//		FPGA_DisPattern(0, 0,255, 0); 
//		break; 
//		case (5): //B 
//		FPGA_DisPattern(0, 0,0,255); 
//		break; 
//		case (6): //L64 
//		FPGA_DisPattern(0, 64,64,64); 
//		break; 
//		case (7): //gray127 
//		FPGA_DisPattern(0, 127,127,127); 
//		break; 
//		case (8): //crosstalk
//		FPGA_DisPattern(7, 127,127,127); 
//		break; 
//		case (9): //crosstalk
//		FPGA_DisPattern(1, 127,127,127); 
//		break; 
//		case (10): //Flicker
//		FPGA_DisPattern(22, 127, 0, 0);	
//		break; 
//		case (11): //WRGB transtion
//		FPGA_DisPattern(90, 0,0,0); 
//		break; 
//		case (12): //dot check 
//		FPGA_DisPattern(24, 127,0,0); 
////		break; 
////		case (13): //dot check 
////		FPGA_DisPattern(24, 255,0,0); 
////		break; 
////		case (14): //pixel check 
////		FPGA_DisPattern(23, 127,0,0); 
////		break;
////		case (15): //pixel check 
////		FPGA_DisPattern(23, 255,0,0); 
//		FPGA_Info_Visible(INFO_NONE); 
//		break; 
//		default: 
//		FPGA_DisPattern(0, 0, 0, 0); 
//		break;  
//		}
//}

void ESD_Visual_Check(void) 
{ 
		TOTAL_DIS_NUM = 21; 
		switch (DIS_NUM) 
		{ 		
		case (0): //waku
		ScanForward();
		FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
		FPGA_DisPattern(79, 0, 255, 65);	
		break; 	
		case (1): //black+rgbw
		FPGA_Info_Visible(INFO_NONE); 
		FPGA_DisPattern(82, 0, 0, 0);//Black+R100-G70-B170-W70 , CH1-FPGA_DisPattern(82, 0, 0, 0)
		break; 
		case (2): //L64 
		ScanForward();
		FPGA_Info_Visible(INFO_RGBVAL);
		FPGA_DisPattern(0, 64,64,64); 
		Delay_ms(ET_DLY_LOCK * 2700); 
		break; 
		case (3): //gray127 
		ScanBackward();
		FPGA_Info_Visible(INFO_RGBVAL);
		FPGA_DisPattern(0, 127,127,127); 
		Delay_ms(ET_DLY_LOCK * 1700); 
		break; 
		case (4): //W 
		ScanForward();
		FPGA_Info_Visible(INFO_NONE); 
		FPGA_DisPattern(0, 255,255, 255); 
		if (Pic_Load_Finish == SET || PIC_Load_BMP_ET((uint8_t *)"0.bmp") == ERROR)
		{
			Delay_ms(ET_DLY_LOCK * 2700); 
		}
		break; 	
		case (5): // 
		FPGA_DisPattern(18, 255, 0, 0); 
		break; 	
		case (6): // 
		FPGA_DisPattern(17, 255, 0, 0); 
		break; 		
		case (7): //Flicker
		FPGA_DisPattern(22, 127, 0, 0);	
		break; 
		case (8): //crosstalk
		FPGA_DisPattern(1, 127,127,127); 
		break; 
		case (9): //crosstalk
		FPGA_DisPattern(7, 127,127,127); 
		break; 		
		case (10): 
		FPGA_DisPattern(133, 255, 0, 0); 	//HUAWEI TP
		break;
		case (11): 
		FPGA_DisPattern(136, 255, 0, 0); 	//HUAWEI S1
		break;
		case (12): 
		FPGA_DisPattern(137, 255, 0, 0); 	//HUAWEI S1
		break;
		case (13): //R 
		FPGA_DisPattern(0, 255, 0, 0); 
		break; 
		case (14): //G 
		FPGA_DisPattern(0, 0,255, 0); 
		break; 
		case (15): //B 
		FPGA_DisPattern(0, 0,0,255); 
		break; 
		case (16): //WRGB transtion
		FPGA_DisPattern(92, 0,0,0); 
		break; 
		case (17): //dot check 
		FPGA_DisPattern(24, 127,0,0);  
		break; 
		case (18): //picture
		LCD_PWM(0x0FE1);//POWER-PET12-06£¬E1=22mA
		FPGA_DisPicture(0);	//picture
		break; 
		case (19): 
			LEDA_DIM();
			FPGA_DisPattern(0, 255, 255, 255);	//DIM (low current white)
		break;
		case (20): 
			FPGA_DisPattern(0, 0, 0, 0);
			FPGA_Info_Visible(INFO_NONE);
			KEY_SLEEPIN(); 	
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
