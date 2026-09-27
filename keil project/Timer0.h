#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0Init(void);

// 定时器相关全局变量（在 Timer0.c 中定义）
extern volatile unsigned int  timerCount;   // 秒计数
extern volatile unsigned char remindFlag;   // 提醒标志，1 表示需要提醒

#endif
