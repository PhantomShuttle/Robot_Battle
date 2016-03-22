
#define BRTS BIT3
#define BLEEN BIT2

unsigned int RX_Data=0;
unsigned char RX_Flag=0,TX_Data=0;
void USART_Init( unsigned int baud )
{
	/*设置波特率*/
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* 接收器与发送器使能*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* 设置帧格式: 8 个数据位, 1 个停止位 */
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
}

void USART_Transmit( unsigned char data )
{
	_delay_ms(1);	//延时保证蓝牙有足够时间相应
	
	/* 等待发送缓冲器为空 */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* 将数据放入缓冲器，发送数据 */
	UDR0 = data;
	while ( !( UCSR0A & (1<<TXC0)) );
	
}
void USART_Receive( void )
{
	/* 等待接收数据*/
	if( (UCSR0A &0x80)==0x80)
	{
		RX_Data=UDR0;
		RX_Flag=1;
	}
	
	/* 从缓冲器中获取并返回数据*/
	//return UDR;
}