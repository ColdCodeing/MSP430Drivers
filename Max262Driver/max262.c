#include "max262.h"

void delay_us(unsigned int time)
    {
      unsigned int k;
//      for(i=0;i<2;i++)
        for(k=0;k<time;k++)
        {
        	_NOP();
    	  _NOP();
        }
    }

void Delay(unsigned int time)
{
  unsigned int i,k;
  for(i=0;i<255;i++)
    for(k=0;k<time;k++)
      _NOP();
}

/*******************************************
函数名称：MAX262_Init
功    能：将430与MAX262接口初始化
参    数：无
返回值  ：无
********************************************/

void MAX262_Init(void)
{
	P1DIR |= BIT6;
	P2DIR |= BIT7;
	P3DIR |= BIT2 + BIT3 + BIT4	;
	P6DIR |= BIT5 + BIT6;
}

/*******************************************
函数名称：WriteAddr
功    能：向MAX262写入地址信号
参    数：uchar addr.参考MAX262官方PDF,地址范围[0:15]
          超出地址范围默认写入地址0
返回值  ：无
********************************************/

void WriteAddr(uchar addr)
{
  switch(addr)
  {
    case 0:{Addr3_L;Addr2_L;Addr1_L;Addr0_L;break;}
    case 1:{Addr3_L;Addr2_L;Addr1_L;Addr0_H;break;}
    case 2:{Addr3_L;Addr2_L;Addr1_H;Addr0_L;break;}
    case 3:{Addr3_L;Addr2_L;Addr1_H;Addr0_H;break;}
    case 4:{Addr3_L;Addr2_H;Addr1_L;Addr0_L;break;}
    case 5:{Addr3_L;Addr2_H;Addr1_L;Addr0_H;break;}
    case 6:{Addr3_L;Addr2_H;Addr1_H;Addr0_L;break;}
    case 7:{Addr3_L;Addr2_H;Addr1_H;Addr0_H;break;}
    case 8:{Addr3_H;Addr2_L;Addr1_L;Addr0_L;break;}
    case 9:{Addr3_H;Addr2_L;Addr1_L;Addr0_H;break;}
    case 10:{Addr3_H;Addr2_L;Addr1_H;Addr0_L;break;}
    case 11:{Addr3_H;Addr2_L;Addr1_H;Addr0_H;break;}
    case 12:{Addr3_H;Addr2_H;Addr1_L;Addr0_L;break;}
    case 13:{Addr3_H;Addr2_H;Addr1_L;Addr0_H;break;}
    case 14:{Addr3_H;Addr2_H;Addr1_H;Addr0_L;break;}
    case 15:{Addr3_H;Addr2_H;Addr1_H;Addr0_H;break;}
    default:{Addr3_L;Addr2_L;Addr1_L;Addr0_L;break;}
  }
  delay_us(2);
}

/*******************************************
函数名称：WriteData
功    能：向MAX262写入数据
参    数：uchar data.参考MAX262官方PDF,数据范围[0:3]
          超出数据范围默认写入0
返回值  ：无
********************************************/

void WriteData(uchar data)
{
  DataWR_L;
  delay_us(2);
  switch(data)
  {
    case 0:{Data1_L;Data0_L;break;}
    case 1:{Data1_L;Data0_H;break;}
    case 2:{Data1_H;Data0_L;break;}
    case 3:{Data1_H;Data0_H;break;}
    default:{Data1_L;Data0_L;break;}
  }
  delay_us(2);
  DataWR_H;
  delay_us(2);
}

/*******************************************
函数名称：SetAMode
功    能：设置MAX262滤波器A工作模式
参    数：uchar mode.参考MAX262官方PDF,数据范围[0:3]
返回值  ：无
********************************************/

void  SetAMode(uchar mode)
{
  WriteAddr(0);
  WriteData(mode);
}

