/*
 * GccApplication4.c
 *
 * Created: 2016/3/19 18:15:28
 *  Author: x
 */ 


#define F_CPU 16000000UL//����Ƶ��
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
		USART_Receive();//��ȡ��������
		Battery_voltage=adc_read(6)/102.40;
		if (RX_Flag==1) //�����������
		{   RX_Flag=0;
			TX_Data=RX_Data;
			
			bb++;
		    USART_Transmit(TX_Data);	//���ʹ�������
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
		
			
	if (RX_Data==0x01)//վ��
	{ open_servo();
	  robot_stand(0,-90);
	}
	if (RX_Data==0x02)//��ת
	{robot_move(0,0,40,-90,90,100);}
	if (RX_Data==0x03)//��ת
	{ robot_move(0,0,-40,-90,90,100);}	
	if (RX_Data==0x04)//ǰ��
	{ robot_move(0,40,0,-90,90,100);}	
    if (RX_Data==0x05)//����
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
		
		// OledDispPicture(0,32,64,512,Expression1);//����
	 //   OledDispPicture(0,26,75,600,Expression2);//Ц��
        //TODO:: Please write your application code
		//time_seve++; 
    }
}

void port_init(void)
{
	DDRB = 0xff;        //pb4 0 miso ????11110111
	PORTB= 0xff;
	DDRC = 0xff; 		   //PC����
	PORTC= 0xff; 		 // �޵��� ���ٸ���
	DDRD = 0xFE;              //???3??????????
	PORTD=0xf0;//����˿���������ŵ����浥�������������ģ��  ����Ӧ��֪��Ϊʲô
}



