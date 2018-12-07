
#include "include.h"

uint8_t OTP_TIMES = 0;			    // OTP次数
uint16_t vcom_best = 0x0028;		    // 最佳VCOM		
uint8_t MAIN_PORT = PORT1;	  	// 主MIPI port(作为回读的数据口)	 WQXGA:PORT0 	HF/FHD:PORT1

unsigned short GAMMA_InitCode[]=
{
  //=======Gamma Code  Begin======//

     //?????????Gamma code

 //=======Gamma Code   End======//

    0xF00   //end of initialization
};

/*********************************************************************************
* Function: PreGamma_Set
* Description: transfer the info of x y before adjust the white point
* Input: none
* Output: none
* Return: none
* Call: external
*/
void PreGamma_Set(void)
{
	//add your code according to your project

}
/*********************************************************************************
* Function: DriverIC_Reset
* Description: DDIC reset
* Input: none
* Output: none
* Return: none
* Call: external
*/
 void DriverIC_Reset(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
 	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
 	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	 GPIO_InitStructure.GPIO_Pin = TEST24_PIN; //CONNECTOR2 / TP_RST
 	 GPIO_Init(TEST24_GPIO_PORT, &GPIO_InitStructure);	
	 
	 printf("\r\nDriver IC reset...\r\n");
	 GPIO_ResetBits(LCD_nRST_GPIO_PORT, LCD_nRST_PIN);
	 Delay_ms(1);	 	 
	 GPIO_ResetBits(TEST24_GPIO_PORT, TEST24_PIN);//TP reset pin
	 Delay_ms(10);//typical 10mS 
	 GPIO_SetBits(TEST24_GPIO_PORT, TEST24_PIN);  //TP Set pin	 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
 	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	 GPIO_InitStructure.GPIO_Pin = TEST24_PIN; //CONNECTOR2 / TP_RST
 	 GPIO_Init(TEST24_GPIO_PORT, &GPIO_InitStructure);	
	 Delay_ms(1);	 
	 GPIO_SetBits(LCD_nRST_GPIO_PORT, LCD_nRST_PIN);

	 Delay_ms(100);//2018-6-1 change 20 --100 to cover flash mode probabilistic download f/w error
 }
/*********************************************************************************
* Function: DriverIC_Reset
* Description: DDIC reset
* Input: none
* Output: none
* Return: none
* Call: external
*/
 void DriverIC_RST_TP(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
 	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	 GPIO_InitStructure.GPIO_Pin = TEST24_PIN; //CONNECTOR2 / TP_RST
 	 GPIO_Init(TEST24_GPIO_PORT, &GPIO_InitStructure);	
	 GPIO_ResetBits(TEST24_GPIO_PORT, TEST24_PIN);//TP reset pin
	 Delay_ms(10);//typical 10mS 
	 GPIO_SetBits(TEST24_GPIO_PORT, TEST24_PIN);  //TP reset pin
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
 	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	 GPIO_InitStructure.GPIO_Pin = TEST24_PIN; //CONNECTOR2 / TP_RST
 	 GPIO_Init(TEST24_GPIO_PORT, &GPIO_InitStructure);	
	 Delay_ms(50);
 } 
/*********************************************************************************
* Function: LCD_SoftReset
* Description: DDIC soft reset
* Input: none
* Output: none
* Return: none
* Call: external
*/
void LCD_SoftReset(void)
{
	printf("\r\nDriver IC solfware reset...\r\n");
	SSD_B7 |= SSD_CFGR_DCS;
	SSD_B7 &= ~SSD_CFGR_REN;
	WriteSSDReg((PORT0 | PORT1), SSD_CFGR, SSD_B7);
	printf("SSD_B7 = 0x%04x\r\n", SSD_B7);

	WriteSSDReg((PORT0 | PORT1), 0xBC, 0x0001);
	WriteSSDReg((PORT0 | PORT1), 0xBF, 0x0001);
	Delay_ms(150);	 //delay more than 120ms
}

