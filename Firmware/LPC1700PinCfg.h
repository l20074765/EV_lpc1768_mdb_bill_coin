/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info--------------------------------------------------------------------------------
** File name:			LPC1700PinCfg.c
** Last modified Date:  2009-05-12
** Last Version:		V1.01
** Descriptions:		引脚配置		
**-------------------------------------------------------------------------------------------------------
** Modified by:			sunway
** Modified date:		2013-01-06
** Version:				V1.2
** Descriptions:		对程序的风格以及注释略作调整，并检查代码
********************************************************************************************************/
#ifndef __LPC1700PINCFG_H
#define __LPC1700PINCFG_H
/*********************************************************************************************************
** P0口引脚功能设置
*********************************************************************************************************/
// P0.0
#define	P0_0_GPIO             0x00                                      /* GPIO                         */
#define P0_0_RD1              0x01                                      /* CAN-1控制器接收引脚          */
#define P0_0_TXD3             0x02                                      /* UART3发送引脚                */
#define P0_0_SDA1             0x03                                      /* I2C-1数据线（开漏）          */
#define P0_0_FNUC             P0_0_TXD3
//P0.1
#define P0_1_GPIO             0x00                                      /* GPIO                         */
#define P0_1_TD1              0x01                                      /* CAN-1控制器发送引脚          */
#define P0_1_RXD3             0x02                                      /* UART3接收引脚                */
#define P0_1_SCL1             0x03                                      /* I2C-1时钟线（开漏）          */
#define P0_1_FNUC             P0_1_RXD3
//P0.2
#define P0_2_GPIO             0x00                                      /* GPIO                         */
#define P0_2_TXD0             0x01                                      /* UART0发送引脚                */
#define P0_2_AD07             0x02                                      /* AD0.7引脚                    */
//...   Reserved              0x03
#define P0_2_FNUC             P0_2_TXD0
//P0.3
#define P0_3_GPIO             0x00                                      /* GPIO                         */
#define P0_3_RXD0             0x01                                      /* UART0接收引脚                */
#define P0_3_AD06             0x02                                      /* AD0.6引脚                    */
//...   Reserved              0x03 
#define P0_3_FNUC             P0_3_RXD0
//P0.4
#define P0_4_GPIO             0x00                                      /* GPIO                         */
#define P0_4_I2SRX_CLK        0x01                                      /* I2S总线接收时钟SCK           */
#define P0_4_RD2              0x02                                      /* CAN-2接收线                  */
#define P0_4_CAP20            0x03                                      /* 定时器2捕获输入，通道0       */		
#define P0_4_FNUC             P0_4_GPIO
//P0.5
#define P0_5_GPIO             0x00                                      /* GPIO                         */
#define P0_5_I2SRX_WS         0x01                                      /* I2S总线接收字选择WS          */
#define P0_5_TD2              0x02                                      /* CAN-2发送线                  */
#define P0_5_CAP21            0x03                                      /* 定时器2捕获输入，通道1       */		
#define P0_5_FNUC             P0_5_GPIO
//P0.6
#define P0_6_GPIO             0x00                                      /* GPIO                         */
#define P0_6_I2SRX_SDA        0x01                                      /* I2S总线接收数据线SD          */
#define P0_6_SSEL1            0x02                                      /* SSP-1总线从机选择            */
#define P0_6_MAT20            0x03                                      /* 定时器2匹配输出，通道0       */		
#define P0_6_FNUC             P0_6_GPIO
//P0.7
#define P0_7_GPIO             0x00                                      /* GPIO                         */
#define P0_7_I2STX_CLK        0x01                                      /* I2S总线发送时钟线SCK         */
#define P0_7_SSCK1            0x02                                      /* SSP-1时钟线                  */
#define P0_7_MAT21            0x03                                      /* 定时器2匹配输出，通道1       */	
#define P0_7_FNUC             P0_7_GPIO
//P0.8
#define P0_8_GPIO             0x00                                      /* GPIO                         */
#define P0_8_I2STX_WS         0x01                                      /* I2S总线发送字选择WS          */
#define P0_8_SMISO1           0x02                                      /* SSP-1主输入从输出数据线      */
#define P0_8_MAT22            0x03                                      /* 定时器2匹配输出，通道2       */
#define P0_8_FNUC             P0_8_GPIO		
//P0.9
#define P0_9_GPIO             0x00                                      /* GPIO                         */
#define P0_9_I2STX_SDA        0x01                                      /* I2S总线发送数据线SD          */
#define P0_9_SMOSI1           0x02                                      /* SSP-1主输出从输入数据线      */
#define P0_9_MAT23            0x03                                      /* 定时器2匹配输出，通道3       */
#define P0_9_FNUC             P0_9_GPIO
//P0.10
#define P0_10_GPIO            0x00                                      /* GPIO                         */
#define P0_10_TXD2            0x01                                      /* UART2发送引脚                */
#define P0_10_SDA2            0x02                                      /* I2C-2数据线(非开漏引脚)      */
#define P0_10_MAT30           0x03                                      /* 定时器3匹配输出，通道0       */
#define P0_10_FNUC            P0_10_TXD2               
//P0.11
#define P0_11_GPIO            0x00                                      /* GPIO                         */
#define P0_11_RXD2            0x01                                      /* UART2接收引脚                */
#define P0_11_SCL2            0x02                                      /* I2C-2时钟线(非开漏引脚)      */
#define P0_11_MAT31           0x03                                      /* 定时器3匹配输出，通道1       */
#define P0_11_FNUC            P0_11_RXD2                
//P0.15
#define P0_15_GPIO            0x00                                      /* GPIO                         */
#define P0_15_TXD1            0x01                                      /* UART1发送引脚                */
#define P0_15_SCK0            0x02                                      /* SSP0时钟线                   */
#define P0_15_SCK             0x03                                      /* SPI时钟线                    */                                             
#define P0_15_FNUC            P0_15_GPIO                                                                
//P0.16
#define P0_16_GPIO            0x00                                      /* GPIO                         */
#define P0_16_RXD1            0x01                                      /* UART1接收引脚                */
#define P0_16_SSEL0           0x02                                      /* SSP0从机选择                 */
#define P0_16_SSEL            0x03                                      /* SPI从机选择                  */                                               
#define P0_16_FNUC            P0_16_GPIO                                                         
//P0.17
#define P0_17_GPIO            0x00                                      /* GPIO                         */
#define P0_17_CTS1            0x01                                      /* UART1清零发送信号CTS         */
#define P0_17_MISO0           0x02                                      /* SSP0主输入从输出数据线       */
#define P0_17_MISO            0x03                                      /* SPI主入从出数据线            */                                               
#define P0_17_FNUC            P0_17_GPIO                                                         
//P0.18
#define P0_18_GPIO            0x00                                      /* GPIO                         */
#define P0_18_DCD1            0x01                                      /* UART1数据载波检测输入DCD     */
#define P0_18_MOSI0           0x02                                      /* SSP-0主输出从输入数据线      */
#define P0_18_MOSI            0x03                                      /* SPI主出从入数据线            */                                              
#define P0_18_FNUC            P0_18_GPIO                                                          
//P0.19
#define P0_19_GPIO            0x00                                      /* GPIO                         */
#define P0_19_DSR1            0x01                                      /* UART1数据设置就绪DSR         */
//...   Reserved              0x02                                      /* 保留                         */
#define P0_19_SDA1            0x03                                      /* I2C-1数据线（非开漏）        */                                              
#define P0_19_FNUC            P0_19_GPIO                                                          
//P0.20
#define P0_20_GPIO            0x00                                      /* GPIO                         */
#define P0_20_DTR1            0x01                                      /* UART1终端就绪DTR             */
//...   Reserved              0x02                                  	/* 保留                         */
#define P0_20_SCL1            0x03                                      /* I2C-1时钟线（非开漏）        */                                          
#define P0_20_FNUC            P0_19_GPIO                                      
//P0.21
#define P0_21_GPIO            0x00                                      /* GPIO                         */
#define P0_21_RI1             0x01                                      /* UART1振铃信号                */
//...   Reserved              0x02                                      /* 保留                         */
#define P0_21_RD1             0x03                                      /* CAN-1接收引脚                */                                    
#define P0_21_FNUC            P0_21_GPIO                                      
//P0.22
#define P0_22_GPIO            0x00                                      /* GPIO                         */
#define P0_22_RTS1            0x01                                      /* UART1请求发送引脚            */
//...   Reserved              0x02                                      /* 保留                         */
#define P0_22_TD1             0x03                                      /* CAN-1发送线                  */                                   
#define P0_22_FNUC            P0_22_GPIO                                      
//P0.23
#define P0_23_GPIO            0x00                                      /* GPIO                         */
#define P0_23_AD00            0x01                                      /* ADC-0，通道0                 */
#define P0_23_I2SRX_CLK       0x02                                      /* I2S接收时钟SCK               */
#define P0_23_CAP30           0x03                                      /* 定时器3捕获输入，通道0       */                                     
#define P0_23_FNUC            P0_23_GPIO                                       
//P0.24
#define P0_24_GPIO            0x00                                      /* GPIO                         */
#define P0_24_AD01            0x01                                      /* ADC-0，通道1                 */
#define P0_24_I2SRX_WS        0x02                                      /* I2S接收字选择WS              */
#define P0_24_CAP31           0x03                                      /* 定时器3捕获输入，通道1       */                                      
#define P0_24_FNUC            P0_24_GPIO                                       
//P0.25
#define P0_25_GPIO            0x00                                      /* GPIO                         */
#define P0_25_AD02            0x01                                      /* ADC-0，通道2                 */
#define P0_25_I2SRX_SDA       0x02                                      /* I2S接收数据SD                */
#define P0_25_TXD3            0x03                                      /* UART3发送引脚                */                                  
#define P0_25_FNUC            P0_25_GPIO                                               
//P0.26
#define P0_26_GPIO            0x00                                      /* GPIO                         */
#define P0_26_AD03            0x01                                      /* ADC-0，通道3                 */
#define P0_26_AOUT            0x02                                      /* DAC输出                      */
#define P0_26_RXD3            0x03                                      /* UART-3接收引脚               */                                        
#define P0_26_FNUC            P0_26_GPIO                                              
//P0.27
#define P0_27_GPIO            0x00                                      /* GPIO                         */
#define P0_27_SDA0            0x01                                      /* I2C0数据输入/输出，开漏      */
#define P0_27_USB_SDA         0x02                                      /* USB接口I2C串行数据OTG收发器  */
//..    Reserved              0x03                                      /* 保留                         */                                         
#define P0_27_FNUC            P0_27_SDA0                                              
//P0.28
#define P0_28_GPIO            0x00                                      /* GPIO                         */
#define P0_28_SCL0            0x01                                      /* I2C0时钟输入，开漏           */
#define P0_28_USB_SCL         0x02                                      /* USB接口I2C时钟线，OTG收发器  */
//..    Reserved              0x03                                   /* 保留                         */                                     
#define P0_28_FNUC            P0_28_SCL0                                       
// P0.29
#define P0_29_GPIO            0x00                                      /* GPIO                         */
#define P0_29_USB_DD          0x01                                      /* USB双向数据D+线              */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */                                      
#define P0_29_FNUC            P0_29_GPIO                                      
//P0.30
#define P0_30_GPIO            0x00                                      /* GPIO                         */
#define P0_30_USB_DS          0x01                                      /* USB双向数据D-线              */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */                                     							  
#define P0_30_FNUC            P0_30_GPIO 
/*********************************************************************************************************
** P1口引脚功能设置
*********************************************************************************************************/
//P1.0
#define P1_0_GPIO             0x00                                      /* GPIO                         */
#define P1_0_ENET_TXD0        0x01                                      /* 以太网发送数据脚0            */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */
#define P1_0_FNUC             P1_0_GPIO
// P1.1
#define P1_1_GPIO             0x00                                      /* GPIO                         */
#define P1_1_ENET_TX_EN       0x01                                      /* 以太网发送数据脚1            */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */
#define P1_1_FNUC             P1_1_GPIO
// P1.4
#define P1_4_GPIO             0x00                                      /* GPIO                         */
#define P1_4_ENET_TX_EN       0x01                                      /* 以太网发送使能               */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */
#define P1_4_FNUC             P1_4_GPIO
//P1.8
#define P1_8_GPIO             0x00                                      /* GPIO                         */
#define P1_8_ENET_CRS         0x01                                      /* 以太网载波侦测脚             */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */										     
#define P1_8_FNUC             P1_8_GPIO
//P1.9
#define P1_9_GPIO             0x00                                      /* GPIO                         */
#define P1_9_ENET_RXD0        0x01                                      /* 以太网接收数据脚0            */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */													  
#define P1_9_FNUC             P1_9_GPIO
//P1.10
#define P1_10_GPIO            0x00                                      /* GPIO                         */
#define P1_10_ENET_RXD1       0x01                                      /* 以太网接收数据脚1            */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */
#define P1_10_FNUC            P1_10_GPIO
//P1.11
#define P1_14_GPIO            0x00                                      /*  GPIO                        */
#define P1_14_ENET_RX_ER      0x01                                      /* 以太网接收错误               */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */													     
#define P1_14_FNUC            P1_14_GPIO
//P1.15
#define P1_15_GPIO            0x00                                      /* GPIO                         */
#define P1_15_ENET_REF_CLK    0x01                                      /* 以太网参拷时钟输入           */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */											   
#define P1_15_FNUC            P1_15_GPIO
//P1.16
#define P1_16_GPIO            0x00                                      /* GPIO                         */
#define P1_16_ENET_MDC        0x01                                      /* 以太网MIIM时钟               */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */
#define P1_16_FNUC            P1_16_GPIO
//P1.17
#define P1_17_GPIO            0x00                                      /* GPIO                         */
#define P1_17_ENET_MDIO       0x01                                      /* 以太网MI数据输入\输出        */
//..    Reserved              0x02                                      /* 保留                         */
//..    Reserved              0x03                                      /* 保留                         */
#define P1_17_FNUC            P1_17_GPIO
//P1.18
#define P1_18_GPIO            0x00                                      /*  GPIO                        */
#define P1_18_USB_UP_LED      0x01                                      /* USB GOODLINK指示脚           */
#define P1_18_PWM11           0x02                                      /* PWM1输出，通道1              */
#define P1_18_CAP10           0x03                                      /* Timer1捕获输入，通道0        */                                             
#define P1_18_FNUC            P1_18_GPIO                                                
//P1.19
#define P1_19_GPIO            0x00                                      /*  GPIO                        */
#define P1_19_MCO0A           0x01                                      /* 电机控制PWM通道0，输出A      */
#define P1_19_USB_PPWR        0x02                                      /* USB端口电源使能信号          */
#define P1_19_CAP11           0x03                                      /* Timer1捕获输入，通道1        */                                             
#define P1_19_FNUC            P1_19_GPIO                                                 
//P1.20
#define P1_20_GPIO            0x00                                      /*  GPIO                        */
#define P1_20_MCFB0           0x01                                      /* 电机控制PWM通道0，回环输入   */
#define P1_20_PWM12           0x02                                      /* PWM-2输出，通道2             */
#define P1_20_SCK0            0x03                                      /* SSP-0时钟输入                */                                            
#define P1_20_FNUC            P1_20_GPIO                                                
// P1.21
#define P1_21_GPIO            0x00                                      /* GPIO                         */
#define P1_21_MCABORT         0x01                                      /* 电机控制PWM，紧急中止        */
#define P1_21_PWM13           0x02                                      /* PWM-1输出，通道3             */
#define P1_21_SSEL0           0x03                                      /* SSP-0从机选择                */                                             
#define P1_21_FNUC            P1_21_GPIO                                                
//P1.22
#define P1_22_GPIO            0x00                                      /* GPIO                         */
#define P1_22_MC0B            0x01                                      /* 电机控制PWM通道0，输出B      */
#define P1_22_USB_PWRD        0x02                                      /* USB端口的电源状态            */
#define P1_22_MAT10           0x03                                      /* 定时器1匹配输出，通道0       */                                             
#define P1_22_FNUC            P1_22_GPIO                                                 
//P1.23
#define P1_23_GPIO            0x00                                      /* GPIO                         */
#define P1_23_MCFB1           0x01                                      /* 电机控制PWM通道1，反馈输入   */
#define P1_23_PWM14           0x02                                      /* PWM-1输出，通道4             */
#define P1_23_MISO0           0x03                                      /* SSP-0主机输入，从机输出      */                                              
#define P1_23_FNUC            P1_23_GPIO                                                  
//P1.24
#define P1_24_GPIO            0x00                                      /* GPIO                         */
#define P1_24_MCFB2           0x01                                      /* 电机控制PWM通道2，反馈输入   */
#define P1_24_PWM15           0x02                                      /* PWM-1输出，通道5             */
#define P1_24_MOSI0           0x03                                      /* SSP-0主机输出，从机输入      */                                             
#define P1_24_FNUC            P1_24_GPIO                                               
//P1.25
#define P1_25_GPIO            0x00                                      /* GPIO                         */
#define P1_25_MC1A            0x01                                      /* 电机控制PWM通道1，输出A      */
#define P1_25_CLKOUT          0x02                                      /* 时钟输出引脚                 */
#define P1_25_MAT11           0x03                                      /* 定时器1匹配输出，通道1       */                                             
#define P1_25_FNUC            P1_25_GPIO                                                 
//P1.26
#define P1_26_GPIO            0x00                                      /* GPIO                         */
#define P1_26_MC1B            0x01                                      /* 电机控制PWM通道1，输出B      */
#define P1_26_PWM16           0x02                                      /* PWM-1输出，通道6             */
#define P1_26_CAP00           0x03                                      /* 定时器0捕获输入，通道0       */                                             
#define P1_26_FNUC            P1_26_GPIO                                             
//P1.27
#define P1_27_GPIO            0x00                                      /* GPIO                         */
#define P1_27_CLKOUT          0x01                                      /* 时钟输出引脚                 */
#define P1_27_USB_OVRCR       0x02                                      /* USB端口过载电流状态          */
#define P1_27_CAP01           0x03                                      /* 定时器0捕获输入，通道1       */                                              
#define P1_27_FNUC            P1_27_GPIO                                                 
// P1.28
#define P1_28_GPIO            0x00                                      /* GPIO                         */
#define P1_28_MC2A            0x01                                      /* 电机控制PWM通道2，输出A      */
#define P1_28_PCAP10          0x02                                      /* PWM-1捕获输入，通道0         */
#define P1_28_MAT00           0x03                                      /* 定时器0匹配输出，通道0       */                                             
#define P1_28_FNUC            P1_28_GPIO                                                 
// P1.29
#define P1_29_GPIO            0x00                                      /* GPIO                         */
#define P1_29_MC2B            0x01                                      /* 电机控制PWM通道2，输出B      */
#define P1_29_PCAP11          0x02                                      /* PWM-1捕获输入，通道1         */
#define P1_29_MAT01           0x03                                      /* 定时器0匹配输出，通道1       */                                             
#define P1_29_FNUC            P1_29_GPIO                                                  
//P1.30
#define P1_30_GPIO            0x00                                      /* GPIO                         */
//...   Reserved              0x01                                      /* 保留                         */
#define P1_30_VBUS            0x02                                      /* 存在的USB总线电源            */
#define P1_30_AD04            0x03                                      /* ADC转换器0.通道4输入         */                                             
#define P1_30_FNUC            P1_30_GPIO                                                 
//P1.31
#define P1_31_GPIO            0x00                                      /* GPIO                         */
//...   Reserved              0x01                                      /* 保留                         */
#define P1_31_SSCK1           0x02                                      /* SSP-1时钟线                  */
#define P1_31_AD05            0x03                                      /* ADC-0输入，通道5             */                                            
#define P1_31_FNUC            P1_31_GPIO                                                
/*********************************************************************************************************
** P2口引脚功能设置
*********************************************************************************************************/
//P2.0
#define P2_0_GPIO             0x00                                      /* GPIO                         */
#define P2_0_PWM11            0x01                                      /* PWM-1，通道1                 */
#define P2_0_TXD1             0x02                                      /* UART1数据发送引脚            */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_0_FNUC             P2_0_GPIO
// P2.1
#define P2_1_GPIO             0x00                                      /* GPIO                         */
#define P2_1_PWM12            0x01                                      /* PWM-1，通道2                 */
#define P2_1_RXD1             0x02                                      /* UART1数据接收引脚            */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_1_FNUC             P2_1_GPIO
// P2.2
#define P2_2_GPIO             0x00                                      /* GPIO                         */
#define P2_2_PWM13            0x01                                      /* PWM-1，通道3                 */
#define P2_2_CTS1             0x02                                      /* UART1清零发送线              */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_2_FNUC             P2_2_GPIO
//P2.3
#define P2_3_GPIO             0x00                                      /* GPIO                         */
#define P2_3_PWM14            0x01                                      /* PWM-1，通道4                 */
#define P2_3_DCD1             0x02                                      /* UART1数据载波检测线          */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_3_FNUC             P2_3_GPIO
// P2.4
#define P2_4_GPIO             0x00                                      /* GPIO                         */
#define P2_4_PWM15            0x01                                      /* PWM-1，通道5                 */
#define P2_4_DSR1             0x02                                      /* UART1数据设置就绪线          */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_4_FNUC             P2_4_GPIO
//P2.5
#define P2_5_GPIO             0x00                                      /* GPIO                         */
#define P2_5_PWM16            0x01                                      /* PWM-1，通道6                 */
#define P2_5_DTR1             0x02                                      /* UART1数据终端就绪线          */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_5_FNUC             P2_5_GPIO
//P2.6
#define P2_6_GPIO             0x00                                      /* GPIO                         */
#define P2_6_PCAP10           0x01                                      /* PWM-1捕获输入，通道0         */
#define P2_6_RI1              0x02                                      /* UART1振铃输入                */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_6_FNUC             P2_6_GPIO
//P2.7
#define P2_7_GPIO             0x00                                      /* GPIO                         */
#define P2_7_RD2              0x01                                      /* CAN-2接收线                  */
#define P2_7_RTS1             0x02                                      /* UART1请求发送输出            */                                                                       /* RS-485/EIA-485输出使能信号   */
//...   Reserved              0x03                                      /* 保留                         */
#define P2_7_FNUC             P2_7_GPIO
//P2.8
#define P2_8_GPIO             0x00                                      /* GPIO                         */
#define P2_8_TD2              0x01                                      /* CAN-2发送线                  */
#define P2_8_TXD2             0x02                                      /* UART2发送引脚                */
#define P2_8_ENET_MDC         0x03                                      /* 以太网MIIM时钟               */
#define P2_8_FNUC             P2_8_GPIO
//P2.9
#define P2_9_GPIO             0x00                                      /* GPIO                         */
#define P2_9_U1CONNECT        0x01                                      /* USB1软连接控制               */
#define P2_9_RXD2             0x02                                      /* UART2接收引脚                */
#define P2_9_ENET_MDIO        0x03                                      /* 以太网MIIM数据输入和输出     */
#define P2_9_FNUC             P2_9_GPIO
// P2.10（ISP）
#define P2_10_GPIO            0x00                                      /* GPIO                         */
#define P2_10_EINT0           0x01                                      /* 外部中断0输入                */
#define P2_10_NMI             0x02                                      /* 非屏蔽中断输入               */
//...   Reserved              0x03                                      /* 保留                         */                                             
#define P2_10_FNUC            P2_10_GPIO                                                 
//P2.11
#define P2_11_GPIO            0x00                                      /* GPIO                         */
#define P2_11_EINT1           0x01                                      /* 外部中断1输入                */
//...   Reserved              0x02                                      /* 保留                         */
#define P2_11_I2STX_CLK       0x03                                      /* I2S发送时钟SCK               */                                             
#define P2_11_FNUC            P2_11_GPIO                                                 
//P2.12
#define P2_12_GPIO            0x00                                      /* GPIO                         */
#define P2_12_EINT2           0x01                                      /* 外部中断2输入                */
//...   Reserved              0x02                                      /* 保留                         */
#define P2_12_I2STX_WS        0x03                                      /* I2S发送字选择WS              */                                            
#define P2_12_FNUC            P2_12_EINT2                                                 
// P2.13
#define P2_13_GPIO            0x00                                      /* GPIO                         */
#define P2_13_EINT3           0x01                                      /* 外部中断3输入                */
//...   Reserved              0x02                                      /* 保留                         */
#define P2_13_I2STX_SDA       0x03                                      /* I2S发送数据SD                */                                              
#define P2_13_FNUC            P2_13_GPIO                                            
/*********************************************************************************************************
** P3口引脚功能设置
*********************************************************************************************************/
//P3.25
#define P3_25_GPIO            0x00                                      /*  GPIO                        */
//...   Reserved              0x01                                      /*  保留                        */
#define P3_25_MAT00           0x02                                      /*  定时器0匹配输出，通道0      */
#define P3_25_PWM12           0x03                                      /*  PWM-1输出，通道2            */                                              
#define P3_25_FNUC            P3_25_GPIO                                                    
//P3.26
#define P3_26_GPIO            0x00                                      /* GPIO                         */
#define P3_26_STCLK           0x01                                      /* 系统节拍定时器时钟输入       */
#define P3_26_MAT01           0x02                                      /* 定时器0匹配输出，通道1       */
#define P3_26_PWM13           0x03                                      /* PWM-1输出，通道3             */                                              
#define P3_26_FNUC            P3_26_GPIO                                             
/*********************************************************************************************************
** P4口引脚功能设置
*********************************************************************************************************/
//P4.28
#define P4_28_GPIO            0x00                                      /* GPIO                         */
#define P4_28_RX_MCLK         0x01                                      /* —I2S接收主机时钟            */
#define P4_28_MAT20           0x02                                      /* 定时器2匹配输出，通道0       */
#define P4_28_TXD3            0x03                                      /* UART3发送引脚                */                                              
#define P4_28_FNUC            P4_28_GPIO                                                   
//P4.29
#define P4_29_GPIO            0x00                                      /* GPIO                         */
#define P4_29_TX_MCLK         0x01                                      /* I2S发送主机时钟              */
#define P4_29_MAT21           0x02                                      /* 定时器2匹配输出，通道1       */
#define P4_29_RXD3            0x03                                      /* UART3接收引脚                */                                             
#define P4_29_FNUC            P4_29_GPIO                                               
/*********************************************************************************************************
**  P10  The Trace Port Interface Unit (TPIU)
*********************************************************************************************************/
//bit[3]
#define TPIU_Disable          0x00                                     /* TPIU interface 禁止          */
#define TPIU_Enable           0x01                                     /* TPIU interface 使能          */
#define P10_3_FNUC            TPIU_Disable
/*********************************************************************************************************
** 引脚内部上下拉电阻配置
*********************************************************************************************************/
#define PIN_PULL_UP           0x00                                      /* 引脚内部上拉                 */
#define PIN_REPEATER          0x01                                      /* 引脚内部上拉                 */
#define PIN_NO_PULL           0x02                                      /* 引脚既不上拉，也不下拉       */
#define PIN_PULL_DOWN         0x03                                      /* 引脚内部下拉                 */
//P0
#define P0_0_MODE             PIN_PULL_UP
#define P0_1_MODE             PIN_PULL_UP
#define P0_2_MODE             PIN_PULL_UP
#define P0_3_MODE             PIN_PULL_UP
#define P0_4_MODE             PIN_PULL_UP
#define P0_5_MODE             PIN_PULL_UP
#define P0_6_MODE             PIN_PULL_UP
#define P0_7_MODE             PIN_PULL_UP
#define P0_8_MODE             PIN_PULL_UP
#define P0_9_MODE             PIN_PULL_UP
#define P0_10_MODE            PIN_PULL_UP
#define P0_11_MODE            PIN_PULL_UP
#define P0_12_MODE            PIN_PULL_UP
#define P0_13_MODE            PIN_PULL_UP
#define P0_14_MODE            PIN_PULL_UP
#define P0_15_MODE            PIN_PULL_UP
#define P0_16_MODE            PIN_PULL_UP
#define P0_17_MODE            PIN_PULL_UP
#define P0_18_MODE            PIN_PULL_UP
#define P0_19_MODE            PIN_PULL_UP
#define P0_20_MODE            PIN_PULL_UP
#define P0_21_MODE            PIN_PULL_UP
#define P0_22_MODE            PIN_PULL_UP
#define P0_23_MODE            PIN_PULL_UP
#define P0_24_MODE            PIN_PULL_UP
#define P0_25_MODE            PIN_PULL_UP
#define P0_26_MODE            PIN_PULL_UP
#define P0_27_MODE            PIN_PULL_UP
#define P0_28_MODE            PIN_PULL_UP
#define P0_29_MODE            PIN_PULL_UP
#define P0_30_MODE            PIN_PULL_UP
#define P0_31_MODE            PIN_PULL_UP
//P1
#define P1_0_MODE             PIN_PULL_UP
#define P1_1_MODE             PIN_PULL_UP
#define P1_2_MODE             PIN_PULL_UP
#define P1_3_MODE             PIN_PULL_UP
#define P1_4_MODE             PIN_PULL_UP
#define P1_5_MODE             PIN_PULL_UP
#define P1_6_MODE             PIN_PULL_UP
#define P1_7_MODE             PIN_PULL_UP 
#define P1_8_MODE             PIN_PULL_UP
#define P1_9_MODE             PIN_PULL_UP
#define P1_10_MODE            PIN_PULL_UP
#define P1_11_MODE            PIN_PULL_UP
#define P1_12_MODE            PIN_PULL_UP
#define P1_13_MODE            PIN_PULL_UP
#define P1_14_MODE            PIN_PULL_UP
#define P1_15_MODE            PIN_PULL_UP
#define P1_16_MODE            PIN_PULL_UP
#define P1_17_MODE            PIN_PULL_UP    
#define P1_18_MODE            PIN_PULL_UP
#define P1_19_MODE            PIN_PULL_UP
#define P1_20_MODE            PIN_PULL_UP
#define P1_21_MODE            PIN_PULL_UP
#define P1_22_MODE            PIN_PULL_UP
#define P1_23_MODE            PIN_PULL_UP
#define P1_24_MODE            PIN_PULL_UP
#define P1_25_MODE            PIN_PULL_UP
#define P1_26_MODE            PIN_PULL_UP
#define P1_27_MODE            PIN_PULL_UP     
#define P1_28_MODE            PIN_PULL_UP     
#define P1_29_MODE            PIN_PULL_UP     
#define P1_30_MODE            PIN_PULL_UP     
#define P1_31_MODE            PIN_PULL_UP     
// P2
#define P2_0_MODE             PIN_PULL_UP
#define P2_1_MODE             PIN_PULL_UP
#define P2_2_MODE             PIN_PULL_UP
#define P2_3_MODE             PIN_PULL_UP
#define P2_4_MODE             PIN_PULL_UP
#define P2_5_MODE             PIN_PULL_UP
#define P2_6_MODE             PIN_PULL_UP
#define P2_7_MODE             PIN_PULL_UP
#define P2_8_MODE             PIN_PULL_UP
#define P2_9_MODE             PIN_PULL_UP
#define P2_10_MODE            PIN_PULL_UP
#define P2_11_MODE            PIN_PULL_UP
#define P2_12_MODE            PIN_PULL_UP
#define P2_13_MODE            PIN_PULL_UP
#define P2_14_MODE            PIN_PULL_UP
#define P2_15_MODE            PIN_PULL_UP
//P3
#define P3_25_MODE            PIN_PULL_UP
#define P3_26_MODE            PIN_PULL_UP
//P4
#define P4_28_MODE            PIN_PULL_UP     
#define P4_29_MODE            PIN_PULL_UP     
		
