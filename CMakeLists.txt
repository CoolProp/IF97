cmake_minimum_required(VERSION 2.8.11)

#######################################
#         PROJECT INFORMATION         #
#-------------------------------------#
# This CMakeLists.txt file is for the #
# IAPWS-IF97 thermodynamic library    #
# written by Ian Bell and Jeff        #
# Henning. The following  section     #
# contains project and version        #
# information.                        #
#######################################

# Project name
set(project_name "IF97")
set(app_name ${project_name})
project(${project_name})

#########################################################################
#                              WRAPPER MODULES                          #
#-----------------------------------------------------------------------#
# Wrapper module compilation should be flagged from the command line.   #
# Each wrapper should set(IF97_FLAG ON) to indicate a module was built. #
# If no module is specified on the command line, the IF97_FLAG is not   #
# set and the default test program is built.                            #
#########################################################################

#########################
#  MATHCAD PRIME MODULE #
#########################
option(IF97_PRIME_MODULE "Build MathCAD Prime wrapper" OFF)
if (IF97_PRIME_MODULE)
    set(CMAKE_BUILD_TYPE Release CACHE)
    set(IF97_FLAG ON)
    if(NOT WIN32)
      message(FATAL_ERROR "IF97_PRIME_MODULE can only be used on windows host")
    endif()
    IF( "${IF97_PRIME_ROOT}" STREQUAL "")
        message(FATAL_ERROR "You must provide the path to MathCAD Prime Root directory using something like -DIF97_PRIME_ROOT=\"C:/Program Files/PTC/Mathcad Prime 3.1\"")
    else()
        message(STATUS "IF97_PRIME_ROOT: ${IF97_PRIME_ROOT}")
    endif()
    FILE(GLOB_RECURSE IF97_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes/*.h")
    include_directories("${IF97_PRIME_ROOT}/Custom Functions" "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes")
    add_library(IF97 SHARED ${IF97_HEADERS} "${CMAKE_CURRENT_SOURCE_DIR}/IF97.h" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/MathCAD/IF97.cpp")
    target_link_libraries(IF97 "${IF97_PRIME_ROOT}/Custom Functions/mcaduser.lib")
    SET_TARGET_PROPERTIES(IF97 PROPERTIES LINK_FLAGS "/ENTRY:\"DllEntryPoint\"")
    set_target_properties(IF97 PROPERTIES SUFFIX ".dll" PREFIX "")
#    install (TARGETS IF97 DESTINATION "${IF97_INSTALL_PREFIX}/MathCADPrime")
#    install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/MathCAD/if97_validation.mcdx" DESTINATION MathCADPrime)
endif()

#########################
#   MATHCAD 15 MODULE   #
#########################
option(IF97_MATHCAD15_MODULE "Build MathCAD 15 wrapper" OFF)
if (IF97_MATHCAD15_MODULE)
    set(CMAKE_BUILD_TYPE Release CACHE)
    set(IF97_FLAG ON)
    if(NOT WIN32)
      message(FATAL_ERROR "IF97_MATHCAD15_MODULE can only be used on windows host")
    endif()
    IF( "${IF97_MATHCAD15_ROOT}" STREQUAL "")
        message(FATAL_ERROR "You must provide the path to MathCAD 15 Root directory using something like -DIF97_MATHCAD15_ROOT=\"C:/Program Files (x86)/Mathcad/Mathcad 15\"")
    else()
        message(STATUS "IF97_MATHCAD15_ROOT: ${IF97_MATHCAD15_ROOT}")
    endif()
    FILE(GLOB_RECURSE IF97_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes/*.h")
    include_directories("${IF97_MATHCAD15_ROOT}/userefi/microsft/include" "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes")
    add_library(IF97 SHARED ${IF97_HEADERS} "${CMAKE_CURRENT_SOURCE_DIR}/IF97.h" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/MathCAD/IF97.cpp")
    target_link_libraries(IF97 "${IF97_MATHCAD15_ROOT}/userefi/microsft/lib/mcaduser.lib")
    SET_TARGET_PROPERTIES(IF97 PROPERTIES LINK_FLAGS "/ENTRY:\"DllEntryPoint\"")
    set_target_properties(IF97 PROPERTIES SUFFIX ".dll" PREFIX "")
 #   install (TARGETS IF97 DESTINATION "${IF97_INSTALL_PREFIX}/MathCAD15")
 #   install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/MathCAD/if97_validation.xmcdz" DESTINATION MathCAD15)
 #   install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/MathCAD/if97_EN.xml" DESTINATION MathCAD15)
endif()

###########################
# CMAKE INTERFACE LIBRARY #
###########################
option(IF97_CMAKE_MODULE "Build CMake interface library" OFF)
if(IF97_CMAKE_MODULE)
    set(CMAKE_BUILD_TYPE Release CACHE)
    set(IF97_FLAG ON)
    message(STATUS "Building IF97 CMake interface library")
    #add_library(IF97 STATIC "${CMAKE_CURRENT_SOURCE_DIR}/IF97.h")
    #set_target_properties(IF97 PROPERTIES LINKER_LANGUAGE CXX)
    add_library(IF97 INTERFACE)
    #target_include_directories(IF97 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
    target_include_directories(IF97 INTERFACE  
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/IF97>  
        $<INSTALL_INTERFACE:include/IF97>  # <prefix>/include/IF97
    )
    install(
        FILES IF97.h
        DESTINATION "include"
    )
endif()

#########################
# TEST MODULE (DEFAULT) #
#########################
option(IF97_FLAG "Skip IF97 test executable" OFF)
if (NOT IF97_FLAG)
    message(STATUS "Stand-alone IF97 Test.")
    add_executable(IF97 "${CMAKE_CURRENT_SOURCE_DIR}/IF97.cpp")
endif()

