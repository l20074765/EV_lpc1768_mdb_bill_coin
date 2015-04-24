/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               vic_cfg.h
** Latest modified Date:    2008-12-22
** Latest Version:          1.0
** Descriptions:            异常处理程序定义
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Chenmingji
** Created date:            2008-12-22
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __VIC_CFG_H
#define __VIC_CFG_H

/*********************************************************************************************************
  lpc1000特定异常处理程序定义，VECTOR_TABLE_IN_FLASH = 0时无意义
*********************************************************************************************************/
#define WWDG_IRQ_HANDLER                defaultVectorHandle             /* 16 WDT                       */
#define TIMER0_IRQ_HANDLER              TIMER0_IRQHandler             	/* 17 TIMER0                    */
#define TIMER1_IRQ_HANDLER              TIMER1_IRQHandler             	/* 18 TIMER1                    */
#define TIMER2_IRQ_HANDLER              TIMER2_IRQHandler             	/* 19 TIMER2                    */
#define TIMER3_IRQ_HANDLER              TIMER3_IRQHandler             	/* 20 TIMER3                    */
#define UART0_IRQ_HANDLER               Uart0IsrHandler             	/* 21 UART0                     */
#define UART1_IRQ_HANDLER               Uart1IsrHandler             	/* 22 UART1                     */
#define UART2_IRQ_HANDLER               Uart2IsrHandler             	/* 23 UART2                     */
#define UART3_IRQ_HANDLER               Uart3IsrHandler					/* 24 UART3                     */
#define PWM1_IRQ_HANDLER                defaultVectorHandle             /* 25 PWM1                      */
#define I2C0_IRQ_HANDLER                I2C0_IRQHandler             	/* 26 I2C0                      */
#define I2C1_IRQ_HANDLER                defaultVectorHandle            	/* 27 I2C1                      */
#define I2C2_IRQ_HANDLER                defaultVectorHandle             /* 28 I2C2                      */
#define SPI_IRQ_HANDLER                 defaultVectorHandle             /* 29 SPI                       */
#define SSP0_IRQ_HANDLER                defaultVectorHandle             /* 30 SSP0                      */
#define SSP1_IRQ_HANDLER                defaultVectorHandle             /* 31 SSP1                      */
#define PLL0_IRQ_HANDLER                defaultVectorHandle             /* 32 PLL0                      */
#define RTC_IRQ_HANDLER                 defaultVectorHandle             /* 33 RTC                       */
#define EINT0_IRQ_HANDLER               defaultVectorHandle             /* 34 EINT0                     */
#define EINT1_IRQ_HANDLER               defaultVectorHandle             /* 35 EINT1                     */
#define EINT2_IRQ_HANDLER               EINT2_IsrHandler             	/* 36 EINT2                     */
#define EINT3_GPIO_Handler              defaultVectorHandle             /* 37 EINT3                     */
#define ADC_IRQ_HANDLER                 defaultVectorHandle             /* 38 ADC                       */
#define BOD_IRQ_HANDLER                 defaultVectorHandle             /* 39 BOD                       */
#define USB_IRQ_HANDLER                 defaultVectorHandle             /* 40 USB                       */
#define CAN_IRQ_HANDLER                 defaultVectorHandle             /* 41 CAN                       */
#define GPDMA_IRQ_HANDLER               defaultVectorHandle             /* 42 GP DMA                    */
#define I2S_IRQ_HANDLER                 defaultVectorHandle             /* 43 I2S                       */
#define ETHERNET_IRQ_HANDLER            defaultVectorHandle             /* 44 Ethernet                  */
#define RIT_IRQ_HANDLER                 defaultVectorHandle             /* 45 Repete Interrupt Timer    */
#define MC_IRQ_HANDLER                  defaultVectorHandle             /* 46 Motor Control PWM         */
#define QE_IRQ_HANDLER                  defaultVectorHandle             /* 47 Quadrature Encoder        */
#define PLL1_IRQ_HANDLER                defaultVectorHandle             /* 48 PLL1                      */ 
#define USBACT_IRQ_HANDLER              defaultVectorHandle             /* 49 USB_NEED_CLK              */
#define CANACT_IRQ_HANDLER              defaultVectorHandle             /* 50 CAN1WAKE, CAN2WAKE        */ 