/*********************************************************************************************************
** 外设控制位在PCONP中定义
*********************************************************************************************************/
#define PCTIM0_Enable         1                                         /* 禁止定时器/计数器0功率/时钟  */
#define PCTIM0_Disable        0                                         /* 使能定时器/计数器0功率/时钟  */
#define PCTIM0_FUNC           PCTIM0_Enable

#define PCTIM1_Enable         1                                         /* 禁止定时器/计数器1功率/时钟  */
#define PCTIM1_Disable        0                                         /* 禁止定时器/计数器1功率/时钟	*/
#define PCTIM1_FUNC           PCTIM1_Enable

#define PCUART0_Enable        1                                         /* 使能UART0功率/时钟控制位     */
#define PCUART0_Disable       0                                         /* 禁止UART0功率/时钟控制位     */
#define PCUART0_FUNC          PCUART0_Enable

#define PCUART1_Enable        1                                         /* 使能UART1功率/时钟控制位	    */
#define PCUART1_Disable       0                                         /* 禁止UART1功率/时钟控制位     */
#define PCUART1_FUNC          PCUART1_Enable

#define PWM1_Enable           1                                         /* 使能PWM1功率/时钟控制位      */
#define PWM1_Disable          0                                         /* 禁止PWM1功率/时钟控制位      */
#define PWM1_FUNC             PWM1_Enable

