cmake_minimum_required(VERSION 3.20)

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

function(get_version file_name output)
  file(STRINGS "${file_name}" FIRST_MATCH REGEX "(.*IF97VERSION.*\")(v[0-9](\\.[0-9])*)(\".*)")
  #message(STATUS "[${PROJECT_NAME}] - Found version number: ${FIRST_MATCH}")
  string(REGEX MATCH "[0-9]\\.[0-9]\\.[0-9]" SECOND_MATCH "${FIRST_MATCH}")
  if(SECOND_MATCH)
    message(STATUS "[IF97] - Found version number: ${SECOND_MATCH}")
    set(${output} ${SECOND_MATCH} PARENT_SCOPE)
  else()
    message(FATAL_ERROR "Data were not found for the required build specification.")
  endif() 
endfunction()

get_version("${CMAKE_CURRENT_LIST_DIR}/IF97.h" VERSION)

# Project name
project("IF97" LANGUAGES CXX VERSION ${VERSION})

message(STATUS "[${PROJECT_NAME}] - Building v${PROJECT_VERSION} of ${PROJECT_NAME}")
string(REPLACE "." "," IF97_VERSION "${VERSION}")

option(IF97_PRIME_MODULE "Build MathCAD Prime wrapper" OFF)
option(IF97_MATHCAD15_MODULE "Build MathCAD 15 wrapper" OFF)
option(IF97_HEADER_MODULE "Install header file only" OFF)
option(IF97_CMAKE_MODULE "Install CMake interface library" OFF)
option(IF97_FLAG "Skip IF97 test executable" OFF)

list(APPEND options ${IF97_PRIME_MODULE} ${IF97_MATHCAD15_MODULE} ${IF97_HEADER_MODULE} ${IF97_CMAKE_MODULE} ${IF97_FLAG})
set(options_count 0)
foreach(option_value ${options})
  if(option_value)
    math(EXPR options_count "${options_count}+1")
  endif()
endforeach(option_value)

if(${options_count} GREATER 1)
  message(FATAL_ERROR "[${PROJECT_NAME}] - You cannot select more than one option to build.")
elseif(${options_count} LESS 1)
  message(STATUS "[${PROJECT_NAME}] - No option selected, building the test executable.")
  set(IF97_FLAG ON)
endif()

#set(options_count 0)
#set(options_index 0)
#list(LENGTH options count)
#while(index LESS count)
#  list(GET ${options} ${index} item)
#  if(item)
#    math(EXPR options_count "${options_count}+1")
#  endif()
#  math(EXPR index "${index}+1")
#endwhile(index LESS count)

#########################################################################
#                              WRAPPER MODULES                          #
#-----------------------------------------------------------------------#
# Wrapper module compilation should be flagged from the command line.   #
# If no module is specified on the command line, the IF97_FLAG is not   #
# set and the default test program is built.                            #
#########################################################################

