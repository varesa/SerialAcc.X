#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Microchip/Common/debug_ram_buffer.c Microchip/Common/TimeDelay.c "Microchip/USB/CDC Device Driver/usb_function_cdc.c" "Microchip/USB/Generic Device Driver/usb_function_generic.c" Microchip/USB/usb_device.c main.c usb_descriptors.c usb_io.c i2c_mpu.c msg_buffer.c umpl/accel/mpu6050.c umpl/accel.c umpl/checksum.c umpl/compass.c umpl/compass_debug.c umpl/compass_supervisor.c umpl/compass_supervisor_lite_callbacks.c umpl/dmpDefaultMantis.c umpl/key0_96.c umpl/log_pic24.c umpl/ml.c umpl/mlarray_lite.c umpl/mlBiasNoMotion.c umpl/mlcontrol.c umpl/mldl.c umpl/mldl_cfg.c umpl/mldl_cfg_init_umpl_6050a2.c umpl/mldmp.c umpl/mlFIFO.c umpl/mlFIFOHW.c umpl/mlMathFunc.c umpl/mlos_pic24.c umpl/mlSetGyroBias.c umpl/mlsl_pic24.c umpl/mlstates.c umpl/mlsupervisor.c umpl/ml_init.c umpl/ml_invobj.c umpl/ml_mputest.c umpl/mputest.c umpl/pressure.c umpl/temp_comp_u.c umpl/umpl-setup.c umpl/umpl-states.c umpl/ustore_lite_fusion_delegate.c umpl/ustore_manager.c umpl/ustore_pic24.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o ${OBJECTDIR}/Microchip/Common/TimeDelay.o "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" ${OBJECTDIR}/Microchip/USB/usb_device.o ${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_io.o ${OBJECTDIR}/i2c_mpu.o ${OBJECTDIR}/msg_buffer.o ${OBJECTDIR}/umpl/accel/mpu6050.o ${OBJECTDIR}/umpl/accel.o ${OBJECTDIR}/umpl/checksum.o ${OBJECTDIR}/umpl/compass.o ${OBJECTDIR}/umpl/compass_debug.o ${OBJECTDIR}/umpl/compass_supervisor.o ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o ${OBJECTDIR}/umpl/dmpDefaultMantis.o ${OBJECTDIR}/umpl/key0_96.o ${OBJECTDIR}/umpl/log_pic24.o ${OBJECTDIR}/umpl/ml.o ${OBJECTDIR}/umpl/mlarray_lite.o ${OBJECTDIR}/umpl/mlBiasNoMotion.o ${OBJECTDIR}/umpl/mlcontrol.o ${OBJECTDIR}/umpl/mldl.o ${OBJECTDIR}/umpl/mldl_cfg.o ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o ${OBJECTDIR}/umpl/mldmp.o ${OBJECTDIR}/umpl/mlFIFO.o ${OBJECTDIR}/umpl/mlFIFOHW.o ${OBJECTDIR}/umpl/mlMathFunc.o ${OBJECTDIR}/umpl/mlos_pic24.o ${OBJECTDIR}/umpl/mlSetGyroBias.o ${OBJECTDIR}/umpl/mlsl_pic24.o ${OBJECTDIR}/umpl/mlstates.o ${OBJECTDIR}/umpl/mlsupervisor.o ${OBJECTDIR}/umpl/ml_init.o ${OBJECTDIR}/umpl/ml_invobj.o ${OBJECTDIR}/umpl/ml_mputest.o ${OBJECTDIR}/umpl/mputest.o ${OBJECTDIR}/umpl/pressure.o ${OBJECTDIR}/umpl/temp_comp_u.o ${OBJECTDIR}/umpl/umpl-setup.o ${OBJECTDIR}/umpl/umpl-states.o ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o ${OBJECTDIR}/umpl/ustore_manager.o ${OBJECTDIR}/umpl/ustore_pic24.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" ${OBJECTDIR}/Microchip/USB/usb_device.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/usb_io.o.d ${OBJECTDIR}/i2c_mpu.o.d ${OBJECTDIR}/msg_buffer.o.d ${OBJECTDIR}/umpl/accel/mpu6050.o.d ${OBJECTDIR}/umpl/accel.o.d ${OBJECTDIR}/umpl/checksum.o.d ${OBJECTDIR}/umpl/compass.o.d ${OBJECTDIR}/umpl/compass_debug.o.d ${OBJECTDIR}/umpl/compass_supervisor.o.d ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d ${OBJECTDIR}/umpl/dmpDefaultMantis.o.d ${OBJECTDIR}/umpl/key0_96.o.d ${OBJECTDIR}/umpl/log_pic24.o.d ${OBJECTDIR}/umpl/ml.o.d ${OBJECTDIR}/umpl/mlarray_lite.o.d ${OBJECTDIR}/umpl/mlBiasNoMotion.o.d ${OBJECTDIR}/umpl/mlcontrol.o.d ${OBJECTDIR}/umpl/mldl.o.d ${OBJECTDIR}/umpl/mldl_cfg.o.d ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d ${OBJECTDIR}/umpl/mldmp.o.d ${OBJECTDIR}/umpl/mlFIFO.o.d ${OBJECTDIR}/umpl/mlFIFOHW.o.d ${OBJECTDIR}/umpl/mlMathFunc.o.d ${OBJECTDIR}/umpl/mlos_pic24.o.d ${OBJECTDIR}/umpl/mlSetGyroBias.o.d ${OBJECTDIR}/umpl/mlsl_pic24.o.d ${OBJECTDIR}/umpl/mlstates.o.d ${OBJECTDIR}/umpl/mlsupervisor.o.d ${OBJECTDIR}/umpl/ml_init.o.d ${OBJECTDIR}/umpl/ml_invobj.o.d ${OBJECTDIR}/umpl/ml_mputest.o.d ${OBJECTDIR}/umpl/mputest.o.d ${OBJECTDIR}/umpl/pressure.o.d ${OBJECTDIR}/umpl/temp_comp_u.o.d ${OBJECTDIR}/umpl/umpl-setup.o.d ${OBJECTDIR}/umpl/umpl-states.o.d ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d ${OBJECTDIR}/umpl/ustore_manager.o.d ${OBJECTDIR}/umpl/ustore_pic24.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o ${OBJECTDIR}/Microchip/Common/TimeDelay.o ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o ${OBJECTDIR}/Microchip/USB/usb_device.o ${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_io.o ${OBJECTDIR}/i2c_mpu.o ${OBJECTDIR}/msg_buffer.o ${OBJECTDIR}/umpl/accel/mpu6050.o ${OBJECTDIR}/umpl/accel.o ${OBJECTDIR}/umpl/checksum.o ${OBJECTDIR}/umpl/compass.o ${OBJECTDIR}/umpl/compass_debug.o ${OBJECTDIR}/umpl/compass_supervisor.o ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o ${OBJECTDIR}/umpl/dmpDefaultMantis.o ${OBJECTDIR}/umpl/key0_96.o ${OBJECTDIR}/umpl/log_pic24.o ${OBJECTDIR}/umpl/ml.o ${OBJECTDIR}/umpl/mlarray_lite.o ${OBJECTDIR}/umpl/mlBiasNoMotion.o ${OBJECTDIR}/umpl/mlcontrol.o ${OBJECTDIR}/umpl/mldl.o ${OBJECTDIR}/umpl/mldl_cfg.o ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o ${OBJECTDIR}/umpl/mldmp.o ${OBJECTDIR}/umpl/mlFIFO.o ${OBJECTDIR}/umpl/mlFIFOHW.o ${OBJECTDIR}/umpl/mlMathFunc.o ${OBJECTDIR}/umpl/mlos_pic24.o ${OBJECTDIR}/umpl/mlSetGyroBias.o ${OBJECTDIR}/umpl/mlsl_pic24.o ${OBJECTDIR}/umpl/mlstates.o ${OBJECTDIR}/umpl/mlsupervisor.o ${OBJECTDIR}/umpl/ml_init.o ${OBJECTDIR}/umpl/ml_invobj.o ${OBJECTDIR}/umpl/ml_mputest.o ${OBJECTDIR}/umpl/mputest.o ${OBJECTDIR}/umpl/pressure.o ${OBJECTDIR}/umpl/temp_comp_u.o ${OBJECTDIR}/umpl/umpl-setup.o ${OBJECTDIR}/umpl/umpl-states.o ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o ${OBJECTDIR}/umpl/ustore_manager.o ${OBJECTDIR}/umpl/ustore_pic24.o

