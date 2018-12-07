#include "include.h"

uint8_t OTP_TIMES = 0;          // OTP次数
uint16_t vcom_best = 0x010E;    // 最佳VCOM
uint8_t MAIN_PORT = PORT1;

/*********************************************************************************
 * 函数名：ID_OTP
 * 描述  ：//---CH1 OTP Color ID , White_Lv ID , Project ID----//
 * 输入  ：/
 * 输出  ：
 * 返回  ：
 * 调用  ：外部调用
 */
void ID_OTP()
{
	 uint8_t   uc_buf[1];
	 uint16_t  a;	
		
	//--CH1 Color ID 
		SendPage(0x20);
		uc_buf[0]=ID_COLOR;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x44, 1, uc_buf);
	
	//--CH1 Project ID
	//--DP082---JHSN771100-----TL065FVXF01-00/TL065FVXF06-00/TL065FVXF07-00/TL065FVXF08-00
	//--DP102---JACK771100-----TL065FVXF02-00/TL065FVXF03-00/TL065FVXF04-00/TL065FVXF05-00
		SendPage(0x20);
		uc_buf[0]=ID_PJ1;//		
		MIPI_DCS_Write((PORT0 | PORT1), 0x23, 1, uc_buf);
	
		uc_buf[0]=ID_PJ2;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x24, 1, uc_buf);
	
		uc_buf[0]=ID_PJ3;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x25, 1, uc_buf);

		uc_buf[0]=ID_PJ4;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x26, 1, uc_buf);

		uc_buf[0]=ID_PJ5;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x27, 1, uc_buf);
		
		uc_buf[0]=ID_PJ6;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x28, 1, uc_buf);
		
		uc_buf[0]=ID_PJ7;//
		MIPI_DCS_Write((PORT0 | PORT1), 0x46, 1, uc_buf);		
	

	//CH1 White_Lv ID 
	//--Lv<380: ---NG,
	//--Lv=380: ---0000,0001;
	//--Lv=381~507: ---Lv-380；0000,0001--0111,1111;
	//--Lv=508~634: ---Lv-379； 1000,0001--1111,1111;
	//--Lv>634: ---1111,1111;
		if (GAMMAEXPERT == SET)
		{
			a=(uint16_t)(ID3 * 1.5 + 308);
			printf("white_Lv = %d\r\n",a);
			 if(a==380)
				uc_buf[0]=1;
			 else if((a>=381)&&(a<=507))
				uc_buf[0]=a-380;
			 else if((a>=508)&&(a<=634))
				uc_buf[0]=a-379;
			 else if(a>634)
				uc_buf[0]=255;

			SendPage(0x20);
			MIPI_DCS_Write((PORT0 | PORT1), 0x45, 1, uc_buf);	
		}
		else
		{
			a=(uint16_t)(chroma_Lv);
			printf("white_Lv = %d\r\n",a);
			 if(a==380)
				uc_buf[0]=1;
			 else if((a>=381)&&(a<=507))
				uc_buf[0]=a-380;
				else if((a>=508)&&(a<=634))
				uc_buf[0]=a-379;
			 else if(a>634)
				uc_buf[0]=255;
			
			SendPage(0x20);
			MIPI_DCS_Write((PORT0 | PORT1), 0x45, 1, uc_buf);	
		}
		
}

/*********************************************************************************
 * 函数名：SendPage
 * 描述  ：切页
 * 输入  ：-pageNum
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用
 */