/*******************************************
函数名称：SetAF
功    能：设置MAX262滤波器A的频率f
参    数：uchar freq.参考MAX262官方PDF,数据范围[0:63]
返回值  ：无
********************************************/

void  SetAF(uchar freq)
{
  uchar temp;
  WriteAddr(1);
  temp=freq&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(2);
  temp=(freq>>2)&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(3);
  temp=(freq>>4)&(BIT0+BIT1);
  WriteData(temp);
}

/*******************************************
函数名称：SetAQ
功    能：设置MAX262滤波器A的Q
参    数：uchar Qvalue.参考MAX262官方PDF,数据范围[0:127]
返回值  ：无
********************************************/

void  SetAQ(uchar Qvalue)
{
  uchar temp;
  WriteAddr(4);
  temp=Qvalue&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(5);
  temp=(Qvalue>>2)&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(6);
  temp=(Qvalue>>4)&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(6);
  temp=(Qvalue>>6)&(BIT0);
  WriteData(temp);
}

/*******************************************
函数名称：SetBMode
功    能：设置MAX262滤波器B工作模式
参    数：uchar mode.参考MAX262官方PDF,数据范围[0:3]
返回值  ：无
********************************************/

void  SetBMode(uchar mode)
{
  WriteAddr(8);
  WriteData(mode);
}

/*******************************************
函数名称：SetBF
功    能：设置MAX262滤波器B的频率f
参    数：uchar freq.参考MAX262官方PDF,数据范围[0:63]
返回值  ：无
********************************************/

void  SetBF(uchar freq)
{
  uchar temp;
  WriteAddr(9);
  temp=freq&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(10);
  temp=(freq>>2)&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(11);
  temp=(freq>>4)&(BIT0+BIT1);
  WriteData(temp);
}

/*******************************************
函数名称：SetBQ
功    能：设置MAX262滤波器B的Q
参    数：uchar Qvalue.参考MAX262官方PDF,数据范围[0:127]
返回值  ：无
********************************************/

void  SetBQ(uchar Qvalue)
{
  uchar temp;
  WriteAddr(12);
  temp=Qvalue&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(13);
  temp=(Qvalue>>2)&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(14);
  temp=(Qvalue>>4)&(BIT0+BIT1);
  WriteData(temp);
  WriteAddr(15);
  temp=(Qvalue>>6)&(BIT0);
  WriteData(temp);
}

/*******************************************
函数名称：ComputeFN
功    能：计算MAX262中心频率或拐点频率f0对应的控制字
参    数：uchar mode,long int fclk,float f0.
          mode 范围[0-3],fclk单位为HZ,范围[40-4000000],
          f0单位为HZ,范围[1-100000]
          fclk,f0具体可用范围需参考MAX262官方PDF
返回值  ：uchar。中心频率对应的控制字。范围[0-63]
********************************************/
uchar ComputeFN(uchar mode,long int fclk,long int f0)
{
  if(mode==1)
    return ((float)((fclk/f0)/1.11072)-26);
  else
    return ((float)((fclk*2/f0)/PI)-26);
}

/*******************************************
函数名称：ComputeQN
功    能：计算MAX262的Q值对应的控制字QN
参    数：uchar mode,float Q.
          mode 范围[0-3],Q范围[0.5-64],
          Q值具体范围需参考MAX262官方PDF
返回值  ：uchar。Q值 对应的控制字。范围[0-127]
********************************************/

uchar ComputeQN(uchar mode,float Q)
{
  if(mode==1)
    return (128-(float)(90.51/Q));
  else
    return (128-(float)(64/Q));
}
/*******************************************
函数名称：LPSet 需要DDS
功    能：通过查表设置低通滤波时钟频率
参    数：uchar f0。范围[1,20]，单位KHZ
返回值  ：无
********************************************/
void LPSet(uchar a,uchar b,uchar c,uchar d)
{
  SetAMode(0);
  SetAF(a);
  SetAQ(c);
  SetBMode(0);
  SetBF(b);
  SetBQ(d);
}
