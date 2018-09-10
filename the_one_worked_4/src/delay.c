
void delay_ms(unsigned long int  _ms)
{
	int i=0,k=0,j=0;
	for( ;i<10000;i++)
		for( ;k<10000;k++)
			for(;j<2500*_ms;j++);
}
void delay_ns(unsigned long int _ns)
{
	int i=0,k=0,j=0;
	for( ;i<100;i++)
		for( ;k<100;k++)
			for(;j<_ns;j++);
}
