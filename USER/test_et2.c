#include "include.h"

/*********************************************************************************
* Function: Test_ET2
* Description: ET2 test
* Input: none
* Output: none
* Return: none
* Call: external
*/
// void Test_ET2(void)
// {
// 	TOTAL_DIS_NUM = 12;
// 	switch (DIS_NUM) 
//	{
//		case (0): 
//			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
//			FPGA_DisPattern(81, 127, 0x77, 0x41);	//waku+black
//			ScanForward();	
//			break;
//		case (1): 			
//			FPGA_Info_Visible(INFO_NONE);
//		  ScanForward();
//		  FPGA_DisPattern(0, 0, 0, 0);			//black
//		  Delay_ms(ET_DLY_LOCK * 2700); 
//			break;
//		case (2): 
//		  LEDA_NORM();
//			FPGA_Info_Visible(INFO_RGBVAL);
//			ScanBackward();
//			FPGA_DisPattern(0, 127, 127, 127);	//gray127
//			Delay_ms(ET_DLY_LOCK * 2700); 
//			break;
//		case (3): 
//		  FPGA_Info_Visible(INFO_NONE);
//			LEDA_DIM();
//			ScanForward();
//			FPGA_DisPattern(0, 255, 255, 255);	//DIM (low current white)
//			Delay_ms(100);		  
//		  SPEC_LEDA_MIN = SPEC_MIN_LEDA_DIM;
//		  SPEC_LEDA_MAX	= SPEC_MAX_LEDA_DIM;
//			break;
//		case (4): 
//			LEDA_NORM();
//			FPGA_DisPattern(0, 255, 255, 255);	//white
//			if (Pic_Load_Finish == SET || PIC_Load_BMP_ET((uint8_t *)"0.bmp") == ERROR)
//			{
//				Delay_ms(ET_DLY_LOCK * 2700); 
//			}
//			break;

// }




 void Test_ET2(void)      // OQC2Í¼°¸
 {
 	TOTAL_DIS_NUM = 5;
 	switch (DIS_NUM) 
	{
		case (0): 
         FPGA_DisPicture(0);
			break;
		case (1): 			
FPGA_DisPicture(1);
			break;
		case (2): 
FPGA_DisPicture(2);
			break;
		case (3): 
FPGA_DisPicture(3);
			break;
		case (4): 
FPGA_DisPicture(4);
			break;
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}
 }
