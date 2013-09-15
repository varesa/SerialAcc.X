//#include <asf.h>   specific to Atmel
#include <stdio.h>
#include <string.h>
#include "umpl-tests.h"
#include "mlsl.h"
#include "mpu.h"

int g_accel_slaveaddr = 0x0f;
int g_accel_burstaddr = 0x06;
#define MPUREG_PRODUCT_ID 0x81
#define REG_BURST_START MPUREG_PRODUCT_ID
#define FILL_FIFO_SIZE      (512)
#define FIFO_RW_CHUNK_SIZE  (128)
#define FILL_RAM_SIZE (128)
#define REG_BURST_LEN 20
typedef void (*data_setup_func) (unsigned char*, int);

void setup_random(unsigned char* data, int len)
{
    int i;
    for(i = 0; i < len; i++) {
        data[i] = 1 + rand() & (0xFF - 2);
    }
}

void setup_zero(unsigned char* data, int len)
{
    memset(data, 0x00, len);
}
void setup_counter(unsigned char* data, int len)
{
    int i;
    for(i = 0; i < len; i++) {
        data[i] = i & 0xFF;
    }
}

void setup_ff(unsigned char* data, int len)
{
    memset(data, 0xff, len);
}

void setup_aa(unsigned char* data, int len)
{
    memset(data, 0xaa, len);
}

void setup_aa_55(unsigned char* data, int len)
{
    int ii;
    for (ii = 0; ii + 1 < len; ii += 2) {
        data[ii] = 0xaa;
        data[ii+1] = 0x55;
    }
}
void error_pattern(unsigned char* data, int len)
{
    memset(data, 0xBE, len);
}


int test_single_wr(void)
{
    unsigned short res;
    unsigned char write_val = rand() % 256;
    unsigned char read_val;

    printf("\rTEST SINGLE BYTE READ AND WRITE\n");

    // Set slave address and burst addr
    res = MLSLSerialWriteSingle( 0, 0x68,
                                0x14, write_val);
    if (res != 0){
        printf( "\rtest_single_wr failed - could not MLSLSerialWriteSingle\n");
    }
    res = MLSLSerialRead(0, 0x68,
                         0x14, 1, &read_val);
    if (res != 0){
        printf( "\r serial write failed.\n"
                "\rAUX_SLV_ADDR reg is 0x%02X (exp:0x%02X)\n", read_val, write_val );
    }
    // restore reg value
    res = MLSLSerialWriteSingle(0, 0x68,
                                0x14, g_accel_slaveaddr);
   if (res != 0){
        printf( "\r restore reg value failed.\n");
    }
    return res;
}
int test_burst_wr(void)
{
    unsigned char i2c_write[1 + REG_BURST_LEN];
    unsigned char *write_data = &i2c_write[1];
    unsigned char read_data[REG_BURST_LEN];
    unsigned short thisLen;
    unsigned short res, fail;
    int i;

    printf("\rMulti byte write and read\n");

    i2c_write[0] = REG_BURST_START;
    setup_random(write_data, REG_BURST_LEN);
    //write_data[0] = DEFAULT_MPU_SLAVEADDR;

    thisLen = 1;
    while (thisLen < REG_BURST_LEN) {
        setup_ff(read_data, REG_BURST_LEN);  // clear read data from prev cycle


        res = MLSLSerialWrite(0, 0x68,
                              1 + thisLen, i2c_write);
        if (res != 0){
                printf( "\r burst write failed.\n");
        }
        res = MLSLSerialRead(0, 0x68,
                             REG_BURST_START,
                             thisLen, read_data);
        if (res != 0){
                printf( "\r burst read failed.\n");
        }
        // error checking
        for(i = 0, fail = 0; i < thisLen; i++) {
            if(write_data[i] != read_data[i]) {
                fail++;
            }
        }
        // error handling
        if (fail) {
            printf("\r serial burst write and read failed at %d B",
                         thisLen );
        }

        thisLen += 1;
    }
    // reset MPU
    res = MLSLSerialWriteSingle(0, 0x68,
                          MPUREG_PWR_MGM, 0x80);
                          if (res != 0){
                printf("\rtest_burst_wr - restting MPU faield.\n");
        }

    return res;
}

