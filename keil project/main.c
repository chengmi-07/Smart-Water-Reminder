#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Buzzer.h"
#include "Timer0.h"

// 共阴极数码管段码表：0~6 的显示编码
unsigned char code NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D};

unsigned char drinkCount = 0;   // 喝水次数（0~6）

void main(void)
{
    P0 = 0x3F;      // 数码管初始显示 0
    P2 = 0xFF;      // LED 全灭

    Timer0Init();   // 初始化定时器0（1ms定时）

    while(1)
    {
        // ① 定时提醒：10秒未喝水则蜂鸣器提醒，按按键2停止
        if(remindFlag == 1)
        {
            unsigned char i;
            remindFlag = 0;              // 清除提醒标志

            for(i = 0; i < 100; i++)     // 循环100次（约500ms发声）
            {
                Buzzer_Time(5);          // 每次发声5ms
                if(Key() == 2)           // 按下按键2则停止提醒
                {
                    timerCount = 0;      // 重置计时
                    break;
                }
            }
        }

        // ② 按键检测与处理
        {
            unsigned char KeyNumber = Key();

            if(KeyNumber == 1)           // 按键1（P3_1）：记录一次喝水
            {
                timerCount = 0;          // 重置计时
                drinkCount++;

                if(drinkCount > 6)       // 超过6杯，清零重新开始
                {
                    drinkCount = 0;
                    Buzzer_Time(50);
                }
                else if(drinkCount == 6) // 完成6杯，庆祝三声
                {
                    Buzzer_Time(100);
                    Delay(50);
                    Buzzer_Time(100);
                    Delay(50);
                    Buzzer_Time(100);
                }
                else                     // 1~5杯，短促提示音
                {
                    Buzzer_Time(20);
                }
            }
            else if(KeyNumber == 2)      // 按键2（P3_0）：停止提醒/重置计时
            {
                remindFlag = 0;
                timerCount = 0;
            }
        }

        // ③ 数码管显示当前喝水次数
        P0 = NixieTable[drinkCount];
    }
}
