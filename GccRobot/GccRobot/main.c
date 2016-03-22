/*
 * GccApplication4.c
 *
 * Created: 2016/3/19 18:15:28
 *  Author: x
 */ 


#define F_CPU 16000000UL//晶振频率
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "Oled.h"
#include "ADC.h"
#include "servo.h"
#include "robot.h"
#include "Bluetooth_serial.h "

void port_init(void);
unsigned char bb=0;

float Battery_voltage;     
int main(void)
{   port_init();
	OledInit ();
	timer1_init();
	adc_init();
	USART_Init(0x08);
	_delay_ms(10);
	
    while(1)
    { 
		USART_Receive();//读取串口数据
		Battery_voltage=adc_read(6)/102.40;
		if (RX_Flag==1) //如果有新数据
		{   RX_Flag=0;
			TX_Data=RX_Data;
			
			bb++;
		    USART_Transmit(TX_Data);	//发送串口数据
		}
		
	rest(RX_Data);
	if ((RX_Data==0x00)||(Battery_voltage<7.0))	
	{ off_servo();
	  if (Battery_voltage<7.0){DisplayChar_16X08(36,2,"~(zzz)~") ;}
	  else{DisplayChar_16X08(36,2,"~(@o@)~") ;	 }
	}
	
if ((Battery_voltage>8.0)&&(!(RX_Data==0x00)))
	{DisplayChar_16X08(36,2,"~(^o^)~") ;	 
	}
else if ((Battery_voltage>7.0)&&(!(RX_Data==0x00)))
{DisplayChar_16X08(36,2,"~(=o=)~") ;	
}
		
			
	if (RX_Data==0x01)//站立
	{ open_servo();
	  robot_stand(0,-90);
	}
	if (RX_Data==0x02)//左转
	{robot_move(0,0,40,-90,90,100);}
	if (RX_Data==0x03)//右转
	{ robot_move(0,0,-40,-90,90,100);}	
	if (RX_Data==0x04)//前进
	{ robot_move(0,40,0,-90,90,100);}	
    if (RX_Data==0x05)//后退
	{robot_move(0,-40,0,-90,90,100);}
	 if (RX_Data==0x06)//
	 {robot_Sur_Place(1,-90,90,100);}
	 if (RX_Data==0x07)//
	 {robot_move(40,0,0,-90,90,100);}
	 if (RX_Data==0x08)//
	 {robot_move(40,0,0,-90,90,100);}
	 if (RX_Data==0x09)//
	 {robot_move(20,20,0,-90,90,100);}
		
		
		//DisplayChar_16X08(36,2,"~(@o@)~") ;	 	 
	
     Cache_MDigit5(RX_Data,6,0,1 );Cache_MDigit5(Battery_voltage*100,6,88,1 );
		
		// OledDispPicture(0,32,64,512,Expression1);//爱心
	 //   OledDispPicture(0,26,75,600,Expression2);//笑脸
        //TODO:: Please write your application code
		//time_seve++; 
    }
}

void port_init(void)
{
	DDRB = 0xff;        //pb4 0 miso ????11110111
	PORTB= 0xff;
	DDRC = 0xff; 		   //PC输入
	PORTC= 0xff; 		 // 无电阻 减少干扰
	DDRD = 0xFE;              //???3??????????
	PORTD=0xf0;//这个端口设置如果放到后面单独开启这个蓝牙模块  不响应不知道为什么
}



