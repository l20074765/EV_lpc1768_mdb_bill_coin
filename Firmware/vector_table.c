/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info-------------------------------------------------------------------------------
** File name:           vector_table.c
** Last modified Date:  2009-07-22
** Last Version:        V1.00
** Descriptions:        lpc1000异常向量表                      
**------------------------------------------------------------------------------------------------------
** Created by:          chenmingji
** Created date:        2009-07-22
** Version:             V1.00
** Descriptions:        The original version
********************************************************************************************************/
#include  "..\config.h"
#include  "vector_cfg.h"
/*********************************************************************************************************
  外部函数定义
*********************************************************************************************************/
extern void __main(void);
extern void sysTickIsr(void);
/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
#if CRP_LEVEL != 0 && CRP_LEVEL != 1 && CRP_LEVEL != 2 && CRP_LEVEL != 3
    #error  "CRP_LEVEL must 0,1,2,3!"
#endif                                                                  /*  CRP_LEVEL                   */

#if CRP_LEVEL == 0

#if VECTOR_TABLE_IN_FLASH > 0

void *const __GpvVectorTable[] = {
   (void *)RAM_TOP,
   (void *)__main,
   (void *)(NMI_HANDLE),
   (void *)(HARD_FAULT_HANDLE),
   (void *)(MEM_MANAGE_FAULT_HANDLE),
   (void *)(BUS_FAULT_HANDLE),
   (void *)(USAGE_FAULT_HANDLE),
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)(SVCALL_HANDLE),

   (void *)(DEBUG_MON_HANDLE),
    NULL,
   (void *)(PEND_SV_HANDLE),
   (void *)(SYS_TICK_HANDLE),

   (void *)IRQ_16_HANDLE,
   (void *)IRQ_17_HANDLE,
   (void *)IRQ_18_HANDLE,
   (void *)IRQ_19_HANDLE,

   (void *)IRQ_20_HANDLE,
   (void *)IRQ_21_HANDLE,
   (void *)IRQ_22_HANDLE,
   (void *)IRQ_23_HANDLE,
   (void *)IRQ_24_HANDLE,
   (void *)IRQ_25_HANDLE,
   (void *)IRQ_26_HANDLE,
   (void *)IRQ_27_HANDLE,
   (void *)IRQ_28_HANDLE,
   (void *)IRQ_29_HANDLE,

   (void *)IRQ_30_HANDLE,
   (void *)IRQ_31_HANDLE,
   (void *)IRQ_32_HANDLE,
   (void *)IRQ_33_HANDLE,
   (void *)IRQ_34_HANDLE,
   (void *)IRQ_35_HANDLE,
   (void *)IRQ_36_HANDLE,
   (void *)IRQ_37_HANDLE,
   (void *)IRQ_38_HANDLE,
   (void *)IRQ_39_HANDLE,

   (void *)IRQ_40_HANDLE,
   (void *)IRQ_41_HANDLE,
   (void *)IRQ_42_HANDLE,
   (void *)IRQ_43_HANDLE,
   (void *)IRQ_44_HANDLE,
   (void *)IRQ_45_HANDLE,
   (void *)IRQ_46_HANDLE,
   (void *)IRQ_47_HANDLE,
   (void *)IRQ_48_HANDLE,
   (void *)IRQ_49_HANDLE,

   (void *)IRQ_50_HANDLE

};

#else

void *const __GpvVectorRom[] = {
   (void *)RAM_TOP,
   (void *)__main,
   (void *)(NMI_HANDLE),
   (void *)(HARD_FAULT_HANDLE),
   (void *)(MEM_MANAGE_FAULT_HANDLE),
   (void *)(BUS_FAULT_HANDLE),
   (void *)(USAGE_FAULT_HANDLE),
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)(SVCALL_HANDLE)
};

void *__GpvVectorTable[MAX_VICS] = {
   (void *)RAM_TOP,
   (void *)__main,
   (void *)(NMI_HANDLE),
   (void *)(HARD_FAULT_HANDLE),
   (void *)(MEM_MANAGE_FAULT_HANDLE),
   (void *)(BUS_FAULT_HANDLE),
   (void *)(USAGE_FAULT_HANDLE),
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)(SVCALL_HANDLE)

};

#endif                                                                  /*  VECTOR_TABLE_IN_FLASH       */

#else

