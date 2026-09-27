#include <REGX52.H>
#include "Delay.h"

// 蜂鸣器引脚（P2^5）
sbit Buzzer = P2^5;

/**
  * @brief  蜂鸣器发声
  * @param  ms 发声时长（毫秒）
  * @retval 无
  * @note   通过翻转引脚产生方波驱动无源蜂鸣器，周期约2ms，音调约500Hz
  */
void Buzzer_Time(unsigned int ms)
{
    unsigned int i;
    for(i = 0; i < ms; i++)
    {
        Buzzer = !Buzzer;   // 翻转电平产生方波
        Delay(1);           // 约1ms
    }
}