#define PCI2C0_Enable         1                                         /* 使能I2C0接口功率/时钟控制位  */
#define PCI2C0_Disable        0                                         /* 禁止I2C0接口功率/时钟控制位  */
#define PCI2C0_FUNC           PWM1_Disable

#define PCSPI_Enable          1                                         /* 使能SPI接口功率/时钟控制位	*/
#define PCSPI_Disable         0                                         /* 禁止SPI接口功率/时钟控制位   */
#define PCSPI_FUNC            PCSPI_Enable

#define PCRTC_Enable          1                                         /* 使能RTC功率/时钟控制位       */
#define PCRTC_Disable         0                                         /* 禁止RTC功率/时钟控制位       */
#define PCRTC_FUNC            PCRTC_Disable								

#define PCSSP1_Enable         1                                         /* 使能SSP1接口功率/时钟控制位  */
#define PCSSP1_Disable        0                                         /* 禁止SSP1接口功率/时钟控制位  */
#define PCSSP1_FUNC           PCSSP1_Disable

#define PCAD_Enable           1                                         /* 使能A/D转换器功率/时钟控制位 */
#define PCAD_Disable          0                                         /* 禁止A/D转换器功率/时钟控制位 */
#define PCAD_FUNC             PCAD_Disable

#define PCCAN1_Enable         1                                         /* 使能CAN控制器1功率/时钟控制位*/
#define PCCAN1_Disable        0                                         /* 禁止CAN控制器1功率/时钟控制位*/
#define PCCAN1_FUNC           PCCAN1_Disable