int test_single_write(void)
{
    unsigned char data = BIT_DMP_EN|BIT_FIFO_EN;
    unsigned char usr_ctrl_before = 0x00;
    unsigned char usr_ctrl_after = 0x00;
    //unsigned char data = 0xDF;    // reset all also
    unsigned short res = INV_SUCCESS;

    printf("\rSINGLE BYTE WRITE\n");

    // Set slave address and burst addr
    res = MLSLSerialWriteSingle(0, 0x68,
                                MPUREG_AUX_SLV_ADDR, g_accel_slaveaddr);

    res = MLSLSerialWriteSingle(0, 0x68,
                                MPUREG_ACCEL_BURST_ADDR, g_accel_burstaddr);
       if (res != 0){
                printf( "\r Setting slave and burst address failed \n");
            }
    delay_ms(1);

    // Enable the DMP, FIFO and auxiliary slave (master mode)
    res = MLSLSerialRead(0, 0x68,
                         MPUREG_USER_CTRL, 1, &usr_ctrl_before);

    res = MLSLSerialWriteSingle(0, 0x68,
                                MPUREG_USER_CTRL, data);

    res = MLSLSerialRead(0, 0x68,
                         MPUREG_USER_CTRL, 1, &usr_ctrl_after);
        if (res != 0){
                printf( "\r Enable the DMP, FIFO and auxiliary slave (master mode) failed \n");
            }

    res = MLSLSerialWriteSingle(0, 0x68,
                                MPUREG_USER_CTRL, usr_ctrl_before);

    delay_ms(1);
    res = MLSLSerialRead(0, 0x68,
                         MPUREG_USER_CTRL, 1, &data);

return res;

}

int test_register_dump(void)
{
    unsigned char data;
    unsigned short res = 0;
    unsigned char ff_cnt = 0;
    unsigned int error = false;
    unsigned char usrCfgRegs[NUM_OF_MPU_REGISTERS];
    int ii;

    printf("\rRegister dump\n");

    for(ii = 0; ii < NUM_OF_MPU_REGISTERS; ii++) {
        if (ii == MPUREG_FIFO_R_W || ii == MPUREG_MEM_R_W) {
            data = 0x00;
        }
        else {
            res = MLSLSerialRead(0, 0x68, ii, 1, &data);
             if (res != 0){
                printf( "\rregister dump failed.\n");
            }
        }
        ff_cnt += (data == 0xff);
        usrCfgRegs[ii] = data;
    }
    if (ff_cnt > NUM_OF_MPU_REGISTERS/4) {
        error = true;
    }
    return res;

}


int test_fill_ram_in_chunks(void)
{
    unsigned char write_data[MPU_MEM_BANK_SIZE], read_data[MPU_MEM_BANK_SIZE];
    unsigned short res;
    //const unsigned char bank = MPU_MEM_RAM_BANK_1;
	unsigned char bank = 1;			//  Added by Stephen Allen 8/16/11
    unsigned short chunk_size = MPU_MEM_BANK_SIZE * 2; // will be divided by 2
    int fail = true;
    int i;

    printf("\rLoad RAM bank\n");

    setup_counter(write_data, MPU_MEM_BANK_SIZE);

    // try and load memory halving the chunk size at each try
    while(fail) {
        unsigned rem = MPU_MEM_BANK_SIZE;

        chunk_size /= 2;
        while(rem) {
            const unsigned char memStart = MPU_MEM_BANK_SIZE-rem;
            //write to memory area
            res = MLSLSerialWriteMem(0, 0x68,
                                     bank << 8 | memStart,
                                     chunk_size, &write_data[memStart]);
           if (res != 0){
                printf( "\rwrite to memory area failed.\n");
            }

            //read back
            res = MLSLSerialReadMem(0, 0x68,
                                    bank << 8 | memStart,
                                    chunk_size, &read_data[memStart]);
           if (res != 0){
                printf( "\rread from memory area failed.\n");
            }
            rem -= chunk_size;
        }
        fail = false;
        for (i = 0; i < MPU_MEM_BANK_SIZE; i++) {
            if (write_data[i] != read_data[i]) {
                fail = true;
            }
        }
    }

    return res;
}