/*********************************************************************************************************
  异常处理程序定义，VECTOR_TABLE_IN_FLASH = 0时无意义
*********************************************************************************************************/
#define NMI_HANDLE                      defaultVectorHandle
#define HARD_FAULT_HANDLE               defaultVectorHandle
#define MEM_MANAGE_FAULT_HANDLE         defaultVectorHandle
#define BUS_FAULT_HANDLE                defaultVectorHandle
#define USAGE_FAULT_HANDLE              defaultVectorHandle
#define SVCALL_HANDLE                   svcallHandle                    /*  不能修改                    */
#define DEBUG_MON_HANDLE                defaultVectorHandle
#define PEND_SV_HANDLE                  __s_OSCtxSw                     /*  不能修改                    */
#define SYS_TICK_HANDLE                 __sysTickIsr                    /*  不能修改                    */

#define IRQ_16_HANDLE                   WWDG_IRQ_HANDLER
#define IRQ_17_HANDLE                   TIMER0_IRQ_HANDLER
#define IRQ_18_HANDLE                   TIMER1_IRQ_HANDLER
#define IRQ_19_HANDLE                   TIMER2_IRQ_HANDLER

#define IRQ_20_HANDLE                   TIMER3_IRQ_HANDLER
#define IRQ_21_HANDLE                   UART0_IRQ_HANDLER
#define IRQ_22_HANDLE                   UART1_IRQ_HANDLER
#define IRQ_23_HANDLE                   UART2_IRQ_HANDLER
#define IRQ_24_HANDLE                   UART3_IRQ_HANDLER
#define IRQ_25_HANDLE                   PWM1_IRQ_HANDLER
#define IRQ_26_HANDLE                   I2C0_IRQ_HANDLER
#define IRQ_27_HANDLE                   I2C1_IRQ_HANDLER
#define IRQ_28_HANDLE                   I2C2_IRQ_HANDLER
#define IRQ_29_HANDLE                   SPI_IRQ_HANDLER

#define IRQ_30_HANDLE                   SSP0_IRQ_HANDLER
#define IRQ_31_HANDLE                   SSP1_IRQ_HANDLER
#define IRQ_32_HANDLE                   PLL0_IRQ_HANDLER
#define IRQ_33_HANDLE                   RTC_IRQ_HANDLER
#define IRQ_34_HANDLE                   EINT0_IRQ_HANDLER
#define IRQ_35_HANDLE                   EINT1_IRQ_HANDLER
#define IRQ_36_HANDLE                   EINT2_IRQ_HANDLER
#define IRQ_37_HANDLE                   EINT3_GPIO_Handler
#define IRQ_38_HANDLE                   ADC_IRQ_HANDLER
#define IRQ_39_HANDLE                   BOD_IRQ_HANDLER

#define IRQ_40_HANDLE                   USB_IRQ_HANDLER
#define IRQ_41_HANDLE                   CAN_IRQ_HANDLER
#define IRQ_42_HANDLE                   GPDMA_IRQ_HANDLER
#define IRQ_43_HANDLE                   I2S_IRQ_HANDLER
#define IRQ_44_HANDLE                   ETHERNET_IRQ_HANDLER
#define IRQ_45_HANDLE                   RIT_IRQ_HANDLER
#define IRQ_46_HANDLE                   MC_IRQ_HANDLER
#define IRQ_47_HANDLE                   QE_IRQ_HANDLER
#define IRQ_48_HANDLE                   PLL1_IRQ_HANDLER
#define IRQ_49_HANDLE                   USBACT_IRQ_HANDLER

#define IRQ_50_HANDLE                   CANACT_IRQ_HANDLER
#define IRQ_51_HANDLE                   defaultVectorHandle
#define IRQ_52_HANDLE                   defaultVectorHandle
#define IRQ_53_HANDLE                   defaultVectorHandle
#define IRQ_54_HANDLE                   defaultVectorHandle
#define IRQ_55_HANDLE                   defaultVectorHandle
#define IRQ_56_HANDLE                   defaultVectorHandle
#define IRQ_57_HANDLE                   defaultVectorHandle
#define IRQ_58_HANDLE                   defaultVectorHandle
#define IRQ_59_HANDLE                   defaultVectorHandle