#define PCCAN2_Enable         1                                         /* 使能CAN控制器2功率/时钟控制位*/
#define PCCAN2_Disable        0                                         /* 禁止CAN控制器2功率/时钟控制位*/
#define PCCAN2_FUNC           PCCAN2_Disable

#define PCGPIO_Enable         1                                         /* 使能GPIO	                    */
#define PCGPIO_Disable        0                                         /* 禁止GPIO                 	*/
#define PCGPIO_FUNC           PCGPIO_Enable

#define PCRIT_Enable          1                                         /* 使能重复中断定时器		    */
                                                                        /* 功率/时钟控制位              */
#define PCRIT_Disable         0                                         /* 禁止重复中断定时器           */
                                                                        /* 功率/时钟控制位	            */
#define PCRIT_FUNC            PCRIT_Disable

#define PCMC_Enable           1                                         /* 使能电机控制PWM              */
#define PCMC_Disable          0                                         /* 禁止电机控制PWM              */
#define PCMC_FUNC             PCMC_Disable

#define PCQEI_Enable          1                                         /* 使能正交编码器接口           */
                                                                        /* 功率/时钟控制位              */
#define PCQEI_Disable         0                                         /* 禁止正交编码器接口           */
                                                                        /* 功率/时钟控制位              */
#define PCQEI_FUNC            PCQEI_Disable

