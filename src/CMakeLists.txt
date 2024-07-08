##################################################################
# Executable name and version setup
##################################################################

# Set main target name. This is the name of the final ELF file
set(TARGET_NAME "aurix_sample_tc33x")

# Set executable name if not already set by user
set(EXECUTABLE_NAME "${TARGET_NAME}")

##################################################################
# Targets
##################################################################

add_executable(AurixExecutable Cpu0_Main.c Blinky_LED.c)
target_link_libraries(AurixExecutable PRIVATE InfineonLib)
target_include_directories(AurixExecutable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Make sure a map file is generated
target_link_options(AurixExecutable PRIVATE -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_NAME}.map)
# Set C standard for main target
target_compile_features(AurixExecutable PRIVATE c_std_99)

# force executable output name to be formatted as "EXEC_NAME.elf"
set_target_properties(AurixExecutable PROPERTIES OUTPUT_NAME ${EXECUTABLE_NAME} SUFFIX .elf)


# Add custom command to generate the .hex file, and
# create a custom target to build it
find_program(OBJDUMP_BIN NAMES tricore-objcopy tricore-elf-objcopy REQUIRED)
add_custom_command(
  OUTPUT ${EXECUTABLE_NAME}.hex
  COMMAND ${OBJDUMP_BIN} ${EXECUTABLE_NAME}.elf -O ihex ${EXECUTABLE_NAME}.hex
  DEPENDS AurixExecutable
  COMMENT "Generate ${EXECUTABLE_NAME}.hex"
  VERBATIM
)
add_custom_target(HexFile ALL DEPENDS ${EXECUTABLE_NAME}.hex)
