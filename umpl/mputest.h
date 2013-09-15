/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

/******************************************************************************
 *
 * $Id: mputest.h 4051 2010-11-19 04:51:58Z mcaramello $
 *
 *****************************************************************************/

#ifndef MPUTEST_H
#define MPUTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mlsl.h"
#include "mldl_cfg.h"

void inv_set_test_parameters(unsigned int slave_addr, float sensitivity,
                             int p_thresh, float total_time_tol,
                             int bias_thresh, unsigned short accel_samples);
int inv_device_test(void *mlsl_handle, uint_fast8_t sensor_mask,
                uint_fast8_t perform_full_test, uint_fast8_t provide_result);
int inv_accel_z_test(void *mlsl_handle);

#ifdef __cplusplus
}
#endif

#endif /* MPUTEST_H */

