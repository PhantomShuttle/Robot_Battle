
#define BRTS BIT3
#define BLEEN BIT2

unsigned int RX_Data=0;
unsigned char RX_Flag=0,TX_Data=0;
void USART_Init( unsigned int baud )
{
	/*���ò�����*/
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* �������뷢����ʹ��*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* ����֡��ʽ: 8 ������λ, 1 ��ֹͣλ */
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
}

void USART_Transmit( unsigned char data )
{
	_delay_ms(1);	//��ʱ��֤�������㹻ʱ����Ӧ
	
	/* �ȴ����ͻ�����Ϊ�� */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* �����ݷ��뻺�������������� */
	UDR0 = data;
	while ( !( UCSR0A & (1<<TXC0)) );
	
}
void USART_Receive( void )
{
	/* �ȴ���������*/
	if( (UCSR0A &0x80)==0x80)
	{
		RX_Data=UDR0;
		RX_Flag=1;
	}
	
	/* �ӻ������л�ȡ����������*/
	//return UDR;
}