int test_fill_ram(void)
{
    unsigned char write_data[MPU_MEM_BANK_SIZE], read_data[MPU_MEM_BANK_SIZE];
    unsigned short res;
    //const unsigned char bank = MPU_MEM_RAM_BANK_1;
	unsigned char bank = 1;			//  Added by Stephen Allen 8/16/11
    int fail = false;
    data_setup_func fill_data[] = {
        setup_zero,
        setup_ff,
        setup_aa,
        setup_aa_55,
        setup_counter
    };
    const int num_data_sets = sizeof(fill_data) / sizeof(data_setup_func);
    int i, j;

    printf("\rFill RAM area\n");

    for(i = 0; i < num_data_sets; i++) {
        fill_data[i](write_data, FILL_RAM_SIZE);
        error_pattern(read_data, FILL_RAM_SIZE);

        //write to memory area
        res = MLSLSerialWriteMem(0, 0x68,
                                 bank << 8 | 0x00, FILL_RAM_SIZE, write_data);
         if (res != 0){
                printf( "\rwrite to memory area failed.\n");
            }

        //read back
        res = MLSLSerialReadMem(0, 0x68,
                                bank << 8 | 0x00, FILL_RAM_SIZE, read_data);
        if (res != 0){
                printf( "\rread back failed.\n");
            }
        //check
        for(j = 0; j < FILL_RAM_SIZE; j++){
            if(write_data[j] != read_data[j]) {
                    printf("\rRAM area fill mismatch : %02X -> %02X != %02X\n",
                            j, (int)write_data[j], (int)read_data[j]);
                fail++;
            }
        }
        if(fail > 0){
            printf("\rRAM area fill failed - "
                     "memory write and read mismatch in %d location\n", fail);
        }

    }

return res;
}



int test_fill_fifo(void)
{
    unsigned char write_data[FILL_FIFO_SIZE], read_data[FILL_FIFO_SIZE];
    unsigned char usr_ctrl;
    unsigned short res;
    //int fail = 0;
    int len = 0xff;
    int tries = 0;
    int mismatches = 0;
    int j;

    printf("\rTEST Fill FIFO\n");

    j = 0;
    setup_counter(write_data, FILL_FIFO_SIZE);
    setup_zero(read_data, FILL_FIFO_SIZE);

    res = MLSLSerialRead(0, 0x68,
                         0x3d, 1, &usr_ctrl);
    if (res != 0){
        printf( "\rtest_fill_fifo failed - could not MLSLSerialRead usr cntrl.\n");
    }

    // fifo reset
    while (len > 0  && tries++ < 6)
    {
        res = MLSLSerialWriteSingle(0, 0x68,
                                    0x3d,
                                    usr_ctrl & (~BIT_FIFO_EN) | BIT_FIFO_RST);
        if (res != 0){
        printf( "\rtest_fill_fifo failed - could not fifo reset.\n");
        }
        delay_ms(50);
        res = MLSLSerialRead(0, 0x68,
                             0x3a, 2, read_data);
         if (res != 0){
        printf( "\rtest_fill_fifo failed - could not read fifo count.\n");
        }
        len = read_data[0] << 8 | read_data[1];

    }
    if (len != 0){
         printf("\rReset Failed. FIFO COunt is %d\n", len);
    }

    //set up write to FIFO
    res = MLSLSerialWriteSingle(0, 0x68,
                                0x3d,
                                usr_ctrl | (BIT_FIFO_EN | BIT_FIFO_RST));
      if (res != 0){
        printf( "\rtest_fill_fifo failed - could not set up write to FIFO.\n");
        }
    delay_ms(5);

    // write the fifo, FIFO_RW_CHUNK_SIZE bytes at a time
    len = 0;
    while (len < FILL_FIFO_SIZE) {
        res = MLSLSerialWriteFifo(0, 0x68,
                                  FIFO_RW_CHUNK_SIZE, &write_data[len]);
        if (res != 0){
        printf( "\rtest_fill_fifo failed - could not write the fifo, FIFO_RW_CHUNK_SIZE bytes at a time.\n");
        }
        len += FIFO_RW_CHUNK_SIZE;
    }

    // read the fifo content, FIFO_RW_CHUNK_SIZE bytes at a time
    len = 0;
    while (len < FILL_FIFO_SIZE) {
        res = MLSLSerialReadFifo(0, 0x68,
                                 FIFO_RW_CHUNK_SIZE, &read_data[len]);
        if (res != 0){
        printf( "\rtest_fill_fifo failed - could not read the fifo, FIFO_RW_CHUNK_SIZE bytes at a time.\n");
        }
        len += FIFO_RW_CHUNK_SIZE;
    }

     //disable the fifo
    res = MLSLSerialWriteSingle(0, 0x68,
                                0x3d, usr_ctrl & ~BIT_FIFO_EN);
    if (res != 0){
        printf( "\r could not disable the fifo.\n");
        }

    // compare
    for(j = 0; j < FILL_FIFO_SIZE; j++) {
        mismatches += (write_data[j] != read_data[j]);
    }
    if (mismatches) {
        printf("\rThere were %d mismatches \n", mismatches);
    }
    //if (mismatches) {
        //if (g_verbose) {
            //ADD_MESSAGE("\nwritten data:\n");
            //print_data(write_data, FILL_FIFO_SIZE);
            //ADD_MESSAGE("\nread data:\n");
            //print_data(read_data, FILL_FIFO_SIZE);
//
            //ADD_MESSAGE("\nMismatching bytes (%d):\n", mismatches);
            //ADD_MESSAGE("\tloc. -> Wrote Read Bytes\n");
            //for(j = 0; j < FILL_FIFO_SIZE; j++) {
                //if (write_data[j] != read_data[j]) {
                    //ADD_MESSAGE("\t%4d    0x%02X  0x%02X",
                                //j, write_data[j], read_data[j]);
                //}
            //}
            //ADD_MESSAGE("\n");
        //}
        //RECORD_ERROR(mismatches, "FIFO fill failed on %d B out of %d",
                                 //mismatches, FILL_FIFO_SIZE);
    //}
//
    return res;
}
int test_open(void)
{
    int result = 0;
    printf("\rTEST OPEN\n");
    // reset and wake up the chip.
    //  It may fail if the driver is not actually working
    result = MLSLSerialWriteSingle(0, 0x68,
                                0x3e, 0xC0);
    if (result != 0){
        printf( "\rserial open failed - could not reset the part\n");
    }

    delay_ms (50);
    result = MLSLSerialWriteSingle(0, 0x68,
                                0x3e, 0x00);
    if (result != 0){
        printf( "\rserial open failed - could not wake up the part\n");
    }

   delay_ms (50);
   return result;
}

