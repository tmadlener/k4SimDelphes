cmake_minimum_required(VERSION 3.3)

project(k4SimDelphes)

#--- Declare options -----------------------------------------------------------

option(BUILD_PYTHIA_READER "Build the EDM4hep plugin for DD4hep" ON)
option(BUILD_EVTGEN_READER "Build the DELPHES plugin for DD4hep" ON)
option(BUILD_HEPMC_READER "Build the DELPHES plugin for DD4hep" ON)
option(BUILD_FRAMEWORK "Build the DELPHES plugin for DD4hep" OFF)
option(K4SIMDELPHES_DOCUMENTATION "Whether or not to create doxygen doc target." OFF)
option(ENABLE_CPACK "Whether or not to use cpack config" OFF)
option(USE_EXTERNAL_CATCH2 "If off, build the catch2 unittest framework locally" OFF)

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 0 )
SET( ${PROJECT_NAME}_VERSION_MINOR 1 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

SET( ${PROJECT_NAME}_VERSION  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}" )


set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

if(NOT CMAKE_CXX_STANDARD MATCHES "17")
  message(FATAL_ERROR "Unsupported C++ standard: ${CMAKE_CXX_STANDARD}")
endif()

message (STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")

#--- add version files ---------------------------------------------------------


# - Use GNU-style hierarchy for installing build products
include(GNUInstallDirs)

#--- setup build type (and default) if supported -------------------------------
if (NOT CMAKE_CONFIGURATION_TYPES)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo
      CACHE STRING "Choose the type of build, options are: None|Release|MinSizeRel|Debug|RelWithDebInfo" FORCE)
  else()
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
      CACHE STRING "Choose the type of build, options are: None|Release|MinSizeRel|Debug|RelWithDebInfo" FORCE)
  endif()
endif()

configure_file(${CMAKE_SOURCE_DIR}/k4SimDelphesVersion.h
               ${CMAKE_BINARY_DIR}/k4SimDelphesVersion.h )
install(FILES ${CMAKE_BINARY_DIR}/k4SimDelphesVersion.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/k4SimDelphes )


#--- add CMake infrastructure --------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(cmake/k4SimDelphesCreateConfig.cmake)

#--- add license files ---------------------------------------------------------
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
              DESTINATION ${CMAKE_INSTALL_DOCDIR})

#--- enable unit testing capabilities ------------------------------------------
include(CTest)

#--- enable CPack --------------------------------------------------------------
if(ENABLE_CPACK)
  include(cmake/k4SimDelphesCPack.cmake)
endif()

#--- target for Doxygen documentation ------------------------------------------
if(K4SIMDELPHES_DOCUMENTATION)
  include(cmake/k4SimDelphesDoxygen.cmake)
endif()


#--- Non-optional Dependencies ------------------------------------------

find_package(Delphes)
find_package(EDM4HEP)

add_subdirectory(converter)
add_subdirectory(standalone)
if(BUILD_FRAMEWORK)
  add_subdirectory(framework)
endif()

if(BUILD_TESTING)
  option(BUILD_UNITTESTS "Build the unittest for k4SimDelphes" ON)
  add_subdirectory(tests)
endif()


#--- create uninstall target ---------------------------------------------------
include(cmake/k4SimDelphesUninstall.cmake)
