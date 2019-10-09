function(add_hex_file target)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex
        COMMAND avr-objcopy -O ihex -R .eeprom $<TARGET_FILE:${target}> ${target}.hex
        COMMENT "creating hex file..."
        DEPENDS ${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
    )

    add_custom_target(
        ${target}.hex
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex
    )
endfunction()

function(add_arduino_deploy target)
    if (NOT TARGET ${target}.hex)
        add_hex_file(${target})
    endif ()

    add_custom_target(
        ${target}-deploy
        DEPENDS ${target}.hex
        COMMAND avrdude -F -V -c arduino -p ATMEGA328P -P /dev/pts/7 -b 115200  -U flash:w:${CMAKE_CURRENT_BINARY_DIR}/${target}.hex
    )
endfunction()
