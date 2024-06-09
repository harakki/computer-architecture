cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(computer_architecture)

add_executable(simpleComputer
    console/main.c)

target_link_libraries(simpleComputer PRIVATE console mySimpleComputer myTerm)

add_library(console STATIC
    console/printAccumulator.c
    console/printCell.c
    console/printCommand.c
    console/printCounters.c
    console/printDecodedCommand.c
    console/printFlags.c
    console/printKeys.c
    console/printTerm.c
    console/printTui.c)

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
    mySimpleComputer/sc_reset.c
    mySimpleComputer/sc_variables.c)

target_include_directories(mySimpleComputer PUBLIC include)

add_library(myTerm STATIC
    myTerm/mt_calculatePosition.c
    myTerm/mt_clrscr.c
    myTerm/mt_delLine.c
    myTerm/mt_getScreenSize.c
    myTerm/mt_gotoXY.c
    myTerm/mt_setBgColor.c
    myTerm/mt_setCursorVisibility.c
    myTerm/mt_setDefaultColor.c
    myTerm/mt_setFgColor.c
    myTerm/mt_termDequeue.c
    myTerm/mt_termEnqueue.c
    myTerm/mt_termInit.c
    myTerm/mt_variables.c)

target_include_directories(myTerm PUBLIC include)