/*********************************************************************************
* Function: LCD_SleepIn
* Description: DDIC sleep in and display off
* Input: none
* Output: none
* Return: none
* Call: external
*/
void LCD_SleepIn(void)
{	
	printf("\r\nDriver IC display off then sleep in...\r\n");
	SSD_B7 |= SSD_CFGR_DCS;
	SSD_B7 &= ~SSD_CFGR_REN;
	WriteSSDReg((PORT0 | PORT1), SSD_CFGR, SSD_B7);
	printf("SSD_B7 = 0x%04x\r\n", SSD_B7);
	WriteSSDReg((PORT0 | PORT1), 0xBC, 0x0001);
	WriteSSDReg((PORT0 | PORT1), 0xBF, 0x0028);
	WriteSSDReg((PORT0 | PORT1), 0xBF, 0x0010);
	Delay_ms(120);	  //delay more than 120ms
}

/*********************************************************************************
* Function: LCD_SleepOut
* Description: DDIC sleep out and display on
* Input: none
* Output: none
* Return: none
* Call: external
*/
void LCD_SleepOut(void)
{
	printf("\r\nDriver IC display on then sleep out...\r\n");
	SSD_B7 |= SSD_CFGR_DCS;
	SSD_B7 &= ~SSD_CFGR_REN;
	WriteSSDReg((PORT0 | PORT1), SSD_CFGR, SSD_B7);
	printf("SSD_B7 = 0x%04x\r\n", SSD_B7);
	WriteSSDReg((PORT0 | PORT1), 0xBC, 0x0001);
	WriteSSDReg((PORT0 | PORT1), 0xBF, 0x0011);
	Delay_ms(120);	  //delay more than 120ms
	WriteSSDReg((PORT0 | PORT1), 0xBF, 0x0029);	
}
/*********************************************************************************
* Function: LCD_PWM
* Description: BLU PWM duty setting
* Input: -data, PWM duty(0X00~0XFFF)
* Output: none
* Return: none
* Call: external
*/

void LCD_PWM(uint16_t data)
{
	uint8_t wtBuf[2];

	PWM_DUTY = (data*PWM_T/0xFF);
	printf("\r\nPWM_DUTY=%d\r\n", PWM_DUTY);	
	wtBuf[0] = data & 0x00FF;

	
  MIPI_DCS_Write((PORT0 | PORT1), 0x51, 1, wtBuf);  
	wtBuf[0] = 0x24;//2C-24
	MIPI_DCS_Write((PORT0 | PORT1), 0x53, 1, wtBuf);
	wtBuf[0] = 0x00;
	MIPI_DCS_Write((PORT0 | PORT1), 0x55, 1, wtBuf);
	Delay_ms(10);
}
/*********************************************************************************
* Function: LEDA_DIM()
* Description: BLU PWM duty setting for low current test
* Input: -data, PWM duty(12bit duty)
* Output: none
* Return: none
* Call: external
*/

void LEDA_DIM()
{
	LCD_PWM(0x0D);
}
/*********************************************************************************
 * 函数名：LCD_LitSquence
 * 描述  ：正扫
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */		
void LCD_LitSquence(void)
{	
	LCD_SleepOut();
	LCD_HSMode();
	#ifdef CMD_MODE
	LCD_VideoMode_OFF();
	#else
	LCD_VideoMode_ON();
	#endif
	LCD_PWM(0xff);
}

/*********************************************************************************
 * 函数名：ScanForward
 * 描述  ：正扫
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */											
void ScanForward(void)
{
	unsigned char wtBuf[1];
	wtBuf[0] = 0x00;
	MIPI_DCS_Write((PORT0 | PORT1), 0x36, 1, wtBuf);	
}

/*********************************************************************************
 * 函数名：ScanBackward
 * 描述  ：反扫
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */
void ScanBackward(void)
{
	unsigned char wtBuf[1];
		
	wtBuf[0] = 0x80;		//Bit D7 Page Address Order 1:Bottom to to	
	MIPI_DCS_Write((PORT0 | PORT1), 0x36, 1, wtBuf);	
}

/*********************************************************************************
 * 函数名：Vcom_Set
 * 描述  ：设置VCOM
 * 输入  ：-VCOM值 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */
