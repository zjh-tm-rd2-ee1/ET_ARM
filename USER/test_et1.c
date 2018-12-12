#include "include.h"

/*********************************************************************************
* Function: Test_ET1
* Description: ET1 test
* Input: none
* Output: none
* Return: none
* Call: external
*/
// void Test_ET1(void)
// {
// 	TOTAL_DIS_NUM = 5;	
// 	switch (DIS_NUM) 
//	{
////		case (0): 
////			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
////			FPGA_DisPattern(24, 127, 127, 127);	//dotcheck
////			break;
////		case (1):	
////			FPGA_Info_Visible(INFO_NONE);
//		case (0):			
//			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
//			ScanForward();	
// 			FPGA_DisPattern(0, 0, 0, 0);	//black
//			Delay_ms(ET_DLY_LOCK * 2700); 
//			break;
//		case (1): 	
//			FPGA_Info_Visible(INFO_RGBVAL);
//			ScanBackward();
// 			FPGA_DisPattern(0, 127, 127, 127);	//gray
//			Delay_ms(ET_DLY_LOCK * 3700); 
//			break;
//		case (2): 
//			FPGA_Info_Visible(INFO_NONE);
//			ScanForward();
//			FPGA_DisPattern(0, 255, 255, 255);	//white
//		  Delay_ms(ET_DLY_LOCK * 700); 
//			break;
//		case (3): 
//			FPGA_DisPattern(127, 255, 255, 255);	//RGB
//			break;
//		case (4): 
//			FPGA_DisPattern(0, 0, 0, 0);
//			KEY_SLEEPIN(); 
//		  Flag_Test_Current = RESET;				  //DO NOT test the current!
//			break;
//		default: 
//			FPGA_DisPattern(0, 0, 0, 0); 
//			break;
//	}
//	Delay_ms(ET_DLY_LOCK * 300);
// }









// void Test_ET1(void)      //项目验证报告10个画面
// {
// 	TOTAL_DIS_NUM = 11;	
// 	switch (DIS_NUM) 
//	{
//		case (0): 
//			LEDA_NORM();
//			FPGA_Info_Visible(INFO_NONE);
//			FPGA_DisPattern(0, 255, 0, 0); 	//R
//			break;
//		case (1): 	
//			FPGA_DisPattern(0, 0, 255, 0); 	//G
//			break;
//		case (2): 
//			FPGA_DisPattern(0, 0, 0, 255); 	//B
//			break;
//		case (3): 
//			FPGA_DisPattern(0, 0, 0, 0); //black
//			break;
//		case (4): 
//			FPGA_DisPattern(0, 255, 255, 255);	//White
//			break;
//		case (5): 
//			FPGA_DisPattern(50, 0, 0, 0);    //H-Color Bar
//			break;
//			case (6): 
//			FPGA_DisPattern(22, 127, 127, 127);	//flicker
//			break;
//			case (7): 
//			FPGA_DisPattern(69, 0, 255, 0);    //1*1 Bar
//			if (Pic_Load_Finish == SET || PIC_Load_BMP_ET((uint8_t *)"0.bmp") == ERROR)
//			{
//				Delay_ms(ET_DLY_LOCK * 2700); 
//			}
//			break;
//			case (8):
//			if (Pic_Load == ERROR)
//			{
//				FPGA_Info_Visible(INFO_STR);
//				FPGA_Info_Set((uint8_t *)"LOAD PIC FAIL.");
//			}
//			FPGA_DisPicture(0);	//picture
//			break;
//			case (9): 
//				LEDA_NORM();
//			FPGA_DisPattern(24, 127, 127, 127);	//dotcheck
//			break;
//			case (10): 
//		  FPGA_Info_Visible(INFO_NONE);
//			LEDA_DIM();
//			ScanForward();
//			FPGA_DisPattern(0, 255, 255, 255);	//DIM (low current white)
//			Delay_ms(100);		  
//		  SPEC_LEDA_MIN = SPEC_MIN_LEDA_DIM;
//		  SPEC_LEDA_MAX	= SPEC_MAX_LEDA_DIM;
//			break;
//		default: 
//			FPGA_DisPattern(0, 0, 0, 0); 
//			break;
//	}
//	Delay_ms(ET_DLY_LOCK * 300);
// }













 void Test_ET1(void)
 {
 	TOTAL_DIS_NUM = 3;	
 	switch (DIS_NUM) 
	{
 		case (0):
			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
		  FPGA_DisPattern(0, 0, 0, 0);
		  break;
		case (1):
			FPGA_Info_Visible(INFO_NONE);			
 		  FPGA_DisPattern(112, 0, 53, 107);	//20*20 chessboard		
 			break;
 		case (2): 
			FPGA_Info_Visible(INFO_RGBVAL);
 		  FPGA_DisPattern(0, 60, 60, 60);//gray60
 			break;
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}
	Delay_ms(ET_DLY_LOCK * 300);
 }

