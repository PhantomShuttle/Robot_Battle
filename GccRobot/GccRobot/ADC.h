/********AD转换初始化********/
void adc_init(void)
{   ADCSRA = 0x00;  //ADC控制和状态寄存器清零
	ADMUX = 0x46; //2.56V 的片内基准电压源， AREF 引脚外加滤波电容 模拟通道6
	ACSR=1<<ACD;//模拟比较器禁用
	ADCSRA = 0x83;  // ADC 使能,8分频因子
}

/********AD转换********/
unsigned int adc_read(unsigned char ADCChannel)
{ unsigned int data;unsigned char i;
	ADMUX = (ADMUX & 0xf0)+(ADCChannel & 0x0f);
	data = 0;
	for (i=0;i<4;i++)                        //??????
	{     ADCSRA|=0x40;                   //??????
		while ((ADCSRA&0x10)==0);       //???????
		ADCSRA&=0xEF;                   //????λ
		data+=ADC;                        //???????
	}
	data/=4;                              //??????
	return data;
}