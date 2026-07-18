#include <REGX52.H>

void Timer0Init(void)
{
	TMOD &= 0xF0;		// 清除Timer0配置位
	TMOD |= 0x01;		// 设置Timer0为模式1（16位定时器）
	TL0 = 0x66;		// 低8位初值（与ISR重载值一致）
	TH0 = 0xFC;		// 高8位初值（与ISR重载值一致）
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

// 中断服务函数 Timer0_Routine() 
/*void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	if(T0Count >= 1000)       // 1000ms = 1秒
	{
		T0Count = 0;
		timerCount++;
		if(timerCount >= 10)  // 10秒到
		{
			timerCount = 0;
			remindFlag = 1;   // 置位提醒标志
		}
	}
}*/
// 定时1ms，计时10秒后置 remindFlag=1 触发喝水提醒