void VCOM_Set(unsigned short vcom)
{
	unsigned char wtBuf[9];
	wtBuf[0] = 0x04; //0x03 For TD4320 vcom wirte protect OFF
	MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, wtBuf);	
	
	wtBuf[0] = 0x03; //0x03 For TD4320 vcom wirte protect OFF
	wtBuf[1] = 0x3F; //05-3f
	wtBuf[2] = 0x00;
	wtBuf[3] = 0x00;
	MIPI_GEN_Write((PORT0 | PORT1), 0xE5, 4, wtBuf);	
	wtBuf[0] = vcom>>8;
	wtBuf[1] = vcom;
	wtBuf[2] = vcom>>8;
	wtBuf[3] = vcom;
//	wtBuf[4] = 0x02;
//	wtBuf[5] = 0xDC; 
//	wtBuf[6] = 0x02;
//	wtBuf[7] = 0xDC;
	MIPI_GEN_Write((PORT0 | PORT1), 0xD5, 4, wtBuf);
}



/*********************************************************************************
 * 函数名：VCOM_Read
 * 描述  ：回读VCOM
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：VCOM值
 * 调用  ：外部调用
 */
unsigned short VCOM_Read(void)
{
	unsigned char rdBuf[8];

	MIPI_GEN_Read(MAIN_PORT, 0xD5, 8, rdBuf);

	return ((rdBuf[0]<<8)+rdBuf[1]);
}

/*********************************************************************************
 * 函数名：OTPTimes_Read
 * 描述  ：回读OTP次数
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：OTP次数
 * 调用  ：外部调用
 */
unsigned char OTPTimes_Read(void)
{
	unsigned char rdBuf[6];

	MIPI_DCS_Read(MAIN_PORT, 0xFB, 3, rdBuf);

	return (0x0F&rdBuf[0]);
}

/*********************************************************************************
 * 函数名：ID_Chroma_OTP
 * 描述  ：OTP ID, chroma...
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */
void ID_Chroma_OTP(void)
{
//If need to OTP ID, please uncomment the following code	
//write ID(together with Vcom) --Customer information write 	

	//unsigned char buf[6];

	 
//	buf[0] = ID1;
//		MIPI_GEN_Write((PORT0 | PORT1), 0xDA, 1, buf); 
//	buf[0] = ID2;
//		MIPI_GEN_Write((PORT0 | PORT1), 0xDB, 1, buf); 
//	buf[0] = ID3;
//		MIPI_GEN_Write((PORT0 | PORT1), 0xDC, 1, buf); 
//	 
//	buf[0] = 0x11;
//  .......
//	buf[5] = 0x66;
//	MIPI_GEN_Write((PORT0 | PORT1), 0xA1, 6, buf); //The command returns information from the display module 
	 
//RBF is huawei reserve register
//	buf[0] = 0xBF; //target register to be written
//	buf[1] = 0x40; //parameter No.0x40
//	buf[2] = vaule;//write value
//	MIPI_GEN_Write((PORT0 | PORT1), 0xF0, 3, buf); 
	
}

/*********************************************************************************
 * 函数名：OTPSequence
 * 描述  ：OTP流程
 * 输入  ：无 
 * 输出  ：无
 * 返回  ：OTP执行结果
 * 调用  ：外部调用
 *	------------------------------------------------------------------------------
 * 	0xE0寄存器
 *		-第四个参数bit6：NVMFTT指示 OTP操作 是否完成(0->1: start squence	1->0: squence finish)
 *		-第五个参数bit0：NVMVFFLGER指示 erase 是否成功
 *  	-第五个参数bit1：NVMVFFLGWR指示 write 是否成功
 *	------------------------------------------------------------------------------
 */
 ErrorStatus OTPSequence(void)
{
		ErrorStatus otpResult;
		uint8_t buf[7],i;
		unsigned char gamma_flag = 1,vcom_flag = 1,timing_flag = 1;	 
		printf("\r\n==============OTP Sequence Start================\r\n");	
	//Enter sleep mode	 
		LCD_SleepIn();
		LCD_VideoMode_OFF();
		LCD_LPMode();
	 
		buf[0] = 0x04;
		MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, buf); 	
