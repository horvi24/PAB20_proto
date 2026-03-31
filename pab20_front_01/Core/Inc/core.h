#ifndef INC_CORE_H_
#define INC_CORE_H_

#include "include.h"




// printf >> DBG_RX4 (usart4)
#ifdef __GNUC__
// With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
// set to 'Yes') calls __io_putchar()
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif // __GNUC__




#endif /* INC_CORE_H_ */