int whoamitest(void)
{
    unsigned char data;
    unsigned char regaddr;
    int result = 0;
#ifdef M_HW
    regaddr = 117;
    #else
    regaddr = 0;
#endif
    result = MLSLSerialRead( 0, 0x68, regaddr,1, &data );
    if (result != 0) {
        MPL_LOGE("whoamitest serialreadsingle returned %d\n",result);
        return INV_ERROR_SERIAL_READ;
    }
    if (data != 0x68){
        MPL_LOGE("whoamitest expexted 0x68 got %x\n",data);
        return INV_ERROR;
    }
    return INV_SUCCESS;
}

int selfTest(void)
{
    int result = 0;
    result = test_open();
    //1
    if(result == 0){
                        printf("\rtest_open Success\n");
                    }else{
                        printf("\rtest_open Fail \n");
                    }
   //2
   result = test_single_wr();
    if(result == 0){
                        printf("\rtest_single_wr Success\n");
                    }else{
                        printf("\r test_single_wr Fail \n");
                    }
    //3
    result = test_burst_wr();
    if(result == 0){
                        printf("\rtest_burst_wr Success\n");
                    }else{
                        printf("\r test_burst_wr Fail \n");
                    }
    //4
    result = test_single_write();
    if(result == 0){
                        printf("\test_single_write Success\n");
                    }else{
                        printf("\r test_single_write Fail \n");
                    }
    result = test_register_dump();
    if(result == 0){
                        printf("\r test_register_dump Success\n");
                    }else{
                        printf("\r test_register_dump Fail \n");
                    }
    result = test_fill_ram();
    if(result == 0){
                        printf("\r test_fill_ram Success\n");
                    }else{
                        printf("\r test_fill_ram Fail \n");
                    }
    result = test_fill_ram_in_chunks();
    if(result == 0){
                        printf("\r test_fill_ram_in_chunks Success\n");
                    }else{
                        printf("\r test_fill_ram_in_chunks Fail \n");
                    }

    result = test_fill_fifo();
    if(result == 0){
                        printf("\rtest_fill_fifo Success\n");
                    }else{
                        printf("\r test_fill_fifo Fail \n");
                    }
    return result;

}