#########################
#  MATHCAD PRIME MODULE #
#########################
if(IF97_PRIME_MODULE)
    # Make sure we're on Winows - the only platform on which Mathad Prime runs
    if(NOT WIN32)
      message(FATAL_ERROR "[${PROJECT_NAME}] - IF97_PRIME_MODULE can only be used on windows host")
    endif()
    # Check for valid Mathacd Prime Root directory provided by user.  If not provided, try to find it on our own.
    if( "${IF97_PRIME_ROOT}" STREQUAL "")
        # PTC/Mathcad convention is a directory labeled "C:\Program Files\PTC\Mathad Prime X.X.X.X"
        # Find all of these directories on the system and try to set IF97_PRIME_ROOT dynamically
        file(GLOB PTC_CONTENTS 
            LIST_DIRECTORIES true 
            "C:/Program Files/PTC/Mathcad Prime*"
        )
        # Add them to a list, sorted by most recent Marhcad Prime release first
        set(MATHCAD_SEARCH_PATHS "")
        foreach(ITEM ${PTC_CONTENTS})
            if(IS_DIRECTORY "${ITEM}")
                list(APPEND MATHCAD_SEARCH_PATHS "${ITEM}")
            endif()
        endforeach()
        list(SORT MATHCAD_SEARCH_PATHS COMPARE NATURAL ORDER DESCENDING)
        # Now make sure the executable is in one of these directories (newest first)
        find_program(MATHCAD_EXE
          NAMES MathcadPrime.exe
          PATHS ${MATHCAD_SEARCH_PATHS})
        # Strip off program name, and set IF97_PRIME_ROOT to parent path
        #get_filename_comopnent(PARENT_DIR "$MATHCAD_EXE" MATHCAD_ROOT)
        if(MATHCAD_EXE)
          cmake_path(GET MATHCAD_EXE PARENT_PATH IF97_PRIME_ROOT)
          message(STATUS "[${PROJECT_NAME}] - Dynamically Found Mathcad @ \"${IF97_PRIME_ROOT}\"")
          string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$" MATHCAD_VERSION "${IF97_PRIME_ROOT}")
          message(STATUS "[${PROJECT_NAME}] - Linking with Mathcad Prime Library v${MATHCAD_VERSION}\"")
        else()
          message(STATUS "[${PROJECT_NAME}] - Could not Dynamically Locate Mathcad Prime on this System")
          message(FATAL_ERROR "[${PROJECT_NAME}] - You must provide the path to MathCAD Prime Root directory using something like -DIF97_PRIME_ROOT=\"C:/Program Files/PTC/Mathcad Prime 11.0.0.0\"")
        endif()
    else()
        # Mathcad Root directory specified.  Make sure it's a valid Mathcad Prime installation directory
        find_program(MATHCAD_EXE
          NAMES MathcadPrime.exe
          PATHS ${IF97_PRIME_ROOT})
        if(MATHCAD_EXE)
          string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$" MATHCAD_VERSION "${IF97_PRIME_ROOT}")
          message(STATUS "[${PROJECT_NAME}] - Linking with Mathcad Prime Library v${MATHCAD_VERSION}\"")
        else()
          message(STATUS "[${PROJECT_NAME}] - Could not find Mathcad Prime at ${IF97_PRIME_ROOT}")
          message(FATAL_ERROR "[${PROJECT_NAME}] - Check the path to the MathCAD Prime Root directory provided using something like -DIF97_PRIME_ROOT=\"C:/Program Files/PTC/Mathcad Prime 11.0.0.0\"")
        endif()
    endif()
    # Embed Windows VERSIONINFO so IF97.dll's Properties dialog shows
    # FileVersion/ProductVersion fields a la CoolProp(#2863). The .rc 
    # is configured from VERSION above and added to the source
    # list only on MSVC and MSYS2(MinGW), where rc.exe is available.
    set(IF97_RESOURCE "")
    if(MSVC)
      configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/dev/IF97.rc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/IF97.rc"
        @ONLY)
      list(APPEND IF97_RESOURCE "${CMAKE_CURRENT_BINARY_DIR}/IF97.rc")
    endif()
    file(GLOB_RECURSE IF97_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes/*.h")
    include_directories("${IF97_PRIME_ROOT}/Custom Functions" "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes")
    add_library(IF97 SHARED
      ${IF97_HEADERS}
      "${CMAKE_CURRENT_SOURCE_DIR}/IF97.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/MathCAD/IF97.cpp"
       ${IF97_RESOURCE})
    target_link_libraries(IF97 "${IF97_PRIME_ROOT}/Custom Functions/mcaduser.lib")
    set_target_properties(IF97 PROPERTIES LINK_FLAGS "/ENTRY:\"DllEntryPoint\"")
    set_target_properties(IF97 PROPERTIES SUFFIX ".dll" PREFIX "")
#    install(TARGETS IF97 DESTINATION "${IF97_INSTALL_PREFIX}/MathCADPrime")
#    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/MathCAD/if97_validation.mcdx" DESTINATION MathCADPrime)
endif()

#########################
#   MATHCAD 15 MODULE   #
#########################
if(IF97_MATHCAD15_MODULE)
    if(NOT WIN32)
      message(FATAL_ERROR "[${PROJECT_NAME}] - IF97_MATHCAD15_MODULE can only be used on windows host")
    endif()
    if( "${IF97_MATHCAD15_ROOT}" STREQUAL "")
        message(FATAL_ERROR "[${PROJECT_NAME}] - You must provide the path to MathCAD 15 Root directory using something like -DIF97_MATHCAD15_ROOT=\"C:/Program Files (x86)/Mathcad/Mathcad 15\"")
    else()
        message(STATUS "[${PROJECT_NAME}] - IF97_MATHCAD15_ROOT: ${IF97_MATHCAD15_ROOT}")
    endif()
    file(GLOB_RECURSE IF97_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes/*.h")
    include_directories("${IF97_MATHCAD15_ROOT}/userefi/microsft/include" "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/Mathcad/includes")
    add_library(IF97 SHARED ${IF97_HEADERS} "${CMAKE_CURRENT_SOURCE_DIR}/IF97.h" "${CMAKE_CURRENT_SOURCE_DIR}/wrapper/MathCAD/IF97.cpp")
    target_link_libraries(IF97 "${IF97_MATHCAD15_ROOT}/userefi/microsft/lib/mcaduser.lib")
    set_target_properties(IF97 PROPERTIES LINK_FLAGS "/ENTRY:\"DllEntryPoint\"")
    set_target_properties(IF97 PROPERTIES SUFFIX ".dll" PREFIX "")
 #   install(TARGETS IF97 DESTINATION "${IF97_INSTALL_PREFIX}/MathCAD15")
 #   install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/MathCAD/if97_validation.xmcdz" DESTINATION MathCAD15)
 #   install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/MathCAD/if97_EN.xml" DESTINATION MathCAD15)
endif()

#######################
# HEADER FILE LIBRARY #
#######################
if(IF97_HEADER_MODULE)
    message(STATUS "[${PROJECT_NAME}] - Building IF97 header library")
    add_library(IF97 INTERFACE)
    target_include_directories(IF97 INTERFACE  
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    install(FILES IF97.h DESTINATION "include")
endif()

###########################
# CMAKE INTERFACE LIBRARY #
###########################
if(IF97_CMAKE_MODULE)
    message(STATUS "[${PROJECT_NAME}] - Building IF97 CMake interface library")
    add_library(IF97 INTERFACE)
    target_include_directories(IF97 INTERFACE  
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    set(include_install_dir "include")
    set(config_install_dir "lib/cmake/${PROJECT_NAME}")
    set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
    set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
    set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
    set(namespace "${PROJECT_NAME}::")
    include(CMakePackageConfigHelpers)

    # Use:
    #   * PROJECT_VERSION
    write_basic_package_version_file(
        "${version_config}" COMPATIBILITY SameMajorVersion
    )

    # Use:
    #   * TARGETS_EXPORT_NAME
    #   * PROJECT_NAME
    configure_package_config_file(
        "cmake/Config.cmake.in"
        "${project_config}"
        INSTALL_DESTINATION "${config_install_dir}"
    )

    install(
        TARGETS IF97
        EXPORT "${TARGETS_EXPORT_NAME}"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "bin"
        INCLUDES DESTINATION "${include_install_dir}"
    )

    install(
        FILES IF97.h
        DESTINATION "${include_install_dir}"
    )

    install(
        FILES "${project_config}" "${version_config}"
        DESTINATION "${config_install_dir}"
    )

    install(
        EXPORT "${TARGETS_EXPORT_NAME}"
        NAMESPACE "${namespace}"
        DESTINATION "${config_install_dir}"
    )
endif()

#########################
# TEST MODULE (DEFAULT) #
#########################
if(IF97_FLAG)
    message(STATUS "[${PROJECT_NAME}] - Stand-alone IF97 Test.")
    add_executable(IF97 "${CMAKE_CURRENT_SOURCE_DIR}/IF97.cpp")
endif()

