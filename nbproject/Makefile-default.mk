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
SOURCEFILES_QUOTED_IF_SPACED=Microchip/Common/debug_ram_buffer.c Microchip/Common/TimeDelay.c "Microchip/USB/CDC Device Driver/usb_function_cdc.c" "Microchip/USB/Generic Device Driver/usb_function_generic.c" Microchip/USB/usb_device.c eMPL/inv_mpu.c eMPL/inv_mpu_dmp_motion_driver.c main.c usb_descriptors.c usb_io.c i2c_mpu.c msg_buffer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o ${OBJECTDIR}/Microchip/Common/TimeDelay.o "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" ${OBJECTDIR}/Microchip/USB/usb_device.o ${OBJECTDIR}/eMPL/inv_mpu.o ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o ${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_io.o ${OBJECTDIR}/i2c_mpu.o ${OBJECTDIR}/msg_buffer.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" ${OBJECTDIR}/Microchip/USB/usb_device.o.d ${OBJECTDIR}/eMPL/inv_mpu.o.d ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/usb_io.o.d ${OBJECTDIR}/i2c_mpu.o.d ${OBJECTDIR}/msg_buffer.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o ${OBJECTDIR}/Microchip/Common/TimeDelay.o ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o ${OBJECTDIR}/Microchip/USB/usb_device.o ${OBJECTDIR}/eMPL/inv_mpu.o ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o ${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_io.o ${OBJECTDIR}/i2c_mpu.o ${OBJECTDIR}/msg_buffer.o

# Source Files
SOURCEFILES=Microchip/Common/debug_ram_buffer.c Microchip/Common/TimeDelay.c Microchip/USB/CDC Device Driver/usb_function_cdc.c Microchip/USB/Generic Device Driver/usb_function_generic.c Microchip/USB/usb_device.c eMPL/inv_mpu.c eMPL/inv_mpu_dmp_motion_driver.c main.c usb_descriptors.c usb_io.c i2c_mpu.c msg_buffer.c


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
	
${OBJECTDIR}/eMPL/inv_mpu.o: eMPL/inv_mpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/eMPL 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu.o.d 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu.o 
	@${FIXDEPS} "${OBJECTDIR}/eMPL/inv_mpu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/eMPL/inv_mpu.o.d" -o ${OBJECTDIR}/eMPL/inv_mpu.o eMPL/inv_mpu.c   
	
${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o: eMPL/inv_mpu_dmp_motion_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/eMPL 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d" -o ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o eMPL/inv_mpu_dmp_motion_driver.c   
	
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
	
${OBJECTDIR}/eMPL/inv_mpu.o: eMPL/inv_mpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/eMPL 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu.o.d 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu.o 
	@${FIXDEPS} "${OBJECTDIR}/eMPL/inv_mpu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/eMPL/inv_mpu.o.d" -o ${OBJECTDIR}/eMPL/inv_mpu.o eMPL/inv_mpu.c   
	
${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o: eMPL/inv_mpu_dmp_motion_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/eMPL 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d 
	@${RM} ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o.d" -o ${OBJECTDIR}/eMPL/inv_mpu_dmp_motion_driver.o eMPL/inv_mpu_dmp_motion_driver.c   
	
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