# Source Files
SOURCEFILES=Microchip/Common/debug_ram_buffer.c Microchip/Common/TimeDelay.c Microchip/USB/CDC Device Driver/usb_function_cdc.c Microchip/USB/Generic Device Driver/usb_function_generic.c Microchip/USB/usb_device.c main.c usb_descriptors.c usb_io.c i2c_mpu.c msg_buffer.c umpl/accel/mpu6050.c umpl/accel.c umpl/checksum.c umpl/compass.c umpl/compass_debug.c umpl/compass_supervisor.c umpl/compass_supervisor_lite_callbacks.c umpl/dmpDefaultMantis.c umpl/key0_96.c umpl/log_pic24.c umpl/ml.c umpl/mlarray_lite.c umpl/mlBiasNoMotion.c umpl/mlcontrol.c umpl/mldl.c umpl/mldl_cfg.c umpl/mldl_cfg_init_umpl_6050a2.c umpl/mldmp.c umpl/mlFIFO.c umpl/mlFIFOHW.c umpl/mlMathFunc.c umpl/mlos_pic24.c umpl/mlSetGyroBias.c umpl/mlsl_pic24.c umpl/mlstates.c umpl/mlsupervisor.c umpl/ml_init.c umpl/ml_invobj.c umpl/ml_mputest.c umpl/mputest.c umpl/pressure.c umpl/temp_comp_u.c umpl/umpl-setup.c umpl/umpl-states.c umpl/ustore_lite_fusion_delegate.c umpl/ustore_manager.c umpl/ustore_pic24.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o: Microchip/Common/debug_ram_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d" -o ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o Microchip/Common/debug_ram_buffer.c   
	
