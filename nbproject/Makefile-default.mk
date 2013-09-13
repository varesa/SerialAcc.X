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
SOURCEFILES_QUOTED_IF_SPACED=main.c usb_descriptors.c Microchip/Common/debug_ram_buffer.c Microchip/Common/TimeDelay.c Microchip/Common/timer.c Microchip/Common/uart2.c "Microchip/USB/Audio Device Driver/usb_function_audio.c" "Microchip/USB/CDC Device Driver/usb_function_cdc.c" "Microchip/USB/CDC Host Driver/usb_host_cdc.c" "Microchip/USB/CDC Host Driver/usb_host_cdc_interface.c" "Microchip/USB/Charger Host Driver/usb_host_charger.c" "Microchip/USB/Generic Device Driver/usb_function_generic.c" "Microchip/USB/Generic Host Driver/usb_host_generic.c" "Microchip/USB/HID Device Driver/usb_function_hid.c" "Microchip/USB/HID Host Driver/usb_host_hid.c" "Microchip/USB/HID Host Driver/usb_host_hid_parser.c" "Microchip/USB/MSD Device Driver/usb_function_msd.c" "Microchip/USB/MSD Host Driver/usb_host_msd.c" "Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c" "Microchip/USB/Printer Host Driver/usb_host_printer.c" "Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.c" "Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.c" "Microchip/USB/Printer Host Driver/usb_host_printer_postscript.c" "Microchip/USB/Printer Host Driver/usb_host_printer_primitives.c" Microchip/USB/usb_device.c Microchip/USB/usb_host.c Microchip/USB/usb_otg.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o ${OBJECTDIR}/Microchip/Common/TimeDelay.o ${OBJECTDIR}/Microchip/Common/timer.o ${OBJECTDIR}/Microchip/Common/uart2.o "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o" "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o" "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o" "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o" "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o" "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o" "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o" "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o" "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o" "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o" "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o" ${OBJECTDIR}/Microchip/USB/usb_device.o ${OBJECTDIR}/Microchip/USB/usb_host.o ${OBJECTDIR}/Microchip/USB/usb_otg.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o.d ${OBJECTDIR}/Microchip/Common/TimeDelay.o.d ${OBJECTDIR}/Microchip/Common/timer.o.d ${OBJECTDIR}/Microchip/Common/uart2.o.d "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o.d" "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o.d" "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o.d" "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o.d" "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o.d" "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o.d" "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o.d" "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o.d" "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o.d" "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o.d" "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o.d" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o.d" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o.d" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o.d" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o.d" "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o.d" ${OBJECTDIR}/Microchip/USB/usb_device.o.d ${OBJECTDIR}/Microchip/USB/usb_host.o.d ${OBJECTDIR}/Microchip/USB/usb_otg.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/Microchip/Common/debug_ram_buffer.o ${OBJECTDIR}/Microchip/Common/TimeDelay.o ${OBJECTDIR}/Microchip/Common/timer.o ${OBJECTDIR}/Microchip/Common/uart2.o ${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver/usb_function_audio.o ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.o ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.o ${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver/usb_host_charger.o ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o ${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver/usb_host_generic.o ${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver/usb_function_hid.o ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid.o ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.o ${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver/usb_function_msd.o ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd.o ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.o ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer.o ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.o ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.o ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.o ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.o ${OBJECTDIR}/Microchip/USB/usb_device.o ${OBJECTDIR}/Microchip/USB/usb_host.o ${OBJECTDIR}/Microchip/USB/usb_otg.o

# Source Files
SOURCEFILES=main.c usb_descriptors.c Microchip/Common/debug_ram_buffer.c Microchip/Common/TimeDelay.c Microchip/Common/timer.c Microchip/Common/uart2.c Microchip/USB/Audio Device Driver/usb_function_audio.c Microchip/USB/CDC Device Driver/usb_function_cdc.c Microchip/USB/CDC Host Driver/usb_host_cdc.c Microchip/USB/CDC Host Driver/usb_host_cdc_interface.c Microchip/USB/Charger Host Driver/usb_host_charger.c Microchip/USB/Generic Device Driver/usb_function_generic.c Microchip/USB/Generic Host Driver/usb_host_generic.c Microchip/USB/HID Device Driver/usb_function_hid.c Microchip/USB/HID Host Driver/usb_host_hid.c Microchip/USB/HID Host Driver/usb_host_hid_parser.c Microchip/USB/MSD Device Driver/usb_function_msd.c Microchip/USB/MSD Host Driver/usb_host_msd.c Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c Microchip/USB/Printer Host Driver/usb_host_printer.c Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.c Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.c Microchip/USB/Printer Host Driver/usb_host_printer_postscript.c Microchip/USB/Printer Host Driver/usb_host_printer_primitives.c Microchip/USB/usb_device.c Microchip/USB/usb_host.c Microchip/USB/usb_otg.c


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
	
${OBJECTDIR}/Microchip/Common/timer.o: Microchip/Common/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/timer.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/timer.o.d" -o ${OBJECTDIR}/Microchip/Common/timer.o Microchip/Common/timer.c   
	
${OBJECTDIR}/Microchip/Common/uart2.o: Microchip/Common/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/uart2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/uart2.o.d" -o ${OBJECTDIR}/Microchip/Common/uart2.o Microchip/Common/uart2.c   
	
${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver/usb_function_audio.o: Microchip/USB/Audio\ Device\ Driver/usb_function_audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver/usb_function_audio.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o.d" -o "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o" "Microchip/USB/Audio Device Driver/usb_function_audio.c"   
	
${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o: Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.o: Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o" "Microchip/USB/CDC Host Driver/usb_host_cdc.c"   
	
${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.o: Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o" "Microchip/USB/CDC Host Driver/usb_host_cdc_interface.c"   
	
${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver/usb_host_charger.o: Microchip/USB/Charger\ Host\ Driver/usb_host_charger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver/usb_host_charger.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o.d" -o "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o" "Microchip/USB/Charger Host Driver/usb_host_charger.c"   
	
${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o: Microchip/USB/Generic\ Device\ Driver/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" -o "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" "Microchip/USB/Generic Device Driver/usb_function_generic.c"   
	
${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver/usb_host_generic.o: Microchip/USB/Generic\ Host\ Driver/usb_host_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver/usb_host_generic.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o.d" -o "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o" "Microchip/USB/Generic Host Driver/usb_host_generic.c"   
	
${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver/usb_function_hid.o: Microchip/USB/HID\ Device\ Driver/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver/usb_function_hid.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o.d" -o "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o" "Microchip/USB/HID Device Driver/usb_function_hid.c"   
	
${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid.o: Microchip/USB/HID\ Host\ Driver/usb_host_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o.d" -o "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o" "Microchip/USB/HID Host Driver/usb_host_hid.c"   
	
${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.o: Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o.d" -o "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o" "Microchip/USB/HID Host Driver/usb_host_hid_parser.c"   
	
${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver/usb_function_msd.o: Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver/usb_function_msd.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o.d" -o "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o" "Microchip/USB/MSD Device Driver/usb_function_msd.c"   
	
${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd.o: Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o.d" -o "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o" "Microchip/USB/MSD Host Driver/usb_host_msd.c"   
	
${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.o: Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o.d" -o "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o" "Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o" "Microchip/USB/Printer Host Driver/usb_host_printer.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o" "Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o" "Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o" "Microchip/USB/Printer Host Driver/usb_host_printer_postscript.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o" "Microchip/USB/Printer Host Driver/usb_host_printer_primitives.c"   
	
${OBJECTDIR}/Microchip/USB/usb_device.o: Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_device.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_device.o Microchip/USB/usb_device.c   
	
${OBJECTDIR}/Microchip/USB/usb_host.o: Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_host.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_host.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_host.o Microchip/USB/usb_host.c   
	
${OBJECTDIR}/Microchip/USB/usb_otg.o: Microchip/USB/usb_otg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_otg.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_otg.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_otg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_otg.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_otg.o Microchip/USB/usb_otg.c   
	
else
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
	
${OBJECTDIR}/Microchip/Common/timer.o: Microchip/Common/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/timer.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/timer.o.d" -o ${OBJECTDIR}/Microchip/Common/timer.o Microchip/Common/timer.c   
	
${OBJECTDIR}/Microchip/Common/uart2.o: Microchip/Common/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/Common 
	@${RM} ${OBJECTDIR}/Microchip/Common/uart2.o.d 
	@${RM} ${OBJECTDIR}/Microchip/Common/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/Common/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/Common/uart2.o.d" -o ${OBJECTDIR}/Microchip/Common/uart2.o Microchip/Common/uart2.c   
	
${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver/usb_function_audio.o: Microchip/USB/Audio\ Device\ Driver/usb_function_audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Audio\ Device\ Driver/usb_function_audio.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o.d" -o "${OBJECTDIR}/Microchip/USB/Audio Device Driver/usb_function_audio.o" "Microchip/USB/Audio Device Driver/usb_function_audio.c"   
	
${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o: Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Device Driver/usb_function_cdc.o" "Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.o: Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc.o" "Microchip/USB/CDC Host Driver/usb_host_cdc.c"   
	
${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.o: Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/CDC\ Host\ Driver/usb_host_cdc_interface.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o.d" -o "${OBJECTDIR}/Microchip/USB/CDC Host Driver/usb_host_cdc_interface.o" "Microchip/USB/CDC Host Driver/usb_host_cdc_interface.c"   
	
${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver/usb_host_charger.o: Microchip/USB/Charger\ Host\ Driver/usb_host_charger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Charger\ Host\ Driver/usb_host_charger.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o.d" -o "${OBJECTDIR}/Microchip/USB/Charger Host Driver/usb_host_charger.o" "Microchip/USB/Charger Host Driver/usb_host_charger.c"   
	
${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o: Microchip/USB/Generic\ Device\ Driver/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Generic\ Device\ Driver/usb_function_generic.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o.d" -o "${OBJECTDIR}/Microchip/USB/Generic Device Driver/usb_function_generic.o" "Microchip/USB/Generic Device Driver/usb_function_generic.c"   
	
${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver/usb_host_generic.o: Microchip/USB/Generic\ Host\ Driver/usb_host_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Generic\ Host\ Driver/usb_host_generic.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o.d" -o "${OBJECTDIR}/Microchip/USB/Generic Host Driver/usb_host_generic.o" "Microchip/USB/Generic Host Driver/usb_host_generic.c"   
	
${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver/usb_function_hid.o: Microchip/USB/HID\ Device\ Driver/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/HID\ Device\ Driver/usb_function_hid.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o.d" -o "${OBJECTDIR}/Microchip/USB/HID Device Driver/usb_function_hid.o" "Microchip/USB/HID Device Driver/usb_function_hid.c"   
	
${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid.o: Microchip/USB/HID\ Host\ Driver/usb_host_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o.d" -o "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid.o" "Microchip/USB/HID Host Driver/usb_host_hid.c"   
	
${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.o: Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/HID\ Host\ Driver/usb_host_hid_parser.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o.d" -o "${OBJECTDIR}/Microchip/USB/HID Host Driver/usb_host_hid_parser.o" "Microchip/USB/HID Host Driver/usb_host_hid_parser.c"   
	
${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver/usb_function_msd.o: Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/MSD\ Device\ Driver/usb_function_msd.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o.d" -o "${OBJECTDIR}/Microchip/USB/MSD Device Driver/usb_function_msd.o" "Microchip/USB/MSD Device Driver/usb_function_msd.c"   
	
${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd.o: Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o.d" -o "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd.o" "Microchip/USB/MSD Host Driver/usb_host_msd.c"   
	
${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.o: Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o.d" -o "${OBJECTDIR}/Microchip/USB/MSD Host Driver/usb_host_msd_scsi.o" "Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer.o" "Microchip/USB/Printer Host Driver/usb_host_printer.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_esc_pos.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.o" "Microchip/USB/Printer Host Driver/usb_host_printer_esc_pos.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_pcl_5.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.o" "Microchip/USB/Printer Host Driver/usb_host_printer_pcl_5.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_postscript.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_postscript.o" "Microchip/USB/Printer Host Driver/usb_host_printer_postscript.c"   
	
${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.o: Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver 
	@${RM} ${OBJECTDIR}/Microchip/USB/Printer\ Host\ Driver/usb_host_printer_primitives.o.d 
	@${RM} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o" 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o.d" -o "${OBJECTDIR}/Microchip/USB/Printer Host Driver/usb_host_printer_primitives.o" "Microchip/USB/Printer Host Driver/usb_host_printer_primitives.c"   
	
${OBJECTDIR}/Microchip/USB/usb_device.o: Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_device.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_device.o Microchip/USB/usb_device.c   
	
${OBJECTDIR}/Microchip/USB/usb_host.o: Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_host.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_host.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_host.o Microchip/USB/usb_host.c   
	
${OBJECTDIR}/Microchip/USB/usb_otg.o: Microchip/USB/usb_otg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microchip/USB 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_otg.o.d 
	@${RM} ${OBJECTDIR}/Microchip/USB/usb_otg.o 
	@${FIXDEPS} "${OBJECTDIR}/Microchip/USB/usb_otg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Microchip/USB/usb_otg.o.d" -o ${OBJECTDIR}/Microchip/USB/usb_otg.o Microchip/USB/usb_otg.c   
	
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