#define IRQ_60_HANDLE                   defaultVectorHandle
#define IRQ_61_HANDLE                   defaultVectorHandle
#define IRQ_62_HANDLE                   defaultVectorHandle
#define IRQ_63_HANDLE                   defaultVectorHandle
#define IRQ_64_HANDLE                   defaultVectorHandle
#define IRQ_65_HANDLE                   defaultVectorHandle
#define IRQ_66_HANDLE                   defaultVectorHandle
#define IRQ_67_HANDLE                   defaultVectorHandle
#define IRQ_68_HANDLE                   defaultVectorHandle
#define IRQ_69_HANDLE                   defaultVectorHandle

#define IRQ_70_HANDLE                   defaultVectorHandle
#define IRQ_71_HANDLE                   defaultVectorHandle
#define IRQ_72_HANDLE                   defaultVectorHandle
#define IRQ_73_HANDLE                   defaultVectorHandle
#define IRQ_74_HANDLE                   defaultVectorHandle
#define IRQ_75_HANDLE                   defaultVectorHandle
#define IRQ_76_HANDLE                   defaultVectorHandle
#define IRQ_77_HANDLE                   defaultVectorHandle
#define IRQ_78_HANDLE                   defaultVectorHandle
#define IRQ_79_HANDLE                   defaultVectorHandle

#define IRQ_80_HANDLE                   defaultVectorHandle
#define IRQ_81_HANDLE                   defaultVectorHandle
#define IRQ_82_HANDLE                   defaultVectorHandle
#define IRQ_83_HANDLE                   defaultVectorHandle
#define IRQ_84_HANDLE                   defaultVectorHandle
#define IRQ_85_HANDLE                   defaultVectorHandle
#define IRQ_86_HANDLE                   defaultVectorHandle
#define IRQ_87_HANDLE                   defaultVectorHandle
#define IRQ_88_HANDLE                   defaultVectorHandle
#define IRQ_89_HANDLE                   defaultVectorHandle

#define IRQ_90_HANDLE                   defaultVectorHandle
#define IRQ_91_HANDLE                   defaultVectorHandle
#define IRQ_92_HANDLE                   defaultVectorHandle
#define IRQ_93_HANDLE                   defaultVectorHandle
#define IRQ_94_HANDLE                   defaultVectorHandle
#define IRQ_95_HANDLE                   defaultVectorHandle
#define IRQ_96_HANDLE                   defaultVectorHandle
#define IRQ_97_HANDLE                   defaultVectorHandle
#define IRQ_98_HANDLE                   defaultVectorHandle
#define IRQ_99_HANDLE                   defaultVectorHandle

#define IRQ_100_HANDLE                  defaultVectorHandle
#define IRQ_101_HANDLE                  defaultVectorHandle
#define IRQ_102_HANDLE                  defaultVectorHandle
#define IRQ_103_HANDLE                  defaultVectorHandle
#define IRQ_104_HANDLE                  defaultVectorHandle
#define IRQ_105_HANDLE                  defaultVectorHandle
#define IRQ_106_HANDLE                  defaultVectorHandle
#define IRQ_107_HANDLE                  defaultVectorHandle
#define IRQ_108_HANDLE                  defaultVectorHandle
#define IRQ_109_HANDLE                  defaultVectorHandle

#define IRQ_110_HANDLE                  defaultVectorHandle
#define IRQ_111_HANDLE                  defaultVectorHandle
#define IRQ_112_HANDLE                  defaultVectorHandle
#define IRQ_113_HANDLE                  defaultVectorHandle
#define IRQ_114_HANDLE                  defaultVectorHandle
#define IRQ_115_HANDLE                  defaultVectorHandle
#define IRQ_116_HANDLE                  defaultVectorHandle
#define IRQ_117_HANDLE                  defaultVectorHandle
#define IRQ_118_HANDLE                  defaultVectorHandle
#define IRQ_119_HANDLE                  defaultVectorHandle

#define IRQ_120_HANDLE                  defaultVectorHandle
#define IRQ_121_HANDLE                  defaultVectorHandle
#define IRQ_122_HANDLE                  defaultVectorHandle
#define IRQ_123_HANDLE                  defaultVectorHandle
#define IRQ_124_HANDLE                  defaultVectorHandle
#define IRQ_125_HANDLE                  defaultVectorHandle
#define IRQ_126_HANDLE                  defaultVectorHandle
#define IRQ_127_HANDLE                  defaultVectorHandle
#define IRQ_128_HANDLE                  defaultVectorHandle
#define IRQ_129_HANDLE                  defaultVectorHandle

