#include <REGX52.H>
#include "Timer0.h"

// 定时器相关全局变量（供 main.c 使用，见 Timer0.h 的 extern 声明）
volatile unsigned int  timerCount = 0;   // 秒计数，每1秒加1，到10秒触发提醒
volatile unsigned char remindFlag = 0;   // 提醒标志，1 表示需要提醒

/**
  * @brief  定时器0初始化（1ms定时）
  * @param  无
  * @retval 无
  */
void Timer0Init(void)
{
    TMOD &= 0xF0;       // 清除定时器0的配置位
    TMOD |= 0x01;       // 定时器0设为模式1（16位定时器）
    TL0 = 0x66;         // 1ms定时初值低8位
    TH0 = 0xFC;         // 1ms定时初值高8位
    TF0 = 0;            // 清除溢出标志
    TR0 = 1;            // 启动定时器0
    ET0 = 1;            // 允许定时器0中断
    EA  = 1;            // 开启总中断
    PT0 = 0;            // 定时器0使用默认（低）优先级
}

/**
  * @brief  定时器0中断服务函数
  * @param  无
  * @retval 无
  * @note   每1ms进入一次；累计1秒，10秒无操作则置 remindFlag=1
  */
void Timer0_Routine(void) interrupt 1
{
    static unsigned int T0Count = 0;

    TL0 = 0x66;         // 重装定时初值
    TH0 = 0xFC;

    T0Count++;
    if(T0Count >= 1000)         // 1000ms = 1秒
    {
        T0Count = 0;
        timerCount++;
        if(timerCount >= 10)    // 10秒到
        {
            timerCount = 0;
            remindFlag = 1;     // 置位提醒标志
        }
    }
}
