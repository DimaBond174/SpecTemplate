# ************** Prepare **************
include(cmake/prepare.cmake)
set(LIB_testclient "testclient")
set(LIB_testclient_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/client/testclient.cpp
  ${SPEC_SRC_COMMON}/log/speclog/speclog.cpp
  ${SQLDB__SRC}
  )
set(LIB_testclient_INCLUDES
    ${SPEC_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SQLDB_INCLUDE}
    )
set(LIB_testclient_DEFINITIONS
    ${SPEC_DEFINITIONS}
    ${SPEC_DB}
    )

set(LIB_testclient_LINK_LIBS
    ${SQLDB_LIBS}
    )

custom_add_static_lib( ${LIB_testclient}
    "${SPEC_BUILD_DIR}"
    "${LIB_testclient_SRC}"
    "${LIB_testclient_INCLUDES}"
    "${LIB_testclient_DEFINITIONS}"
    "${LIB_testclient_LINK_LIBS}"
    )
#add_library(${LIB_testclient}
#    "${LIB_testclient_SRC}"
#    )

set(LIB_testsuite "testsuite")
set(LIB_testsuite_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/testsuite.cpp
  ${SPEC_SRC_COMMON}/log/speclog/speclog.cpp
  ${SPEC_SRC_COMMON}/config/json/configjson.cpp
  ${SPEC_SRC_COMMON}/file/fileadapter.cpp
  ${SPEC_SRC_COMMON}/tools/spec_os.cpp
  ${OS_SRC}
  )
set(LIB_testsuite_INCLUDES
    ${SPEC_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SPEC_SRC_COMMON}/config/json/configjson.cpp
    ${SPEC_SRC_COMMON}/file/fileadapter.cpp
    ${OS_INCLUDE}
    )

set(LIB_testsuite_DEFINITIONS
    ${SPEC_DEFINITIONS}
    ${SPEC_DB}
    )

set(LIB_testsuite_LINK_LIBS
    ${LIB_testclient}
    ${OS_LIBS}
    )

custom_add_static_lib( ${LIB_testsuite}
    "${SPEC_BUILD_DIR}"
    "${LIB_testsuite_SRC}"
    "${LIB_testsuite_INCLUDES}"
    "${LIB_testsuite_DEFINITIONS}"
    "${LIB_testsuite_LINK_LIBS}"
    )

# Compile test exe without test:
set(EXE_NAME "test_exe")
set(EXE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/test_exe/test_exe.cpp
    )
set(EXE_INCLUDE
    ${SPEC_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
set(EXE_DEFINITIONS
    ${SPEC_DEFINITIONS}
    )
set(EXE_LINK_LIBS
    "${LIB_testsuite}"
    )
set(EXE_PROPERTIES
    "${SPEC_PROPERTIES}"
    )

custom_add_executable(${EXE_NAME}
    "${SPEC_BUILD_DIR}"
    "${EXE_SRC}"
    "${EXE_INCLUDE}"
    "${EXE_DEFINITIONS}"
    "${EXE_LINK_LIBS}"
    "${EXE_PROPERTIES}"
    )

# Compile test
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${CMAKE_CURRENT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

set(GOOGLETEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})

add_executable(
    unit_tests
    test/main.cpp
    test/example_add.cpp
    test/example_subtract.cpp
    )

add_dependencies(unit_tests googletest)

target_link_libraries(
    unit_tests
    googletest
    ${LIB_testsuite}
    pthread
    )

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)
