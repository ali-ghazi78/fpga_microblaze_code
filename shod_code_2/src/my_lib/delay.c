
void delay_ms(unsigned long int  _ms)
{
	unsigned long int i=0,k=0,j=0;
	for( ;i<10000;i++)
		for( ;k<10000;k++)
			for(;j<2500*_ms;j++);
}
void delay_ns(unsigned long int _ns)
{
	unsigned long int j=0;
	for(;j<_ns/10000;j++);
}