void SendPage(unsigned char pageNum)
{
    unsigned char wtBuf[1];

    wtBuf[0] = pageNum;
    MIPI_DCS_Write((PORT0 | PORT1), 0xFF, 1, wtBuf);
    Delay_ms(5);
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

    SendPage(0x10);

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

    SendPage(0x10);

    wtBuf[0] = 0x01;
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
    unsigned char wtBuf[1];

    //using short packet
    if ((SSD_B7 & SSD_CFGR_LPE) == SSD_CFGR_LPE)
    {
        printf("\r\nMessage from VCOM_Set: SSD_B7 = 0x%04x\r\n", SSD_B7);
        SSD_B7 &= ~SSD_CFGR_LPE;
        WriteSSDReg(MAIN_PORT, SSD_CFGR, SSD_B7);
        SSD_B7 = ReadSSDReg(MAIN_PORT, SSD_CFGR);
        printf("\r\nMessage from VCOM_Set: SSD_B7 = 0x%04x\r\n", SSD_B7);
    }

    SendPage(0x20);
    wtBuf[0] = vcom & 0xff;
    MIPI_DCS_Write((PORT0 | PORT1), 0x89, 1, wtBuf);     //forward sacn vcom
    MIPI_DCS_Write((PORT0 | PORT1), 0x8A, 1, wtBuf);		 //backward sacn vcom
    MIPI_DCS_Write((PORT0 | PORT1), 0x8B, 1, wtBuf);		 //idle mode forward sacn vcom
    MIPI_DCS_Write((PORT0 | PORT1), 0x8C, 1, wtBuf);		 //idle mode backward sacn vcom
    MIPI_DCS_Write((PORT0 | PORT1), 0x8D, 1, wtBuf);	   // preset vcom
//    MIPI_DCS_Write((PORT0 | PORT1), 0x8E, 1, wtBuf);	 //30HZ
//    MIPI_DCS_Write((PORT0 | PORT1), 0x8F, 1, wtBuf);	 //15HZ
		
    wtBuf[0] = (((vcom >> 8) & 0x01) << 7);
    MIPI_DCS_Write((PORT0 | PORT1), 0x88, 1, wtBuf);

    SendPage(0x10);

    Delay_ms(10);
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
    unsigned char rdBuf[1];
    unsigned short vcom_rd = 0;

    SendPage(0x20);

    MIPI_DCS_Read(MAIN_PORT, 0x89, 1, rdBuf);
    vcom_rd = rdBuf[0];

    MIPI_DCS_Read(MAIN_PORT, 0x88, 1, rdBuf);
    vcom_rd = vcom_rd + ((rdBuf[0] & 0x80) << 1);

    SendPage(0x10);

    return vcom_rd;
}

/*********************************************************************************
 * 函数名：NVM_Flag
 * 描述  ：回读NVM_Flag
 * 输入  ：无
 * 输出  ：无
 * 返回  ：NVM_Flag
 * 调用  ：外部调用
 */
ErrorStatus NVM_Flag(void)
{
    ErrorStatus NVM_Status;
    unsigned char rdBuf[1];

    SendPage(0x20);
    MIPI_DCS_Read(MAIN_PORT, 0x47, 1, rdBuf);
    printf("\r\nThe data read from NVM_Flag47 is: 0x%02X\r\n",rdBuf[0]);

    if(rdBuf[0] == 0x01)
    {
        NVM_Status=SUCCESS;
    }
    else
    {
        NVM_Status=ERROR;
    }

    SendPage(0x10);

    return NVM_Status;
}

/*********************************************************************************
 * 函数名：CRCCheck
 * 描述  ：回读NVM_Flag
 * 输入  ：无
 * 输出  ：无
 * 返回  ：NVM_Flag
 * 调用  ：外部调用
 */
