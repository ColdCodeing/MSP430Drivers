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
�������ƣ�MAX262_Init
��    �ܣ���430��MAX262�ӿڳ�ʼ��
��    ������
����ֵ  ����
********************************************/

void MAX262_Init(void)
{
	P1DIR |= BIT6;
	P2DIR |= BIT7;
	P3DIR |= BIT2 + BIT3 + BIT4	;
	P6DIR |= BIT5 + BIT6;
}

/*******************************************
�������ƣ�WriteAddr
��    �ܣ���MAX262д���ַ�ź�
��    ����uchar addr.�ο�MAX262�ٷ�PDF,��ַ��Χ[0:15]
          ������ַ��ΧĬ��д���ַ0
����ֵ  ����
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
�������ƣ�WriteData
��    �ܣ���MAX262д������
��    ����uchar data.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:3]
          �������ݷ�ΧĬ��д��0
����ֵ  ����
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
�������ƣ�SetAMode
��    �ܣ�����MAX262�˲���A����ģʽ
��    ����uchar mode.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:3]
����ֵ  ����
********************************************/

void  SetAMode(uchar mode)
{
  WriteAddr(0);
  WriteData(mode);
}

/*******************************************
�������ƣ�SetAF
��    �ܣ�����MAX262�˲���A��Ƶ��f
��    ����uchar freq.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:63]
����ֵ  ����
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
�������ƣ�SetAQ
��    �ܣ�����MAX262�˲���A��Q
��    ����uchar Qvalue.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:127]
����ֵ  ����
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
�������ƣ�SetBMode
��    �ܣ�����MAX262�˲���B����ģʽ
��    ����uchar mode.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:3]
����ֵ  ����
********************************************/

void  SetBMode(uchar mode)
{
  WriteAddr(8);
  WriteData(mode);
}

/*******************************************
�������ƣ�SetBF
��    �ܣ�����MAX262�˲���B��Ƶ��f
��    ����uchar freq.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:63]
����ֵ  ����
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
�������ƣ�SetBQ
��    �ܣ�����MAX262�˲���B��Q
��    ����uchar Qvalue.�ο�MAX262�ٷ�PDF,���ݷ�Χ[0:127]
����ֵ  ����
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
�������ƣ�ComputeFN
��    �ܣ�����MAX262����Ƶ�ʻ�յ�Ƶ��f0��Ӧ�Ŀ�����
��    ����uchar mode,long int fclk,float f0.
          mode ��Χ[0-3],fclk��λΪHZ,��Χ[40-4000000],
          f0��λΪHZ,��Χ[1-100000]
          fclk,f0������÷�Χ��ο�MAX262�ٷ�PDF
����ֵ  ��uchar������Ƶ�ʶ�Ӧ�Ŀ����֡���Χ[0-63]
********************************************/
uchar ComputeFN(uchar mode,long int fclk,long int f0)
{
  if(mode==1)
    return ((float)((fclk/f0)/1.11072)-26);
  else
    return ((float)((fclk*2/f0)/PI)-26);
}

/*******************************************
�������ƣ�ComputeQN
��    �ܣ�����MAX262��Qֵ��Ӧ�Ŀ�����QN
��    ����uchar mode,float Q.
          mode ��Χ[0-3],Q��Χ[0.5-64],
          Qֵ���巶Χ��ο�MAX262�ٷ�PDF
����ֵ  ��uchar��Qֵ ��Ӧ�Ŀ����֡���Χ[0-127]
********************************************/

uchar ComputeQN(uchar mode,float Q)
{
  if(mode==1)
    return (128-(float)(90.51/Q));
  else
    return (128-(float)(64/Q));
}
/*******************************************
�������ƣ�LPSet ��ҪDDS
��    �ܣ�ͨ��������õ�ͨ�˲�ʱ��Ƶ��
��    ����uchar f0����Χ[1,20]����λKHZ
����ֵ  ����
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