${OBJECTDIR}/Microchip/Common/TimeDelay.o: Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" -o ${OBJECTDIR}/Microchip/Common/TimeDelay.o Microchip/Common/TimeDelay.c   
	
${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o: Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o: Microchip/USB/Generic\ Device\ Driver/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" -o "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" "Microchip/USB/Generic Device Driver/usb_function_generic.c"   
	
${OBJECTDIR}/Microchip/USB/usb_device.o: Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_device.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_device.o Microchip/USB/usb_device.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c   
	
${OBJECTDIR}/usb_io.o: usb_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_io.o.d 
	@${RM} ${OBJECTDIR}/usb_io.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_io.o.d" -o ${OBJECTDIR}/usb_io.o usb_io.c   
	
${OBJECTDIR}/i2c_mpu.o: i2c_mpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/i2c_mpu.o.d 
	@${RM} ${OBJECTDIR}/i2c_mpu.o 
	@${FIXDEPS} "${OBJECTDIR}/i2c_mpu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/i2c_mpu.o.d" -o ${OBJECTDIR}/i2c_mpu.o i2c_mpu.c   
	
${OBJECTDIR}/msg_buffer.o: msg_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/msg_buffer.o.d 
	@${RM} ${OBJECTDIR}/msg_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/msg_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/msg_buffer.o.d" -o ${OBJECTDIR}/msg_buffer.o msg_buffer.c   
	
${OBJECTDIR}/umpl/accel/mpu6050.o: umpl/accel/mpu6050.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl/accel 
	@${RM} ${OBJECTDIR}/umpl/accel/mpu6050.o.d 
	@${RM} ${OBJECTDIR}/umpl/accel/mpu6050.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/accel/mpu6050.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/accel/mpu6050.o.d" -o ${OBJECTDIR}/umpl/accel/mpu6050.o umpl/accel/mpu6050.c   
	
${OBJECTDIR}/umpl/accel.o: umpl/accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/accel.o.d 
	@${RM} ${OBJECTDIR}/umpl/accel.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/accel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/accel.o.d" -o ${OBJECTDIR}/umpl/accel.o umpl/accel.c   
	
${OBJECTDIR}/umpl/checksum.o: umpl/checksum.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/checksum.o.d 
	@${RM} ${OBJECTDIR}/umpl/checksum.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/checksum.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/checksum.o.d" -o ${OBJECTDIR}/umpl/checksum.o umpl/checksum.c   
	
${OBJECTDIR}/umpl/compass.o: umpl/compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass.o.d" -o ${OBJECTDIR}/umpl/compass.o umpl/compass.c   
	
${OBJECTDIR}/umpl/compass_debug.o: umpl/compass_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass_debug.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass_debug.o.d" -o ${OBJECTDIR}/umpl/compass_debug.o umpl/compass_debug.c   
	
${OBJECTDIR}/umpl/compass_supervisor.o: umpl/compass_supervisor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass_supervisor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass_supervisor.o.d" -o ${OBJECTDIR}/umpl/compass_supervisor.o umpl/compass_supervisor.c   
	
${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o: umpl/compass_supervisor_lite_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d" -o ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o umpl/compass_supervisor_lite_callbacks.c   
	
${OBJECTDIR}/umpl/dmpDefaultMantis.o: umpl/dmpDefaultMantis.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/dmpDefaultMantis.o.d 
	@${RM} ${OBJECTDIR}/umpl/dmpDefaultMantis.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/dmpDefaultMantis.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/dmpDefaultMantis.o.d" -o ${OBJECTDIR}/umpl/dmpDefaultMantis.o umpl/dmpDefaultMantis.c   
	
${OBJECTDIR}/umpl/key0_96.o: umpl/key0_96.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/key0_96.o.d 
	@${RM} ${OBJECTDIR}/umpl/key0_96.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/key0_96.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/key0_96.o.d" -o ${OBJECTDIR}/umpl/key0_96.o umpl/key0_96.c   
	
${OBJECTDIR}/umpl/log_pic24.o: umpl/log_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/log_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/log_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/log_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/log_pic24.o.d" -o ${OBJECTDIR}/umpl/log_pic24.o umpl/log_pic24.c   
	
${OBJECTDIR}/umpl/ml.o: umpl/ml.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml.o.d" -o ${OBJECTDIR}/umpl/ml.o umpl/ml.c   
	
${OBJECTDIR}/umpl/mlarray_lite.o: umpl/mlarray_lite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlarray_lite.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlarray_lite.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlarray_lite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlarray_lite.o.d" -o ${OBJECTDIR}/umpl/mlarray_lite.o umpl/mlarray_lite.c   
	
${OBJECTDIR}/umpl/mlBiasNoMotion.o: umpl/mlBiasNoMotion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlBiasNoMotion.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlBiasNoMotion.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlBiasNoMotion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlBiasNoMotion.o.d" -o ${OBJECTDIR}/umpl/mlBiasNoMotion.o umpl/mlBiasNoMotion.c   
	
${OBJECTDIR}/umpl/mlcontrol.o: umpl/mlcontrol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlcontrol.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlcontrol.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlcontrol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlcontrol.o.d" -o ${OBJECTDIR}/umpl/mlcontrol.o umpl/mlcontrol.c   
	
${OBJECTDIR}/umpl/mldl.o: umpl/mldl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldl.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldl.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldl.o.d" -o ${OBJECTDIR}/umpl/mldl.o umpl/mldl.c   
	
${OBJECTDIR}/umpl/mldl_cfg.o: umpl/mldl_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldl_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldl_cfg.o.d" -o ${OBJECTDIR}/umpl/mldl_cfg.o umpl/mldl_cfg.c   
	
${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o: umpl/mldl_cfg_init_umpl_6050a2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d" -o ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o umpl/mldl_cfg_init_umpl_6050a2.c   
	
${OBJECTDIR}/umpl/mldmp.o: umpl/mldmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldmp.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldmp.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldmp.o.d" -o ${OBJECTDIR}/umpl/mldmp.o umpl/mldmp.c   
	
${OBJECTDIR}/umpl/mlFIFO.o: umpl/mlFIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlFIFO.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlFIFO.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlFIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlFIFO.o.d" -o ${OBJECTDIR}/umpl/mlFIFO.o umpl/mlFIFO.c   
	
${OBJECTDIR}/umpl/mlFIFOHW.o: umpl/mlFIFOHW.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlFIFOHW.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlFIFOHW.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlFIFOHW.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlFIFOHW.o.d" -o ${OBJECTDIR}/umpl/mlFIFOHW.o umpl/mlFIFOHW.c   
	
${OBJECTDIR}/umpl/mlMathFunc.o: umpl/mlMathFunc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlMathFunc.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlMathFunc.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlMathFunc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlMathFunc.o.d" -o ${OBJECTDIR}/umpl/mlMathFunc.o umpl/mlMathFunc.c   
	
${OBJECTDIR}/umpl/mlos_pic24.o: umpl/mlos_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlos_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlos_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlos_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlos_pic24.o.d" -o ${OBJECTDIR}/umpl/mlos_pic24.o umpl/mlos_pic24.c   
	
${OBJECTDIR}/umpl/mlSetGyroBias.o: umpl/mlSetGyroBias.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlSetGyroBias.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlSetGyroBias.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlSetGyroBias.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlSetGyroBias.o.d" -o ${OBJECTDIR}/umpl/mlSetGyroBias.o umpl/mlSetGyroBias.c   
	
${OBJECTDIR}/umpl/mlsl_pic24.o: umpl/mlsl_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlsl_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlsl_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlsl_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlsl_pic24.o.d" -o ${OBJECTDIR}/umpl/mlsl_pic24.o umpl/mlsl_pic24.c   
	
${OBJECTDIR}/umpl/mlstates.o: umpl/mlstates.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlstates.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlstates.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlstates.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlstates.o.d" -o ${OBJECTDIR}/umpl/mlstates.o umpl/mlstates.c   
	
${OBJECTDIR}/umpl/mlsupervisor.o: umpl/mlsupervisor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlsupervisor.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlsupervisor.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlsupervisor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlsupervisor.o.d" -o ${OBJECTDIR}/umpl/mlsupervisor.o umpl/mlsupervisor.c   
	
${OBJECTDIR}/umpl/ml_init.o: umpl/ml_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml_init.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml_init.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml_init.o.d" -o ${OBJECTDIR}/umpl/ml_init.o umpl/ml_init.c   
	
${OBJECTDIR}/umpl/ml_invobj.o: umpl/ml_invobj.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml_invobj.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml_invobj.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml_invobj.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml_invobj.o.d" -o ${OBJECTDIR}/umpl/ml_invobj.o umpl/ml_invobj.c   
	
${OBJECTDIR}/umpl/ml_mputest.o: umpl/ml_mputest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml_mputest.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml_mputest.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml_mputest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml_mputest.o.d" -o ${OBJECTDIR}/umpl/ml_mputest.o umpl/ml_mputest.c   
	
${OBJECTDIR}/umpl/mputest.o: umpl/mputest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mputest.o.d 
	@${RM} ${OBJECTDIR}/umpl/mputest.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mputest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mputest.o.d" -o ${OBJECTDIR}/umpl/mputest.o umpl/mputest.c   
	
${OBJECTDIR}/umpl/pressure.o: umpl/pressure.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/pressure.o.d 
	@${RM} ${OBJECTDIR}/umpl/pressure.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/pressure.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/pressure.o.d" -o ${OBJECTDIR}/umpl/pressure.o umpl/pressure.c   
	
${OBJECTDIR}/umpl/temp_comp_u.o: umpl/temp_comp_u.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/temp_comp_u.o.d 
	@${RM} ${OBJECTDIR}/umpl/temp_comp_u.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/temp_comp_u.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/temp_comp_u.o.d" -o ${OBJECTDIR}/umpl/temp_comp_u.o umpl/temp_comp_u.c   
	
${OBJECTDIR}/umpl/umpl-setup.o: umpl/umpl-setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/umpl-setup.o.d 
	@${RM} ${OBJECTDIR}/umpl/umpl-setup.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/umpl-setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/umpl-setup.o.d" -o ${OBJECTDIR}/umpl/umpl-setup.o umpl/umpl-setup.c   
	
${OBJECTDIR}/umpl/umpl-states.o: umpl/umpl-states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/umpl-states.o.d 
	@${RM} ${OBJECTDIR}/umpl/umpl-states.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/umpl-states.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/umpl-states.o.d" -o ${OBJECTDIR}/umpl/umpl-states.o umpl/umpl-states.c   
	
${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o: umpl/ustore_lite_fusion_delegate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d 
	@${RM} ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d" -o ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o umpl/ustore_lite_fusion_delegate.c   
	
${OBJECTDIR}/umpl/ustore_manager.o: umpl/ustore_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ustore_manager.o.d 
	@${RM} ${OBJECTDIR}/umpl/ustore_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ustore_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ustore_manager.o.d" -o ${OBJECTDIR}/umpl/ustore_manager.o umpl/ustore_manager.c   
	
${OBJECTDIR}/umpl/ustore_pic24.o: umpl/ustore_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ustore_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/ustore_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ustore_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ustore_pic24.o.d" -o ${OBJECTDIR}/umpl/ustore_pic24.o umpl/ustore_pic24.c   
	
else
${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o: Microchip/Common/debug_ram_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d" -o ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o Microchip/Common/debug_ram_buffer.c   
	
${OBJECTDIR}/Microchip/Common/TimeDelay.o: Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/TimeDelay.o.d" -o ${OBJECTDIR}/Microchip/Common/TimeDelay.o Microchip/Common/TimeDelay.c   
	
${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o: Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o: Microchip/USB/Generic\ Device\ Driver/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" -o "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" "Microchip/USB/Generic Device Driver/usb_function_generic.c"   
	
${OBJECTDIR}/Microchip/USB/usb_device.o: Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_device.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_device.o Microchip/USB/usb_device.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c   
	
${OBJECTDIR}/usb_io.o: usb_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_io.o.d 
	@${RM} ${OBJECTDIR}/usb_io.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_io.o.d" -o ${OBJECTDIR}/usb_io.o usb_io.c   
	
${OBJECTDIR}/i2c_mpu.o: i2c_mpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/i2c_mpu.o.d 
	@${RM} ${OBJECTDIR}/i2c_mpu.o 
	@${FIXDEPS} "${OBJECTDIR}/i2c_mpu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/i2c_mpu.o.d" -o ${OBJECTDIR}/i2c_mpu.o i2c_mpu.c   
	
${OBJECTDIR}/msg_buffer.o: msg_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/msg_buffer.o.d 
	@${RM} ${OBJECTDIR}/msg_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/msg_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/msg_buffer.o.d" -o ${OBJECTDIR}/msg_buffer.o msg_buffer.c   
	
${OBJECTDIR}/umpl/accel/mpu6050.o: umpl/accel/mpu6050.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl/accel 
	@${RM} ${OBJECTDIR}/umpl/accel/mpu6050.o.d 
	@${RM} ${OBJECTDIR}/umpl/accel/mpu6050.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/accel/mpu6050.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/accel/mpu6050.o.d" -o ${OBJECTDIR}/umpl/accel/mpu6050.o umpl/accel/mpu6050.c   
	
${OBJECTDIR}/umpl/accel.o: umpl/accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/accel.o.d 
	@${RM} ${OBJECTDIR}/umpl/accel.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/accel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/accel.o.d" -o ${OBJECTDIR}/umpl/accel.o umpl/accel.c   
	
${OBJECTDIR}/umpl/checksum.o: umpl/checksum.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/checksum.o.d 
	@${RM} ${OBJECTDIR}/umpl/checksum.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/checksum.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/checksum.o.d" -o ${OBJECTDIR}/umpl/checksum.o umpl/checksum.c   
	
${OBJECTDIR}/umpl/compass.o: umpl/compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass.o.d" -o ${OBJECTDIR}/umpl/compass.o umpl/compass.c   
	
${OBJECTDIR}/umpl/compass_debug.o: umpl/compass_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass_debug.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass_debug.o.d" -o ${OBJECTDIR}/umpl/compass_debug.o umpl/compass_debug.c   
	
${OBJECTDIR}/umpl/compass_supervisor.o: umpl/compass_supervisor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass_supervisor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass_supervisor.o.d" -o ${OBJECTDIR}/umpl/compass_supervisor.o umpl/compass_supervisor.c   
	
${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o: umpl/compass_supervisor_lite_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d 
	@${RM} ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o.d" -o ${OBJECTDIR}/umpl/compass_supervisor_lite_callbacks.o umpl/compass_supervisor_lite_callbacks.c   
	
${OBJECTDIR}/umpl/dmpDefaultMantis.o: umpl/dmpDefaultMantis.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/dmpDefaultMantis.o.d 
	@${RM} ${OBJECTDIR}/umpl/dmpDefaultMantis.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/dmpDefaultMantis.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/dmpDefaultMantis.o.d" -o ${OBJECTDIR}/umpl/dmpDefaultMantis.o umpl/dmpDefaultMantis.c   
	
${OBJECTDIR}/umpl/key0_96.o: umpl/key0_96.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/key0_96.o.d 
	@${RM} ${OBJECTDIR}/umpl/key0_96.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/key0_96.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/key0_96.o.d" -o ${OBJECTDIR}/umpl/key0_96.o umpl/key0_96.c   
	
${OBJECTDIR}/umpl/log_pic24.o: umpl/log_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/log_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/log_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/log_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/log_pic24.o.d" -o ${OBJECTDIR}/umpl/log_pic24.o umpl/log_pic24.c   
	
${OBJECTDIR}/umpl/ml.o: umpl/ml.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml.o.d" -o ${OBJECTDIR}/umpl/ml.o umpl/ml.c   
	
${OBJECTDIR}/umpl/mlarray_lite.o: umpl/mlarray_lite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlarray_lite.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlarray_lite.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlarray_lite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlarray_lite.o.d" -o ${OBJECTDIR}/umpl/mlarray_lite.o umpl/mlarray_lite.c   
	
${OBJECTDIR}/umpl/mlBiasNoMotion.o: umpl/mlBiasNoMotion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlBiasNoMotion.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlBiasNoMotion.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlBiasNoMotion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlBiasNoMotion.o.d" -o ${OBJECTDIR}/umpl/mlBiasNoMotion.o umpl/mlBiasNoMotion.c   
	
${OBJECTDIR}/umpl/mlcontrol.o: umpl/mlcontrol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlcontrol.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlcontrol.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlcontrol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlcontrol.o.d" -o ${OBJECTDIR}/umpl/mlcontrol.o umpl/mlcontrol.c   
	
${OBJECTDIR}/umpl/mldl.o: umpl/mldl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldl.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldl.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldl.o.d" -o ${OBJECTDIR}/umpl/mldl.o umpl/mldl.c   
	
${OBJECTDIR}/umpl/mldl_cfg.o: umpl/mldl_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldl_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldl_cfg.o.d" -o ${OBJECTDIR}/umpl/mldl_cfg.o umpl/mldl_cfg.c   
	
${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o: umpl/mldl_cfg_init_umpl_6050a2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o.d" -o ${OBJECTDIR}/umpl/mldl_cfg_init_umpl_6050a2.o umpl/mldl_cfg_init_umpl_6050a2.c   
	
${OBJECTDIR}/umpl/mldmp.o: umpl/mldmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mldmp.o.d 
	@${RM} ${OBJECTDIR}/umpl/mldmp.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mldmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mldmp.o.d" -o ${OBJECTDIR}/umpl/mldmp.o umpl/mldmp.c   
	
${OBJECTDIR}/umpl/mlFIFO.o: umpl/mlFIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlFIFO.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlFIFO.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlFIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlFIFO.o.d" -o ${OBJECTDIR}/umpl/mlFIFO.o umpl/mlFIFO.c   
	
${OBJECTDIR}/umpl/mlFIFOHW.o: umpl/mlFIFOHW.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlFIFOHW.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlFIFOHW.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlFIFOHW.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlFIFOHW.o.d" -o ${OBJECTDIR}/umpl/mlFIFOHW.o umpl/mlFIFOHW.c   
	
${OBJECTDIR}/umpl/mlMathFunc.o: umpl/mlMathFunc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlMathFunc.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlMathFunc.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlMathFunc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlMathFunc.o.d" -o ${OBJECTDIR}/umpl/mlMathFunc.o umpl/mlMathFunc.c   
	
${OBJECTDIR}/umpl/mlos_pic24.o: umpl/mlos_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlos_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlos_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlos_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlos_pic24.o.d" -o ${OBJECTDIR}/umpl/mlos_pic24.o umpl/mlos_pic24.c   
	
${OBJECTDIR}/umpl/mlSetGyroBias.o: umpl/mlSetGyroBias.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlSetGyroBias.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlSetGyroBias.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlSetGyroBias.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlSetGyroBias.o.d" -o ${OBJECTDIR}/umpl/mlSetGyroBias.o umpl/mlSetGyroBias.c   
	
${OBJECTDIR}/umpl/mlsl_pic24.o: umpl/mlsl_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlsl_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlsl_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlsl_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlsl_pic24.o.d" -o ${OBJECTDIR}/umpl/mlsl_pic24.o umpl/mlsl_pic24.c   
	
${OBJECTDIR}/umpl/mlstates.o: umpl/mlstates.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlstates.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlstates.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlstates.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlstates.o.d" -o ${OBJECTDIR}/umpl/mlstates.o umpl/mlstates.c   
	
${OBJECTDIR}/umpl/mlsupervisor.o: umpl/mlsupervisor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mlsupervisor.o.d 
	@${RM} ${OBJECTDIR}/umpl/mlsupervisor.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mlsupervisor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mlsupervisor.o.d" -o ${OBJECTDIR}/umpl/mlsupervisor.o umpl/mlsupervisor.c   
	
${OBJECTDIR}/umpl/ml_init.o: umpl/ml_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml_init.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml_init.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml_init.o.d" -o ${OBJECTDIR}/umpl/ml_init.o umpl/ml_init.c   
	
${OBJECTDIR}/umpl/ml_invobj.o: umpl/ml_invobj.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml_invobj.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml_invobj.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml_invobj.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml_invobj.o.d" -o ${OBJECTDIR}/umpl/ml_invobj.o umpl/ml_invobj.c   
	
${OBJECTDIR}/umpl/ml_mputest.o: umpl/ml_mputest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ml_mputest.o.d 
	@${RM} ${OBJECTDIR}/umpl/ml_mputest.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ml_mputest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ml_mputest.o.d" -o ${OBJECTDIR}/umpl/ml_mputest.o umpl/ml_mputest.c   
	
${OBJECTDIR}/umpl/mputest.o: umpl/mputest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/mputest.o.d 
	@${RM} ${OBJECTDIR}/umpl/mputest.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/mputest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/mputest.o.d" -o ${OBJECTDIR}/umpl/mputest.o umpl/mputest.c   
	
${OBJECTDIR}/umpl/pressure.o: umpl/pressure.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/pressure.o.d 
	@${RM} ${OBJECTDIR}/umpl/pressure.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/pressure.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/pressure.o.d" -o ${OBJECTDIR}/umpl/pressure.o umpl/pressure.c   
	
${OBJECTDIR}/umpl/temp_comp_u.o: umpl/temp_comp_u.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/temp_comp_u.o.d 
	@${RM} ${OBJECTDIR}/umpl/temp_comp_u.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/temp_comp_u.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/temp_comp_u.o.d" -o ${OBJECTDIR}/umpl/temp_comp_u.o umpl/temp_comp_u.c   
	
${OBJECTDIR}/umpl/umpl-setup.o: umpl/umpl-setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/umpl-setup.o.d 
	@${RM} ${OBJECTDIR}/umpl/umpl-setup.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/umpl-setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/umpl-setup.o.d" -o ${OBJECTDIR}/umpl/umpl-setup.o umpl/umpl-setup.c   
	
${OBJECTDIR}/umpl/umpl-states.o: umpl/umpl-states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/umpl-states.o.d 
	@${RM} ${OBJECTDIR}/umpl/umpl-states.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/umpl-states.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/umpl-states.o.d" -o ${OBJECTDIR}/umpl/umpl-states.o umpl/umpl-states.c   
	
${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o: umpl/ustore_lite_fusion_delegate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d 
	@${RM} ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o.d" -o ${OBJECTDIR}/umpl/ustore_lite_fusion_delegate.o umpl/ustore_lite_fusion_delegate.c   
	
${OBJECTDIR}/umpl/ustore_manager.o: umpl/ustore_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ustore_manager.o.d 
	@${RM} ${OBJECTDIR}/umpl/ustore_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ustore_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ustore_manager.o.d" -o ${OBJECTDIR}/umpl/ustore_manager.o umpl/ustore_manager.c   
	
${OBJECTDIR}/umpl/ustore_pic24.o: umpl/ustore_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/umpl 
	@${RM} ${OBJECTDIR}/umpl/ustore_pic24.o.d 
	@${RM} ${OBJECTDIR}/umpl/ustore_pic24.o 
	@${FIXDEPS} "${OBJECTDIR}/umpl/ustore_pic24.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/umpl/ustore_pic24.o.d" -o ${OBJECTDIR}/umpl/ustore_pic24.o umpl/ustore_pic24.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SerialAcc.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