void MTP_CRC_Calc(uint8_t * readbuf)
{
    uint8_t uc_buf[1];

    SendPage(0x20);

    //enable caculating CRC
	  uc_buf[0] = 0x01;   //0x01: all registers
    MIPI_DCS_Write((PORT0 | PORT1), 0x37, 1, uc_buf);
    Delay_ms(10);

    //read CRC value
    MIPI_DCS_Read(MAIN_PORT, 0x4D, 1, uc_buf);  //CRC[31:24]
    *readbuf = uc_buf[0];

    MIPI_DCS_Read(MAIN_PORT, 0x4C, 1, uc_buf);  //CRC[23:16]
    *(readbuf+1) = uc_buf[0];

    MIPI_DCS_Read(MAIN_PORT, 0x4B, 1, uc_buf);  //CRC[15:8]
    *(readbuf+2) = uc_buf[0];

    MIPI_DCS_Read(MAIN_PORT, 0x4A, 1, uc_buf);  //CRC[7:0]
    *(readbuf+3) = uc_buf[0];

    //disable caculating CRC
    uc_buf[0] = 0x00;
    MIPI_DCS_Write((PORT0 | PORT1), 0x37, 1, uc_buf);

    SendPage(0x10);
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
    unsigned char rdBuf[1];
    unsigned char OTPTime[1];

    SendPage(0x20);

    MIPI_DCS_Read(MAIN_PORT, 0x43, 1, rdBuf);

    switch(rdBuf[0] & 0xF0)  //Return OTP Times based on Zone A (2017-3-30)
    {
        case 0x00:
            OTPTime[0]=0x00;
            break;
        case 0x10:
            OTPTime[0]=0x01;
            break;
        case 0x30:
            OTPTime[0]=0x02;
            break;
        case 0x70:
            OTPTime[0]=0x03;
            break;
        case 0xF0:
            OTPTime[0]=0x04;
            break;
        default:
            OTPTime[0]=0x00;
    }

    SendPage(0x10);

    return OTPTime[0];
}

/*********************************************************************************
 * 函数名：OTPSequence
 * 描述  ：OTP流程
 * 输入  ：无
 * 输出  ：无
 * 返回  ：OTP执行结果
 * 调用  ：外部调用
 */