#define IRQ_130_HANDLE                  defaultVectorHandle
#define IRQ_131_HANDLE                  defaultVectorHandle
#define IRQ_132_HANDLE                  defaultVectorHandle
#define IRQ_133_HANDLE                  defaultVectorHandle
#define IRQ_134_HANDLE                  defaultVectorHandle
#define IRQ_135_HANDLE                  defaultVectorHandle
#define IRQ_136_HANDLE                  defaultVectorHandle
#define IRQ_137_HANDLE                  defaultVectorHandle
#define IRQ_138_HANDLE                  defaultVectorHandle
#define IRQ_139_HANDLE                  defaultVectorHandle

#define IRQ_140_HANDLE                  defaultVectorHandle
#define IRQ_141_HANDLE                  defaultVectorHandle
#define IRQ_142_HANDLE                  defaultVectorHandle
#define IRQ_143_HANDLE                  defaultVectorHandle
#define IRQ_144_HANDLE                  defaultVectorHandle
#define IRQ_145_HANDLE                  defaultVectorHandle
#define IRQ_146_HANDLE                  defaultVectorHandle
#define IRQ_147_HANDLE                  defaultVectorHandle
#define IRQ_148_HANDLE                  defaultVectorHandle
#define IRQ_149_HANDLE                  defaultVectorHandle

#define IRQ_150_HANDLE                  defaultVectorHandle
#define IRQ_151_HANDLE                  defaultVectorHandle
#define IRQ_152_HANDLE                  defaultVectorHandle
#define IRQ_153_HANDLE                  defaultVectorHandle
#define IRQ_154_HANDLE                  defaultVectorHandle
#define IRQ_155_HANDLE                  defaultVectorHandle
#define IRQ_156_HANDLE                  defaultVectorHandle
#define IRQ_157_HANDLE                  defaultVectorHandle
#define IRQ_158_HANDLE                  defaultVectorHandle
#define IRQ_159_HANDLE                  defaultVectorHandle

#define IRQ_160_HANDLE                  defaultVectorHandle
#define IRQ_161_HANDLE                  defaultVectorHandle
#define IRQ_162_HANDLE                  defaultVectorHandle
#define IRQ_163_HANDLE                  defaultVectorHandle
#define IRQ_164_HANDLE                  defaultVectorHandle
#define IRQ_165_HANDLE                  defaultVectorHandle
#define IRQ_166_HANDLE                  defaultVectorHandle
#define IRQ_167_HANDLE                  defaultVectorHandle
#define IRQ_168_HANDLE                  defaultVectorHandle
#define IRQ_169_HANDLE                  defaultVectorHandle

#define IRQ_170_HANDLE                  defaultVectorHandle
#define IRQ_171_HANDLE                  defaultVectorHandle
#define IRQ_172_HANDLE                  defaultVectorHandle
#define IRQ_173_HANDLE                  defaultVectorHandle
#define IRQ_174_HANDLE                  defaultVectorHandle
#define IRQ_175_HANDLE                  defaultVectorHandle
#define IRQ_176_HANDLE                  defaultVectorHandle
#define IRQ_177_HANDLE                  defaultVectorHandle
#define IRQ_178_HANDLE                  defaultVectorHandle
#define IRQ_179_HANDLE                  defaultVectorHandle

#define IRQ_180_HANDLE                  defaultVectorHandle
#define IRQ_181_HANDLE                  defaultVectorHandle
#define IRQ_182_HANDLE                  defaultVectorHandle
#define IRQ_183_HANDLE                  defaultVectorHandle
#define IRQ_184_HANDLE                  defaultVectorHandle
#define IRQ_185_HANDLE                  defaultVectorHandle
#define IRQ_186_HANDLE                  defaultVectorHandle
#define IRQ_187_HANDLE                  defaultVectorHandle
#define IRQ_188_HANDLE                  defaultVectorHandle
#define IRQ_189_HANDLE                  defaultVectorHandle

#define IRQ_190_HANDLE                  defaultVectorHandle

#endif                                                                  /*  __VIC_CFG_H                 */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
