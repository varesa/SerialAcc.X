//  Function prototypes

const unsigned char __attribute__ ((address(0x02A000), space(psv))) calibrationData[512];

int nvmem_write(int, int*, int);
int nvmem_read(int, unsigned char*, int);