ErrorStatus OTPSequence(void)
{
    ErrorStatus es_otp_rslt;
    //ErrorStatus es_reg_cmp;
    ErrorStatus es_nvm;

    uint16_t us_vcom_chk;
    uint8_t uc_buf[1];
    uint8_t uc_crc_buf[4];
    uint8_t uc_crc_buf_chk[4];
    uint8_t uc_otp_times;
    uint8_t uc_otp_times_chk;

    uc_otp_times = OTP_TIMES;
	
////		if(OTP_TIMES>0) //防止其他代码OTP
//		{
//			 DriverIC_Reset();
//			IC_Init(ET2_InitCode);
//			VCOM_Set(vcom_best);
//		}
		
	
		//---OTP ID---WWP-20180428----//
		ID_OTP(); //---CH1 OTP Color ID , White_Lv ID , Project ID----//
			 

		//TP turn off
		SendPage(0xE0);  //CMD3	
		uc_buf[0]=0x01;
    		MIPI_DCS_Write((PORT0 | PORT1), 0xFB, 1, uc_buf); 
		uc_buf[0]=0xB1;
    		MIPI_DCS_Write((PORT0 | PORT1), 0x54, 1, uc_buf);  

		SendPage(0x10);
    //display off
    LCD_DisplayOff();
    Delay_ms(20);

    //stop sending video
    LCD_VideoMode_OFF();
    Delay_ms(20);

    //enter low power mode
    LCD_LPMode();
    Delay_ms(200);

    //read all register value and check
    //printf("\r\n--------Message from OTPSequence(): Before MTP flow, IC register read back check begin...\r\n");
    //es_reg_cmp = ICReg_chk(ET1_InitCode);
    //printf("\r\n--------Message from OTPSequence(): Before MTP flow, IC register read back check end.\r\n");

    //read OTP CRC registers
    MTP_CRC_Calc(uc_crc_buf);
    printf("\r\n--------Message from OTPSequence(): Before MTP flow, CRC =0x%02X%02X%02X%02X\r\n", uc_crc_buf[0], uc_crc_buf[1], uc_crc_buf[2], uc_crc_buf[3]);

    //Switch to Command 2 Page 0
    SendPage(0x20);

    //select MTP zone
    if (uc_otp_times <= 2)  //select A zone and B zone
    {
        uc_buf[0]=0x03;
        MIPI_DCS_Write((PORT0 | PORT1), 0x3F, 1, uc_buf);
    }
    else  //select A zone
    {
        uc_buf[0]=0x01;
        MIPI_DCS_Write((PORT0 | PORT1), 0x3F, 1,uc_buf);
    }

    //Initial MTP flow
    uc_buf[0]=0x01;
    MIPI_DCS_Write((PORT0 | PORT1), 0x38, 1, uc_buf);
    Delay_ms(150);  //wait for more than 120ms

    //Enable MTP end signal output from FTE pin
    uc_buf[0]=0x10;
    MIPI_DCS_Write((PORT0 | PORT1), 0x39, 1, uc_buf);
    Delay_ms(20);  //wait for more than 10ms

    //Check IC status
    SendPage(0x10);
    MIPI_DCS_Read(MAIN_PORT, 0x0A, 1, uc_buf);

    if (uc_buf[0] != 0x98)
    {
        es_otp_rslt = ERROR;
        printf("\r\n--------OTP ERROR_0007: Before MTP Write, IC status check error (not in sleep out)!!!\r\n");
    }
    else
    {
        SendPage(0x20);
        //Enable MTP write
        uc_buf[0]=0x01;
        MIPI_DCS_Write((PORT0 | PORT1), 0x3D, 1, uc_buf);      //3D 01

        //EPWRITE 1+2+3 command
        uc_buf[0]=0x55;
        MIPI_DCS_Write((PORT0 | PORT1), 0x40, 1, uc_buf);      //40 55
        uc_buf[0]=0xAA;
        MIPI_DCS_Write((PORT0 | PORT1), 0x41, 1, uc_buf);      //41 AA
        uc_buf[0]=0x66;
        MIPI_DCS_Write((PORT0 | PORT1), 0x42, 1, uc_buf);      //42 66

        Delay_ms(2000);

        //Read NV Memory Flag Status
        es_nvm = NVM_Flag();

        if (es_nvm == SUCCESS)
        {
            SendPage(0x20);
            //Disable MTP Write
            uc_buf[0]=0x00;
            MIPI_DCS_Write((PORT0 | PORT1), 0x3D, 1, uc_buf);

            //Wait for more than 150ms
            Delay_ms(160);

            //Hardware Reset or Software Reset
            DriverIC_Reset();

            //Wait for more than 50ms
            Delay_ms(60);

            //Sleep Out
            SendPage(0x10);
            uc_buf[0]=0x00;
            MIPI_DCS_Write((PORT0 | PORT1), 0x11, 1, uc_buf);

            //Wait for more than 150ms
            Delay_ms(151);

            //Enable Margin Read
            SendPage(0xF0);  //Command 3 Page B
            uc_buf[0]=0x08;
            MIPI_DCS_Write((PORT0 | PORT1), 0xC7, 1, uc_buf);
            uc_buf[0]=0x05;
            MIPI_DCS_Write((PORT0 | PORT1), 0xC8, 1, uc_buf);

            //Check margin read finish flag (CMD2_Page0, 47h=40h)
            //Then check error flah (CMD3_PageB, 99h=00h)
            SendPage(0x20);
            MIPI_DCS_Read(MAIN_PORT, 0x47, 1, uc_buf);
            SendPage(0xF0);
            MIPI_DCS_Read(MAIN_PORT, 0x99, 1, uc_buf);

            //Disable Margin Read
            SendPage(0xF0);  //Command 3 Page B
            uc_buf[0]=0x00;
            MIPI_DCS_Write((PORT0 | PORT1), 0xC7, 1, uc_buf);
            uc_buf[0]=0x04;
            MIPI_DCS_Write((PORT0 | PORT1), 0xC8, 1, uc_buf);
						Delay_ms(50);
            //read all register value and check
            //printf("\r\n--------Message from OTPSequence(): After MTP flow, IC register read back check begin...\r\n");
            //es_reg_cmp = ICReg_chk(ET1_InitCode);
            //printf("\r\n--------Message from OTPSequence(): After MTP flow, IC register read back check end.\r\n");

            //Read the OTP CRC
            MTP_CRC_Calc(uc_crc_buf_chk);
            printf("\r\n--------Message from OTPSequence(): After MTP flow, CRC =0x%02X%02X%02X%02X\r\n", uc_crc_buf_chk[0], uc_crc_buf_chk[1], uc_crc_buf_chk[2], uc_crc_buf_chk[3]);

            //Check MTP Zone Flag
            uc_otp_times_chk = OTPTimes_Read();

            //Check VCOM
            us_vcom_chk = VCOM_Read();

            if (uc_otp_times_chk == uc_otp_times + 1)
            {
                if (us_vcom_chk == vcom_best)
                {
                    if ((uc_crc_buf[0] == uc_crc_buf_chk[0]) && (uc_crc_buf[1] == uc_crc_buf_chk[1]) && (uc_crc_buf[2] == uc_crc_buf_chk[2]) && (uc_crc_buf[3] == uc_crc_buf_chk[3]))
                    {
                        es_otp_rslt = SUCCESS;
                    }
                    else
                    {
                        es_otp_rslt = ERROR;
                        printf("\r\n--------OTP ERROR_0006: After MTP flow, CRC check error!!!\r\n");
                    }
                }
                else
                {
                    es_otp_rslt = ERROR;
                    printf("\r\n--------OTP ERROR_0005: After MTP flow, vcom check error!!!\r\n");
                }
            }
            else
            {
                es_otp_rslt = ERROR;
                printf("\r\n--------OTP ERROR_0004: After MTP flow, NVM programming times error!!!\r\n");
            }
        }
        else
        {
            es_otp_rslt = ERROR;
            printf("\r\n--------OTP_ERROR_0003: After MTP flow, NVM status error!!!\r\n");
        }
    }

    //light on panel after OTP flow
    LCD_SleepIn();
    MIPI_Reset();
    //printf("\r\nSSD_Init...\r\n");
    IC_Init(SSDInitCode);

    LCMPower_ON();
    Delay_ms(20);
    //POWER_I2C_SETTING(5.5, 5.5);
    Delay_ms(50);
		
    DriverIC_Reset();
    Delay_ms(20);
    DriverIC_Reset();

    if (es_otp_rslt == SUCCESS)
    {
        IC_Init(ET2_InitCode);
    }
    else
    {
        IC_Init(ET1_InitCode);
    }
    FPGA_DisPattern(0, 0, 0, 0);
    Delay_ms(100);
    SendPage(0x10);
    LCD_VideoMode_ON();
    LCD_HSMode();	
    Delay_ms(300); //delay 300ms
    LCD_SleepOut();	
    LCD_PWM(0x0FFF);

    return  es_otp_rslt;
}

