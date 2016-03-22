/********ADת����ʼ��********/
void adc_init(void)
{   ADCSRA = 0x00;  //ADC���ƺ�״̬�Ĵ�������
	ADMUX = 0x46; //2.56V ��Ƭ�ڻ�׼��ѹԴ�� AREF ��������˲����� ģ��ͨ��6
	ACSR=1<<ACD;//ģ��Ƚ�������
	ADCSRA = 0x83;  // ADC ʹ��,8��Ƶ����
}

/********ADת��********/
unsigned int adc_read(unsigned char ADCChannel)
{ unsigned int data;unsigned char i;
	ADMUX = (ADMUX & 0xf0)+(ADCChannel & 0x0f);
	data = 0;
	for (i=0;i<4;i++)                        //??????
	{     ADCSRA|=0x40;                   //??????
		while ((ADCSRA&0x10)==0);       //???????
		ADCSRA&=0xEF;                   //????��
		data+=ADC;                        //???????
	}
	data/=4;                              //??????
	return data;
}