#define PCI2C1_Enable         1                                         /* 使能I2C1接口功率/时钟控制位  */
#define PCI2C1_Disable        0                                         /* 禁止I2C1接口功率/时钟控制位  */
#define PCI2C1_FUNC           PCI2C1_Enable

#define PCSSP0_Enable         1                                         /* 使能SSP0接口功率/时钟控制位  */
#define PCSSP0_Disable        0                                         /* 禁止SSP0接口功率/时钟控制位  */
#define PCSSP0_FUNC           PCSSP0_Disable

#define PCTIM2_Enable         1                                         /* 使能定时器2功率/时钟控制位   */
#define PCTIM2_Disable        0                                         /* 禁止定时器2功率/时钟控制位	*/
#define PCTIM2_FUNC           PCTIM2_Disable

#define PCTIM3_Enable         1                                         /* 使能定时器3功率/时钟控制位   */
#define PCTIM3_Disable        0                                         /* 禁止定时器3功率/时钟控制位   */
#define PCTIM3_FUNC           PCTIM2_Enable

#define PCUART2_Enable        1                                         /* 使能UART2功率/时钟控制位	    */
#define PCUART2_Disable       0                                         /* 禁止UART2功率/时钟控制位	    */
#define PCUART2_FUNC          PCUART2_Enable

