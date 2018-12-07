#include "include.h"


void OD_Visual_Check()
{
		TOTAL_DIS_NUM = 2;	
 	switch (DIS_NUM) 
	{
		case (0): 		
		  FPGA_DisPicture(0);
			break;
		case (1): 
			FPGA_DisPicture(1);
			break;	
		default: 
			FPGA_DisPattern(0, 0, 0, 0); 
			break;
	}

}
/*********************************************************************************
* Function: Test_OD
* Description: OD test
* Input: none
* Output: none
* Return: none
* Call: external
*/
void Test_OD(void)
{
	OD_Visual_Check();
}
