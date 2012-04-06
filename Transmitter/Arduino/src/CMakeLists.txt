#=============================================================================#
# Author: QueezyTheGreat                                                      #
# Date:   26.04.2011                                                          #
#                                                                             #
# Description:  Transmitter               firmware                            #
#                                                                             #
#=============================================================================#


#====================================================================#
#  Settings                                                          #
#====================================================================#
set(FIRMWARE_NAME Transmitter)

#set(${FIRMWARE_NAME}_lib_SRCS  Transmitter_lib.cpp)
#set(${FIRMWARE_NAME}_lib_HDRS  Transmitter_lib.h)
#set(${FIRMWARE_NAME}_lib_BOARD uno)
#generate_arduino_library(${FIRMWARE_NAME}_lib)

#set(disp_lib_SRCS  dispositivo.cpp)
#set(disp_lib_HDRS  dispositivo.h)
#set(disp_lib_BOARD uno)
#generate_arduino_library(disp_lib)



set(${FIRMWARE_NAME}_SRCS Transmitter.cpp)    # Firmware sources
#set(${FIRMWARE_NAME}_HDRS Transmitter_lib.h)    # Firmware sources
#set(${FIRMWARE_NAME}_LIBS  ${FIRMWARE_NAME}_lib)

set(${FIRMWARE_NAME}_BOARD uno)               # Arduino Target board

set(${FIRMWARE_NAME}_PORT /dev/ttyACM0)            # Serial upload port


#====================================================================#
#  Target generation                                                 #
#====================================================================#
generate_arduino_firmware(${FIRMWARE_NAME})
