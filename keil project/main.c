#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Buzzer.h"
#include "Timer0.h"

unsigned char KeyNumber = 0;
unsigned char drinkCount = 0;   // 喝水次数（0~6）
volatile unsigned int  timerCount=0;  
volatile unsigned char remindFlag= 0;  
void main()
{
		
   P0=0x3F;//数码管初始值为0
	 P2=0xFF;//LED全灭
	Timer0Init();
	while(1)
	{
  if(remindFlag == 1)
{
    unsigned char i;
    remindFlag = 0;
    
    for(i = 0; i < 100; i++)      // 循环100次
    {
        Buzzer_Time(5);           // 每次都响
        
        if(Key() == 2)            // 按了按键2就停止
        {
            timerCount = 0;
            break;                // 退出循环
        }
    }
}

		// ② 按键检测与处理
		KeyNumber = Key();
		if(KeyNumber == 1)       // 按下按键1（P3_1）
		{
			//    // 清除提醒
			timerCount = 0;      // 重置计时
			drinkCount++;
			if(drinkCount > 6)
			{
				drinkCount = 0;
				Buzzer_Time(50);
			}
			else if(drinkCount == 6)
			{
				// 完成6杯，庆祝三声
				Buzzer_Time(100);
				Delay(50);
				Buzzer_Time(100);
				Delay(50);
				Buzzer_Time(100);
			}
			else  // drinkCount: 1~5
			{
				Buzzer_Time(20);
			}
		}
			else if(KeyNumber == 2) 
				
			{	
				remindFlag  = 0; 
				timerCount = 0;
				
				}
			

			// ③ 数码管显示
			switch(drinkCount)
			{
				case 0: P0 = 0x3F; break;   // 显示0
				case 1: P0 = 0x06; break;   // 显示1
				case 2: P0 = 0x5B; break;   // 显示2
				case 3: P0 = 0x4F; break;   // 显示3
				case 4: P0 = 0x66; break;   // 显示4
				case 5: P0 = 0x6D; break;   // 显示5
				case 6: P0 = 0x7D; break;   // 显示6
				default: break;
			}
		}
	}


// ④ 定时器0中断服务函数（1ms定时，10秒不按键则提醒）
void Timer0_Routine() interrupt 1
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
			remindFlag = 1; 			// 置位提醒标志
			}
}
			


}