set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR AVR)

set(TOOLCHAIN_PREFIX "avr-")

find_program(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
find_program(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
find_program(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

set(CMAKE_CXX_FLAGS "-Os -DF_CPU=16000000UL -mmcu=atmega328p -fno-exceptions")
set(CMAKE_C_FLAGS   "-Os -DF_CPU=16000000UL -mmcu=atmega328p")

set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
