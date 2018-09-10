#include <stdlib.h>
#include"usart.h"
#include "mblaze_nt_types.h"
#define base_addr_uart_0 0xce200000
uint32_t reverse(uint32_t x);
void my_putchar(u8 data,uint16_t prescaler);
void delay();

int main()
{

	while(1)
		USART_mWriteSlaveReg0(base_addr_uart_0,USART_SLV_REG0_OFFSET,0xffffffff);

	return 0;
}
void delay()
{
	uint32_t i=0,j=0,k=0;
	for(;i<65000;i++)
		for(;j<65000;j++)
			for(;k<65000;k++);
}
void my_putchar(u8 data,uint16_t prescaler)
{
	//microblaze is big-endian
	uint32_t packet=0;
	uint32_t status=0;
	boolean	transmit_fire=1;

//	  my_usart mm(
//	  .clock(clock),
//	  .reset(Bus2IP_Reset),
//	  .led(led),
//	  .prescaler(slv_reg0[16:31]),
//	  .data(slv_reg0[8:15]),
//	  .tx_pin(tx_pin),
//	  .transmit(slv_reg0[7]),
//	  .uart_busy(slv_output_temp_signal[31])
//	  );

//	prescaler=reverse(prescaler);
//data=reverse(data);

	transmit_fire=0;
	packet|=prescaler;
	packet|=data<<16;
	packet|=(1<<24);

	//transmit input is always 1 .when loading data finished and you wanted to send data make transmit low

	USART_mWriteSlaveReg0(base_addr_uart_0,USART_SLV_REG0_OFFSET,packet);
	packet&=~(1<<24);
	USART_mWriteSlaveReg0(base_addr_uart_0,USART_SLV_REG0_OFFSET,packet);


	//while(!(status&(1)))
	//	status=USART_mReadSlaveReg1(base_addr_uart_0,USART_SLV_REG1_OFFSET);//if 0 is busy if 1 is not busy
	packet=0;
	transmit_fire=1;
	packet|=transmit_fire>>17;
	//USART_mWriteSlaveReg0(base_addr_uart_0,USART_SLV_REG0_OFFSET,0xffffffff);
	//clearing transmit_fire


}
uint32_t reverse(uint32_t x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));

}
