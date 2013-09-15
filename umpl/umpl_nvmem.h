/*
 * umpl_nvram.h
 *
 * Created: 5/2/2011 2:27:56 PM
 *  Author: sgurumani
 */ 


#ifndef UMPL_NVMEM_H_
#define UMPL_NVMEM_H_


#ifdef __cplusplus
extern "C" {
#endif

//#include <asf.h>
//#include <compiler.h>
#include "mltypes.h"

//! \name Data type for NVRAM memory addresses.

typedef uint16_t nvram_addr_t;

//! \name Atmel platform non-volatile memory spaces.


//#   include <flashc.h>
//#   define NVRAM_BASE_ADDR      (0x10 + AVR32_FLASHC_USER_PAGE_ADDRESS)
//#   define NVRAM_SIZE           (AVR32_FLASHC_USER_PAGE_SIZE)

//void nvram_read (nvram_addr_t src, void * dst, size_t count);
//void nvram_write (nvram_addr_t dst, const void * src, size_t count, bool erase);

#ifdef __cplusplus
}
#endif



#endif /* UMPL_NVMEM_H_ */