/************************************gamma otp start**********************************/
	#ifdef NO_FLASH_MODE
	if(OTP_TIMES<2)
	#else
	if(OTP_TIMES<1)
	#endif
	{	
		buf[0] = 0x1D;
		MIPI_GEN_Write((PORT0 | PORT1), 0xF4, 1, buf); //Per Panel Tuning programming
		Delay_ms(500);
	 
		buf[0] = 0x04;
		MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, buf); 
//		Delay_ms(10);

		MIPI_GEN_Read(MAIN_PORT, 0xFB, 3, buf); // Per Panel tuning
	i = 3;
	while(i--)
		printf("buf[%d]= %xh\r\n",i,buf[i]);
	if((buf[2]&0xF0) == 0x30 ) 			  // programming succeeded
	{
		printf("\r\n========Gamma programming succeeded==========\r\n");
		gamma_flag = 1;
	}
	 else if((buf[2]&0xF0) == 0x00 ) //programming failed
	{
		gamma_flag = 0;
		printf("\r\n=Gamma programming failed due to flash related issues=\r\n");
	}
	 else if(buf[2]&0x80)						 //programming failed
	 {
		gamma_flag = 0;
		printf("programming executes over the maximum number of writable registers,OTP quite!\r\n");
	 }
 }
/************************************gamma otp end**********************************/
/************************************vcom&IC otp start**********************************/
 ID_Chroma_OTP();
//VCOM/ID/Chroma OTP start===========
	buf[0] = 0x1B;
	#ifdef NO_FLASH_MODE
	buf[1] = 0x4C;//HDL mode should set 0x4C,IIC mode set 0x00;
	#else
	buf[1] = 0x00;
	#endif
	MIPI_GEN_Write((PORT0 | PORT1), 0xF5, 2, buf); 
	Delay_ms(300);
		MIPI_GEN_Read(MAIN_PORT, 0xFB, 3, buf); // ANSIC configuration
	i = 3;
	while(i--)
		printf("buf[%d]= %xh\r\n",i,buf[i]);
	if((buf[0]&0xF0) == 0x30 ) 			  // programming succeeded
	{
		printf("\r\n========ANSIC configuration programming succeeded==========\r\n");
		vcom_flag = 1;
	}
	 else if((buf[0]&0xF0) == 0x00 ) //programming failed
	{
		vcom_flag = 0;
		printf("\r\n=ANSIC configuration programming failed due to flash related issues=\r\n");
	}
	 else if(buf[0]&0x80)						 //programming failed
	 {
		vcom_flag = 0;
		printf("ANSIC configuration programming executes over the maximum number of writable registers,OTP quite!\r\n");
	 }
/************************************vcom&IC otp end**********************************/
/************************************timing otp start**********************************/	 
	#ifdef NO_FLASH_MODE
	if(OTP_TIMES<2)
	#else
	if(OTP_TIMES<1)
	#endif
{
//otp timing
		SSD_B7 = 0x0510 ;
		WriteSSDReg(MAIN_PORT, 0xB7, SSD_B7);
//		Delay_ms(10);
		buf[0] = 0x00;
		MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, buf); 
//		Delay_ms(10);

		buf[0] = 0x1C;
		MIPI_GEN_Write((PORT0 | PORT1), 0xF4, 1, buf);//OTP run!
		Delay_ms(2000);																

		MIPI_GEN_Read(MAIN_PORT, 0xFB, 3, buf);
		i = 3;
	while(i--)
		printf("buf[%d]= %xh\r\n",i,buf[i]);
	if((buf[1]&0xF0) == 0x30 ) 			 
	{
		printf("\r\n========Dispaly programming succeeded==========\r\n");
		timing_flag = 1;
	}
	 else if((buf[1]&0xF0) == 0x00 ) 
	{
		timing_flag = 0;
		printf("\r\n=Dispaly programming failed due to flash related issues=\r\n");
	}
	 else if(buf[1]&0x80)						 
	 {
		 timing_flag = 0;
		printf("Dispaly profile programming executes over the maximum number of writable registers,OTP quite!\r\n");
	 }
 }