/*********************************************************************************
 * 函数名：ICReg_chk
 * 描述  ：check register setting in specified initial code
 * 输入  ：pointer of initial code array
 * 输出  ：
 * 返回  ：
 * 调用  ：外部调用
 */
ErrorStatus ICReg_chk(uint16_t * initCode)
{
    uint16_t * p =  initCode;
    uint8_t cmd_1, cmd_2;
//		uint8_t cmd_3;
    uint8_t data_1, data_2, data_3;
    uint8_t rdBuf[1];
    uint8_t initEnd = 0;

    uint16_t cnt_error = 0;

    while (initEnd == 0)
    {
        cmd_1 = (*p) >> 8;
        data_1 = (*p++);

        if (cmd_1 == 0xF)
        {
            initEnd = 1;
        }
        else if (cmd_1 == 0x1)  // for word conunt = 2 (0xBC of SSD2828 set to 0x02)
        {
            cmd_2 = (*p) >> 8;
            data_2 = (*p++);
//            cmd_3 = (*p) >> 8;
            data_3 = (*p++);

            if ((data_1 == 0xBF) && (cmd_2 == 0x2))
            {
                if (data_2 == 0xFF)  //page selection  command
                {
                    SendPage(data_3);
                }
                else if (data_2 != 0xFB)  //normal register address
                {
                    MIPI_DCS_Read(MAIN_PORT, data_2, 1, rdBuf);

                    if (rdBuf[0] != data_3)
                    {
                        printf ("\r\n ********Message from ICReg_chk: address = 0x%02X, read value = 0x%02X\r, expect value = 0x%02X\r\n", data_2, rdBuf[0], data_3);
                                              //initEnd = 1;
                        cnt_error++;
                    }
                    else
                    {
                        cnt_error = 0;
                    }
                }
            }
        }
    }

    if (cnt_error != 0)
    {
        return ERROR;
    }
    else
    {
        return SUCCESS;
    }
}
