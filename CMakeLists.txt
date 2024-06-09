cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(computer_architecture)

add_executable(pr02
    console/main.c)

target_link_libraries(pr02 PRIVATE console mySimpleComputer)

add_library(console STATIC
    console/printAccumulator.c
    console/printCell.c
    console/printCounters.c
    console/printDecodedCommand.c
    console/printFlags.c)

target_include_directories(console PUBLIC console)

add_library(mySimpleComputer STATIC
    mySimpleComputer/sc_accumulatorGet.c
    mySimpleComputer/sc_accumulatorInit.c
    mySimpleComputer/sc_accumulatorSet.c
    mySimpleComputer/sc_commandDecode.c
    mySimpleComputer/sc_commandEncode.c
    mySimpleComputer/sc_commandValidate.c
    mySimpleComputer/sc_icounterGet.c
    mySimpleComputer/sc_icounterInit.c
    mySimpleComputer/sc_icounterSet.c
    mySimpleComputer/sc_memoryGet.c
    mySimpleComputer/sc_memoryInit.c
    mySimpleComputer/sc_memoryLoad.c
    mySimpleComputer/sc_memorySave.c
    mySimpleComputer/sc_memorySet.c
    mySimpleComputer/sc_regGet.c
    mySimpleComputer/sc_regInit.c
    mySimpleComputer/sc_regSet.c
    mySimpleComputer/sc_variables.c)

target_include_directories(mySimpleComputer PUBLIC include)
