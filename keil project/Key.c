#include <REGX52.H>
#include "Delay.h"

/**
  * @brief  获取独立按键键码
  * @param  无
  * @retval 按下按键的键码，范围：0~4，无按键按下时返回 0
  * @note   带软件消抖和按键松开检测，保证每次按下只返回一次
  */
unsigned char Key(void)
{
    unsigned char KeyNumber = 0;

    if(P3_1 == 0)               // 按键1（P3_1）
    {
        Delay(20);              // 消抖
        while(P3_1 == 0);       // 等待按键松开
        Delay(20);              // 再次消抖
        KeyNumber = 1;
    }
    if(P3_0 == 0)               // 按键2（P3_0）
    {
        Delay(20);
        while(P3_0 == 0);
        Delay(20);
        KeyNumber = 2;
    }
    if(P3_2 == 0)               // 按键3（P3_2）
    {
        Delay(20);
        while(P3_2 == 0);
        Delay(20);
        KeyNumber = 3;
    }
    if(P3_3 == 0)               // 按键4（P3_3）
    {
        Delay(20);
        while(P3_3 == 0);
        Delay(20);
        KeyNumber = 4;
    }

    return KeyNumber;
}