#define PCUART3_Enable        1                                         /* 使能UART3功率/时钟控制位	    */
#define PCUART3_Disable       0                                         /* 禁止UART3功率/时钟控制位	    */
#define PCUART3_FUNC          PCUART3_Enable

#define PCI2C2_Enable         1                                         /* 使能I2C接口2功率/时钟控制位  */
#define PCI2C2_Disable        0                                         /* 禁止I2C接口2功率/时钟控制位	*/
#define PCI2C2_FUNC           PCI2C2_Enable

#define PCI2S_Enable          1                                         /* 使能I2S接口功率/时钟控制位   */
#define PCI2S_Disable         0                                         /* 禁止I2S接口功率/时钟控制位   */
#define PCI2S_FUNC            PCI2S_Disable

#define PCGPDMA_Enable        1                                         /* 使能GP DMA功能功率/时钟控制位*/
#define PCGPDMA_Disable       0                                         /* 禁止GP DMA功能功率/时钟控制位*/
#define PCGPDMA_FUNC          PCGPDMA_Disable

#define PCENET_Enable         1                                         /* 使能以太网模块功率/时钟控制位*/
#define PCENET_Disable        0                                         /* 禁止以太网模块功率/时钟控制位*/
#define PCENET_FUNC           PCENET_Disable

#define PCUSB_Enable          1                                         /* 使能USB接口功率/时钟控制位   */
#define PCUSB_Disable         0                                         /* 禁止USB接口功率/时钟控制位	*/
#define PCUSB_FUNC            PCUSB_Disable

/*********************************************************************************************************
** Function name:     void pinInit
** Descriptions:      初始化所有的引脚配置，完成引脚连接、上下拉电阻设置
**                    注意：需事先在 LPC1700PinCfg.h 头文件中选择好相应管脚的功能
** Input parameters:  无
** Output parameters: 无
** Returned value:    无
*********************************************************************************************************/
extern void pinInit(void);
/*********************************************************************************************************
** Function Name:     pconpInit
** Descriptions:      外设功能初始化：1 表示对应外设使能;0 表示对应外设禁止
** Input parameters:  无
** Output parameters: 无
** Returned value:    无              
*********************************************************************************************************/
extern void pconpInit(void);
#endif           
/**************************************End Of File*******************************************************/
