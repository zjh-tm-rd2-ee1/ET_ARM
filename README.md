ET_ARM
=
ARM PROGRAM FOR ET

【FWlib】
=
存放STM32官方库里的【inc】和【src】两个文件夹，这两个文件夹包含了芯片上的所有驱动。  
【src】文件夹中包含了驱动文件,【inc】文件夹中包含了对应的头文件。

【stm32f2xx_rcc.c】
-
rcc = Reset and Clock Control
【system_stm32f2xx.c】只设置了系统时钟和总线时钟，为了方便软件的移植  
外设时钟都是在【stm32f2xx_rcc.c】文件中实现,因为各SOC厂商在CM3内核基础上添加的外设工作速率不一样

【CMSIS】
=
CMSIS = Cortex Microcontroller Software Interface Standard
存放STM32官方库自带的启动文件和一些M3系列通用的文件。

【core_cm3.c】
-
底层文件，M3系列通用，由ARM公司提供，遵守CMSIS标准
为采用Cortex-M3核设计的SOC芯片外设提供进入M3内核的接口
包含一些跟编译器相关的信息

【system_stm32f2xx.c】
-
底层文件，M3系列通用，由ARM公司提供，遵守CMSIS标准
根据HSE或HSI设置系统时钟和总线时钟
实现系统时钟时要用到PLL，需要操作寄存器，寄存器都是以存储器映射的方式来访问，故需包含【stm32f2xx.h】

【stdint.h】
-
ANSIC C头文件，RVMDK开发环境自带
提供数据类型定义

【core_cm3.h】
-
实现CM3内核里面的NVIC（嵌套向量中断控制器）和SytTick（定时器）这两个资源的所有功能

【stm32f2xx.h】
-
由处理器厂商（ST公司）提供
实现存储器映射（将对内存的操作封装成一个宏，即所谓的寄存器）和寄存器声明

	     | stdint.h | ==> | core_cm3.h |==>\  
	     					\
	| system_sstm32f2xx.h | ===========>| stm32f2xx.h |  
						/
			        | stdint.h |==>/  
				

【USER】
=
存放用户代码
【stm32f2xx_it.c】
-
it = interrupt  
实现中断响应函数


【Project】
=
存放工程文件及输出文件【output】



【INI_OTP】
=
存放工程项目初始化代码




