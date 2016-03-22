
/* ʱ�Ӿ���16MHz ռ�ö�ʱ��1 ����ж��ṩ��������8·�������*/

#define servo_01_h PORTD|=0x10//�˿�D4 ���01
#define servo_01_l PORTD&=0xef//

#define servo_02_h PORTD|=0x20//�˿�D5 ���02
#define servo_02_l PORTD&=0xDf//

#define servo_03_h PORTD|=0x40//�˿�D6 ���03
#define servo_03_l PORTD&=0xBf//

#define servo_04_h PORTD|=0x80//�˿�D7 ���04
#define servo_04_l PORTD&=0x7f//

#define servo_05_h PORTB|=0x01//�˿�B0 ���05
#define servo_05_l PORTB&=0xfe//

#define servo_06_h PORTB|=0x02//�˿�B1 ���06
#define servo_06_l PORTB&=0xfd//

#define servo_07_h PORTB|=0x04//�˿�B2 ���07
#define servo_07_l PORTB&=0xfb//

#define servo_08_h PORTB|=0x08//�˿�B3 ���08
#define servo_08_l PORTB&=0xf7//


unsigned int servo_ch[8]={2090,1290,2090,2890,2090,1290,2090,2890},pp=0;
	unsigned int time_seve=0;	
int servo_Direction[8]={10,10,10,-10,10,10,10,-10},//����Ϊ������ ˳ʱ����
	offset_sever=160;//���ƫ������ֵ	
void servo_age(uchar number,int age)
{   int age_t;
	if (age>100){age_t=100;}
	else if (age<-100){age_t=-100;}
	else{age_t=age;}
	servo_ch[number]=servo_Direction[number]*age_t+2000+offset_sever;
}

void off_servo(void)//�رն��
{
	TCCR1B=0x00;
	servo_01_l;servo_02_l;servo_03_l;servo_04_l;
    servo_05_l;servo_06_l;servo_07_l;servo_08_l;
	pp=18;
}

void open_servo(void)//����������
{if (!(TCCR1B==0x02))
   {   pp=0;
	   TCCR1B=0x02;
	}
}
void timer1_init(void)//8·���ռ�ö�ʱ��1
{  SREG = 0x80;
	TCCR1A=0x00;
	TCCR1B=0x02;
	TCCR1C=0x00;		// T/C1��������ͨģʽ��8��Ƶ
	TIMSK1=0x01;        //����ж�ʹ��
	TCNT1=0x0BDC;
}

ISR(TIMER1_OVF_vect)//8·������
{
	switch(pp)
	{
		case 0:servo_01_h;TCNT1=64535-servo_ch[0];pp=1;break;//���1 2.5ms  3250
		case 1:servo_01_l;TCNT1=61535+servo_ch[0];pp=2;break;
		
		case 2:servo_02_h;TCNT1=64535-servo_ch[1];pp=3;break;//���2 5ms
		case 3:servo_02_l;TCNT1=61535+servo_ch[1];pp=4;break;
		
		case 4:servo_03_h;TCNT1=64535-servo_ch[2];pp=5;break;//���3 7.5ms
		case 5:servo_03_l;TCNT1=61535+servo_ch[2];pp=6;break;
		
		case 6:servo_04_h;TCNT1=64535-servo_ch[3];pp=7;break;//���4 10ms
		case 7:servo_04_l;TCNT1=61535+servo_ch[3];pp=8;break;
		
		case 8:servo_05_h;TCNT1=64535-servo_ch[4];pp=9;break;//���5 12.5ms
		case 9:servo_05_l;TCNT1=61535+servo_ch[4];pp=10;break;
		
		case 10:servo_06_h;TCNT1=64535-servo_ch[5];pp=11;break;//���6 15ms
		case 11:servo_06_l;TCNT1=61535+servo_ch[5];pp=12;break;
		
		case 12:servo_07_h;TCNT1=64535-servo_ch[6];pp=13;break;//���7 15ms
		case 13:servo_07_l;TCNT1=61535+servo_ch[6];pp=14;break;
		
		case 14:servo_08_h;TCNT1=64535-servo_ch[7];pp=15;break;//���6 15ms
		case 15:servo_08_l;TCNT1=61535+servo_ch[7];pp=0; time_seve++;break;
		
		default:TCNT1=65535;pp=0;break;
		
	}
	
}