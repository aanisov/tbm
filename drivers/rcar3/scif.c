#include "sys.h"

#define SCIF_SCFTDR    (0x0C)    /* Transmit FIFO data register    */
#define SCIF_SCFSR     (0x10)    /* Serial status register         */

#define SCFSR_TEND    (1 << 6)    /* Transmission End */
#define SCFSR_TDFE    (1 << 5)    /* Transmit FIFO Data Empty */

#define RCAR3_SCIF2_BASE 0xe6e88000


static int __uart_putchar(int c)
{
	uint16_t status;
    phys_addr_t base = RCAR3_SCIF2_BASE;

	/* Wait for an empty slot.  */
	do {
		status = readw(base + SCIF_SCFSR);
	} while ( !(status & SCFSR_TDFE) );

	writeb(base + SCIF_SCFTDR, c);
    writew(base + SCIF_SCFSR, readw(base + SCIF_SCFSR) &
                 ~(SCFSR_TEND | SCFSR_TDFE));
	return c;
}

int uart_putchar(int c)
{
    __uart_putchar(c);
    if (c == '\n')
        __uart_putchar('\r');
    return c;
}

void uart_init(void)
{
}

