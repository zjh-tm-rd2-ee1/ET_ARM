#include "include.h"

/*********************************************************************************
* Function: Test_ET1
* Description: ET1 test
* Input: none
* Output: none
* Return: none
* Call: external
*/
//FRESULT frs;
//TCHAR *path = (TCHAR*)"0:\\";	
//DIR my_dir;
//FATFS txtfs;
//FIL txtfsrc; 
//static FILINFO MyInfo;
//char Content[1024]={0};
//WORD fileType;
//UINT* br;

void Test_ET1(void){	
 	TOTAL_DIS_NUM = 6;	
 	switch (DIS_NUM) 
	{
		case (0):			
			FPGA_Info_Visible(INFO_VERSION | INFO_PROJECT_NO);
			ScanForward();	
 			FPGA_DisPattern(24, 127, 127, 127);	//dotcheck 
			break;
		case (1): 	
			FPGA_Info_Visible(INFO_NONE);
			ScanForward();
 			FPGA_DisPattern(82, 0, 0, 0);	//Black+R100-G70-B170-W70 , CH1-FPGA_DisPattern(82, 0, 0, 0)
			Delay_ms(ET_DLY_LOCK * 3700); 
			break;
		case (2): 
			FPGA_Info_Visible(INFO_RGBVAL);
			ScanBackward();
			FPGA_DisPattern(0, 127, 127, 127);	//gray
			Delay_ms(ET_DLY_LOCK * 2700);
			break;
		case (3): 
			FPGA_Info_Visible(INFO_NONE);
			ScanForward();
			FPGA_DisPattern(0, 255, 255, 255);	//white
		  Delay_ms(ET_DLY_LOCK * 2700); 
			break;
		case (4): 
			FPGA_DisPattern(127, 255, 255, 255);	//RGB
			break;
		case (5): 
			FPGA_DisPattern(0, 0, 0, 0);
			KEY_SLEEPIN(); 
		  Flag_Test_Current = RESET;				  //DO NOT test the current!
			break;
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}
	Delay_ms(ET_DLY_LOCK * 300);
 }



// // DJ code
//void Test_ET1(void)
//{
//	 TOTAL_DIS_NUM = 6;     
// 
//	 switch (DIS_NUM)
//		 {
//			 case (0):
//								FPGA_DisPattern(129, 0, 2, 155);
//								FPGA_Info_Visible(INFO_VERSION|INFO_PROJECT_NO);
//								break;
//			 case (1):
//								FPGA_DisPattern(0, 255, 255, 255);
//								FPGA_Info_Visible(INFO_NONE);
//								break;
//			 case (2):
//								FPGA_DisPattern(0, 255, 0, 0);
//								break;
//			 case (3):
//								FPGA_DisPattern(0, 0, 255, 0);
//								break;
//			 case (4):
//								FPGA_DisPattern(0, 0, 0, 255);
//								break;
//			 case (5):
//								FPGA_DisPattern(0, 0, 0, 0);
//								FPGA_Info_Visible(INFO_NONE);
//	//            KEY_SLEEPIN();
//								break;
//			 default:
//								FPGA_DisPattern(0, 0, 0, 0);
//								break;
//		 }
//		 Delay_ms(ET_DLY_LOCK * 300);
//}