/************************************timing otp end**********************************/	 	 
	
	//--------OTP check-----------------//

	if(gamma_flag&&timing_flag&&vcom_flag)		//check whether OTP complete
	 {
		printf("OTP Success!\r\n");
		otpResult = SUCCESS;
	 }
	 else 
	 {
		printf("OTP NG!\r\n");
		otpResult = ERROR;
	 }
	//--------OTP finish-----------------//
	DriverIC_Reset();
	MIPI_Reset();
	IC_Init(SSDInitCode);
	 if(otpResult)
	IC_Init(ET2_InitCode);
	 else
	IC_Init(ET1_InitCode);
	LCD_PWM(0xFF);
	LCD_SleepOut();
//	Delay_ms(50); 
	LCD_VideoMode_ON();
	LCD_HSMode();	
	
	return 	otpResult;
}
/*********************************************************************************
 * 函数名：OTP_HDL_MODE
 * 描述  ：OTP HDL流程
 * 输入  ：无 
 * 输出  ：none
 * 返回  ：OTP执行结果
 * 调用  ：外部调用
 *	------------------------------------------------------------------------------
*/
ErrorStatus OTP_HDL_MODE()
{
		ErrorStatus otpResult = ERROR;
		uint8_t buf[7],i;
		buf[0] = 0x04;
		MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, buf); 	
		Delay_ms(10);
		MIPI_GEN_Read(MAIN_PORT, 0xFB, 1, buf);
		if((buf[0]&0x0F)!= 0x00){
			otpResult = SUCCESS;
			printf("NEED NOT OTP HDL!\r\n");
			return otpResult;
		}
		printf("\r\n/*==============OTP HDL Sequence Begin================*/\r\n");	
 
	//Enter sleep mode	 
		LCD_SleepIn();
		LCD_VideoMode_OFF();
		LCD_LPMode();
	 
		buf[0] = 0x04;
		MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, buf); 

		buf[0] = 0x1B;
		buf[1] = 0x4C;	
		MIPI_GEN_Write((PORT0 | PORT1), 0xF5, 2, buf); //write boot config = 0x4C into ASIC configuration
		Delay_ms(300);
	 
		MIPI_GEN_Read(MAIN_PORT, 0xFB, 1, buf);
		if((buf[0]&0x30)== 0x30){
			otpResult = SUCCESS;
			printf("OTP HDL mode success!\r\n");
		}
		else{
			printf("OTP HDL mode Fail!(ERROR CODE %2X)\r\n",buf[0]);			
		}
	
		buf[0] = 0x03;
		MIPI_GEN_Write((PORT0 | PORT1), 0xB0, 1, buf);// 
		printf("\r\n/*==============OTP HDL Sequence End================*/\r\n");		
		//reset &light up lcd
		DriverIC_Reset();
		if (TEST_MODE == TEST_MODE_RA)
		{
				IC_Init(RA_InitCode);
		}
		else
		{
				IC_Init(ET1_InitCode);		
				LCD_LitSquence();		
		}		
		//reset &light up lcd		
		return otpResult;
}

/*********************************************************************************
* Function: LCMPower_ON
* Description: power on timing, low active
* Input: none
* Output: none
* Return: none
* Call: external
*/
void LCMPower_ON(void)
{	
 	POWER_IOVCC_Reset();
	Delay_ms(3);
 	POWER_VCI_Reset();
	Delay_ms(3);
	POWER_VSP_Reset();	
	Delay_ms(3);
	POWER_VSN_Reset();
	Delay_ms(3);
	
	printf("\r\nLCMPower_ON...\r\n");
}

/*********************************************************************************
* Function: LCMPower_OFF
* Description: power off timing, low active
* Input: none
* Output: none
* Return: none
* Call: external
*/
void LCMPower_OFF(void)
{	
 	LCD_PWM(0x0000);
	Delay_ms(1); 
	POWER_VSN_Set();
	Delay_ms(1);
	POWER_VSP_Set();
	Delay_ms(1);	
 	POWER_VCI_Set();
	Delay_ms(3);
	POWER_IOVCC_Set();
	
	printf("\r\nLCMPower_OFF...\r\n");
}
