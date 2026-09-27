#include "Delay.h"

/**
  * @brief  软件延时函数
  * @param  xms 延时时间（毫秒）
  * @retval 无
  * @note   基于11.0592MHz晶振的近似延时，每单位约1ms
  */
void Delay(unsigned int xms)
{
    unsigned char i, j;
    while(xms--)
    {
        i = 12;
        j = 169;
        do
        {
            while(--j);
        } while(--i);
    }
}
