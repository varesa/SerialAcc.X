/*
 * umpl_nvmem.c
 *
 * Created: 5/2/2011 2: :37 PM
 *  Author: sgurumani
 */ 
#include    "umpl_nvmem.h"
#include	"log.h"
#undef		MPL_LOG_TAG
#define		MPL_LOG_TAG "uMPL-nvmem"


#include    <sysclk.h>
#include    <string.h>
#include	<stdio.h>
//#include	"mlos.h"
#include	"packet.h"

static unsigned int calLength;
static bool calDataFlag = false;
#define MAX_CAL_BUFFER_LEN 60

#define DEBUG_READ_CAL 

/*! \brief Write a buffer to non-volatile RAM
 *
 * This routine writes \c count Bytes to the NVRAM destination pointed
 * to by \c dst from the source buffer pointed to by \c src.
 *
 * \param   dst     the write destination in the NVRAM address space
 * \param   src     the source buffer in program data memory space
 * \param   count   the number of Bytes to write
 *
 * \return  Nothing.
 */
void nvram_write (nvram_addr_t dst, const void * src, size_t count, bool erase)
{
	const bool            erase_page = true;
    volatile void * const flash_addr = (volatile void *)(dst + NVRAM_BASE_ADDR);
	sysclk_enable_pbb_module(SYSCLK_FLASHC_REGS);
	flashc_memcpy(flash_addr, src, count, erase_page);
	sysclk_disable_pbb_module(SYSCLK_FLASHC_REGS);
	
	
}

/*! \brief Read a buffer from non-volatile RAM
 *
 * This routine reads \c count Bytes from the NVRAM source pointed
 * to by \c src to the destination buffer pointed to by \c dst.
 *
 * \param   src     the read source in the NVRAM address space
 * \param   dst     the destination buffer in program data memory space
 * \param   count   the number of Bytes to read
 *
 * \return  Nothing.
 */
void nvram_read (nvram_addr_t src, void * dst, size_t count)
{
	irqflags_t const flags = cpu_irq_save();
	memcpy(dst, (void *)(src + NVRAM_BASE_ADDR), count);
	cpu_irq_restore(flags);

}