#if VECTOR_TABLE_IN_FLASH == 1
void *const __GpvVectorTable[] = {
#else
void *const __GpvVectorRom[] = {
#endif                                                                  /*  VECTOR_TABLE_IN_FLASH       */
   (void *)RAM_TOP,
   (void *)__main,
   (void *)(NMI_HANDLE),
   (void *)(HARD_FAULT_HANDLE),
   (void *)(MEM_MANAGE_FAULT_HANDLE),
   (void *)(BUS_FAULT_HANDLE),
   (void *)(USAGE_FAULT_HANDLE),
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)(SVCALL_HANDLE),
   (void *)(DEBUG_MON_HANDLE),
    NULL,
   (void *)(PEND_SV_HANDLE),
   (void *)(SYS_TICK_HANDLE),

   (void *)IRQ_16_HANDLE,
   (void *)IRQ_17_HANDLE,
   (void *)IRQ_18_HANDLE,
   (void *)IRQ_19_HANDLE,

   (void *)IRQ_20_HANDLE,
   (void *)IRQ_21_HANDLE,
   (void *)IRQ_22_HANDLE,
   (void *)IRQ_23_HANDLE,
   (void *)IRQ_24_HANDLE,
   (void *)IRQ_25_HANDLE,
   (void *)IRQ_26_HANDLE,
   (void *)IRQ_27_HANDLE,
   (void *)IRQ_28_HANDLE,
   (void *)IRQ_29_HANDLE,

   (void *)IRQ_30_HANDLE,
   (void *)IRQ_31_HANDLE,
   (void *)IRQ_32_HANDLE,
   (void *)IRQ_33_HANDLE,
   (void *)IRQ_34_HANDLE,
   (void *)IRQ_35_HANDLE,
   (void *)IRQ_36_HANDLE,
   (void *)IRQ_37_HANDLE,
   (void *)IRQ_38_HANDLE,
   (void *)IRQ_39_HANDLE,

   (void *)IRQ_40_HANDLE,
   (void *)IRQ_41_HANDLE,
   (void *)IRQ_42_HANDLE,
   (void *)IRQ_43_HANDLE,
   (void *)IRQ_44_HANDLE,
   (void *)IRQ_45_HANDLE,
   (void *)IRQ_46_HANDLE,
   (void *)IRQ_47_HANDLE,
   (void *)IRQ_48_HANDLE,
   (void *)IRQ_49_HANDLE,

   (void *)IRQ_50_HANDLE,
   (void *)IRQ_51_HANDLE,
   (void *)IRQ_52_HANDLE,
   (void *)IRQ_53_HANDLE,
   (void *)IRQ_54_HANDLE,
   (void *)IRQ_55_HANDLE,
   (void *)IRQ_56_HANDLE,
   (void *)IRQ_57_HANDLE,
   (void *)IRQ_58_HANDLE,
   (void *)IRQ_59_HANDLE,

   (void *)IRQ_60_HANDLE,
   (void *)IRQ_61_HANDLE,
   (void *)IRQ_62_HANDLE,
   (void *)IRQ_63_HANDLE,
   (void *)IRQ_64_HANDLE,
   (void *)IRQ_65_HANDLE,
   (void *)IRQ_66_HANDLE,
   (void *)IRQ_67_HANDLE,
   (void *)IRQ_68_HANDLE,
   (void *)IRQ_69_HANDLE,

   (void *)IRQ_70_HANDLE,
   (void *)IRQ_71_HANDLE,
   (void *)IRQ_72_HANDLE,
   (void *)IRQ_73_HANDLE,
   (void *)IRQ_74_HANDLE,
   (void *)IRQ_75_HANDLE,
   (void *)IRQ_76_HANDLE,
   (void *)IRQ_77_HANDLE,
   (void *)IRQ_78_HANDLE,
   (void *)IRQ_79_HANDLE,

   (void *)IRQ_80_HANDLE,
   (void *)IRQ_81_HANDLE,
   (void *)IRQ_82_HANDLE,
   (void *)IRQ_83_HANDLE,
   (void *)IRQ_84_HANDLE,
   (void *)IRQ_85_HANDLE,
   (void *)IRQ_86_HANDLE,
   (void *)IRQ_87_HANDLE,
   (void *)IRQ_88_HANDLE,
   (void *)IRQ_89_HANDLE,

   (void *)IRQ_90_HANDLE,
   (void *)IRQ_91_HANDLE,
   (void *)IRQ_92_HANDLE,
   (void *)IRQ_93_HANDLE,
   (void *)IRQ_94_HANDLE,
   (void *)IRQ_95_HANDLE,
   (void *)IRQ_96_HANDLE,
   (void *)IRQ_97_HANDLE,
   (void *)IRQ_98_HANDLE,
   (void *)IRQ_99_HANDLE,

   (void *)IRQ_100_HANDLE,
   (void *)IRQ_101_HANDLE,
   (void *)IRQ_102_HANDLE,
   (void *)IRQ_103_HANDLE,
   (void *)IRQ_104_HANDLE,
   (void *)IRQ_105_HANDLE,
   (void *)IRQ_106_HANDLE,
   (void *)IRQ_107_HANDLE,
   (void *)IRQ_108_HANDLE,
   (void *)IRQ_109_HANDLE,

   (void *)IRQ_110_HANDLE,
   (void *)IRQ_111_HANDLE,
   (void *)IRQ_112_HANDLE,
   (void *)IRQ_113_HANDLE,
   (void *)IRQ_114_HANDLE,
   (void *)IRQ_115_HANDLE,
   (void *)IRQ_116_HANDLE,
   (void *)IRQ_117_HANDLE,
   (void *)IRQ_118_HANDLE,
   (void *)IRQ_119_HANDLE,

   (void *)IRQ_120_HANDLE,
   (void *)IRQ_121_HANDLE,
   (void *)IRQ_122_HANDLE,
   (void *)IRQ_123_HANDLE,
   (void *)IRQ_124_HANDLE,
   (void *)IRQ_125_HANDLE,
   (void *)IRQ_126_HANDLE,
   (void *)IRQ_127_HANDLE,
   (void *)IRQ_128_HANDLE,
   (void *)IRQ_129_HANDLE,

   (void *)IRQ_130_HANDLE,
   (void *)IRQ_131_HANDLE,
   (void *)IRQ_132_HANDLE,
   (void *)IRQ_133_HANDLE,
   (void *)IRQ_134_HANDLE,
   (void *)IRQ_135_HANDLE,
   (void *)IRQ_136_HANDLE,
   (void *)IRQ_137_HANDLE,
   (void *)IRQ_138_HANDLE,
   (void *)IRQ_139_HANDLE,

   (void *)IRQ_140_HANDLE,
   (void *)IRQ_141_HANDLE,
   (void *)IRQ_142_HANDLE,
   (void *)IRQ_143_HANDLE,
   (void *)IRQ_144_HANDLE,
   (void *)IRQ_145_HANDLE,
   (void *)IRQ_146_HANDLE,
   (void *)IRQ_147_HANDLE,
   (void *)IRQ_148_HANDLE,
   (void *)IRQ_149_HANDLE,

   (void *)IRQ_150_HANDLE,
   (void *)IRQ_151_HANDLE,
   (void *)IRQ_152_HANDLE,
   (void *)IRQ_153_HANDLE,
   (void *)IRQ_154_HANDLE,
   (void *)IRQ_155_HANDLE,
   (void *)IRQ_156_HANDLE,
   (void *)IRQ_157_HANDLE,
   (void *)IRQ_158_HANDLE,
   (void *)IRQ_159_HANDLE,

   (void *)IRQ_160_HANDLE,
   (void *)IRQ_161_HANDLE,
   (void *)IRQ_162_HANDLE,
   (void *)IRQ_163_HANDLE,
   (void *)IRQ_164_HANDLE,
   (void *)IRQ_165_HANDLE,
   (void *)IRQ_166_HANDLE,
   (void *)IRQ_167_HANDLE,
   (void *)IRQ_168_HANDLE,
   (void *)IRQ_169_HANDLE,

   (void *)IRQ_170_HANDLE,
   (void *)IRQ_171_HANDLE,
   (void *)IRQ_172_HANDLE,
   (void *)IRQ_173_HANDLE,
   (void *)IRQ_174_HANDLE,
   (void *)IRQ_175_HANDLE,
   (void *)IRQ_176_HANDLE,
   (void *)IRQ_177_HANDLE,
   (void *)IRQ_178_HANDLE,
   (void *)IRQ_179_HANDLE,

   (void *)IRQ_180_HANDLE,
   (void *)IRQ_181_HANDLE,
   (void *)IRQ_182_HANDLE,
   (void *)IRQ_183_HANDLE,
   (void *)IRQ_184_HANDLE,
   (void *)IRQ_185_HANDLE,
   (void *)IRQ_186_HANDLE,
   (void *)IRQ_187_HANDLE,
   (void *)IRQ_188_HANDLE,
   (void *)IRQ_189_HANDLE,

   (void *)IRQ_190_HANDLE,

#if CRP_LEVEL == 0
   (void *)0xffffffff
#endif                                                                  /*  CRP_LEVEL                   */

#if CRP_LEVEL == 1
   (void *)0x12345678
#endif                                                                  /*  CRP_LEVEL                   */

#if CRP_LEVEL == 2
   (void *)0x87654321
#endif                                                                  /*  CRP_LEVEL                   */

#if CRP_LEVEL == 3
   (void *)0x43218765
#endif                                                                  /*  CRP_LEVEL                   */

};

#if VECTOR_TABLE_IN_FLASH == 0
void *__GpvVectorTable[MAX_VICS] = {
   (void *)RAM_TOP,
   (void *)__main,
   (void *)(NMI_HANDLE),
   (void *)(HARD_FAULT_HANDLE),
   (void *)(MEM_MANAGE_FAULT_HANDLE),
   (void *)(BUS_FAULT_HANDLE),
   (void *)(USAGE_FAULT_HANDLE),
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)defaultVectorHandle,
   (void *)(SVCALL_HANDLE)
};

#endif                                                                  /*  VECTOR_TABLE_IN_FLASH       */

#endif                                                                  /*  CRP_LEVEL                   */
/**************************************End Of File*******************************************************/
