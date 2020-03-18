# This is the source code of SpecNet project
#
#  Copyright (c) Dmitriy Bondarenko
#  feel free to contact me: specnet.messenger@gmail.com

# Configuration of the assembly
#   according to the selected components:
set(SRV_DEFINITIONS
	${SPEC_DEFINITIONS}
    ${SPEC_DB}
)

set(SRV_PROPERTIES
  ${SPEC_PROPERTIES}
)

set(SRV_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )

set(SRV_INCLUDE
    ${SPEC_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)

#if("${SPEC_LOGGER}" STREQUAL "DSpdLog")
#   message(STATUS "SpdLog logger was chosen ")
#   set(SPEC_INCLUDE
#       ${SPEC_INCLUDE}
#       ${CMAKE_CURRENT_SOURCE_DIR}/src/depend/log/spdlog/include
#       )
#   file(GLOB_RECURSE LOC_SRC
#       ${CMAKE_CURRENT_SOURCE_DIR}/src/depend/log/spdlog/*.h
#       ${CMAKE_CURRENT_SOURCE_DIR}/src/depend/log/spdlog/*.cpp
#   )
#   set(SPEC_SRC ${SPEC_SRC}  ${LOC_SRC})
#else()

#   file(GLOB_RECURSE LOC_SRC
#       ${SPEC_SRC_COMMON}/src/depend/log/speclog/*.h
#       ${CMAKE_CURRENT_SOURCE_DIR}/src/depend/log/speclog/*.cpp
#   )
  message(STATUS "SpecLog logger was chosen ")
   set(SRV_SRC
     ${SRV_SRC}
     ${SPEC_SRC_COMMON}/log/speclog/speclog.cpp
     )
#endif()


if("${SRV_DB}" STREQUAL "DSQLiteDB")
    message(STATUS "SQLiteDB was chosen for Service")
#    add_library(sqlite3
#     STATIC
#     ${SPEC_SRC_COMMON}/db/sqlite/sqlite3/sqlite3.c
#     ${SPEC_SRC_COMMON}/db/sqlite/sqlite3/sqlite3.h
#    )

   set(SRV_INCLUDE
      ${SRV_INCLUDE}
      ${SQLDB_INCLUDE}
      #${SPEC_SRC_COMMON}/db/sqlite/sqlite3
      )
    #if (SPEC_TESTS STREQUAL "ON")
    #    set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS " -fPIC  ")
    #endif()

    set(SRV_LINK_LIBS
        ${SRV_LINK_LIBS}
        ${SQLDB_LIBS}
        #sqlite3
        #dl
    )
#    set(SRV_SRC ${SRV_SRC}
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/server/db/sqlite/sqlitedb.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/server/db/sqlite/sqlitedb.h
#        #${CMAKE_CURRENT_SOURCE_DIR}/src/depend/db/sqlite/sqlite3/sqlite3.h
#        )
endif()


#if("${SPEC_ENCRYPT}" STREQUAL "DSpecSSL")
   message(STATUS "SpecSSL was chosen for Service ")
   set(SRV_INCLUDE
       ${SRV_INCLUDE}
       ${SSL_INCLUDE}
#       ${SPEC_SRC_COMMON}/encrypt/boringssl/include
       )
#   file(GLOB_RECURSE LOC_SRC
##       ${CMAKE_CURRENT_SOURCE_DIR}/src/depend/encrypt/boringssl/*.h
#       ${CMAKE_CURRENT_SOURCE_DIR}/src/depend/encrypt/boringssl/*.cpp
#   )
#   set(SPEC_SRC ${SPEC_SRC}  ${LOC_SRC})
#   add_library( crypto
#                STATIC
#                IMPORTED )
#   add_library( decrepit
#                STATIC
#                IMPORTED )
#   add_library( ssl
#                STATIC
#                IMPORTED )

   set(SRV_LINK_LIBS
                ${SRV_LINK_LIBS}
                ${SSL_LIBS}
#                decrepit
#                ssl
#                crypto
            )

#    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
#        set_target_properties( # Specifies the target library.
#            crypto
#            PROPERTIES IMPORTED_LOCATION
#            ${SPEC_LIB_DIR}/libcrypto.a )
#        set_target_properties( # Specifies the target library.
#            decrepit
#            PROPERTIES IMPORTED_LOCATION
#            ${SPEC_LIB_DIR}/libdecrepit.a )
#        set_target_properties( # Specifies the target library.
#            ssl
#            PROPERTIES IMPORTED_LOCATION
#            ${SPEC_LIB_DIR}/libssl.a )
#	elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
#        set_target_properties( # Specifies the target library.
#            crypto
#            PROPERTIES IMPORTED_LOCATION
#            ${SPEC_LIB_DIR}/crypto.lib )
#        set_target_properties( # Specifies the target library.
#            decrepit
#            PROPERTIES IMPORTED_LOCATION
#            ${SPEC_LIB_DIR}/decrepit.lib )
#        set_target_properties( # Specifies the target library.
#            ssl
#            PROPERTIES IMPORTED_LOCATION
#            ${SPEC_LIB_DIR}/ssl.lib )
#    endif()
#endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
   message(STATUS "Linux was chosen ")
   set(SRV_INCLUDE
       ${SRV_INCLUDE}
       ${CMAKE_CURRENT_SOURCE_DIR}/src/service/linux
       ${OS_INCLUDE}
       //${SPEC_SRC_COMMON}/system/linux
       )

#   file(GLOB_RECURSE LOC_SRC
#       ${CMAKE_CURRENT_SOURCE_DIR}/service/linux/*.cpp
#   )
   set(SRV_SRC
     ${SRV_SRC}
     ${CMAKE_CURRENT_SOURCE_DIR}/src/service/linux/linuxservice.cpp
     ${OS_SRC}
#     ${SPEC_SRC_COMMON}/system/linux/linuxsystem.cpp
     )

   set(SRV_LINK_LIBS
             ${SRV_LINK_LIBS}
             ${OS_LIBS}
#             dl
#            pthread
#            stdc++fs
         )

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
   message(STATUS "Windows was chosen ")
   set(SRV_INCLUDE
       ${SRV_INCLUDE}
       ${CMAKE_CURRENT_SOURCE_DIR}/src/service/windows
       ${OS_INCLUDE}
       )

#   file(GLOB_RECURSE LOC_SRC
#       ${CMAKE_CURRENT_SOURCE_DIR}/serv/windows/*.cpp
#   )
#   set(SRV_SRC ${SRV_SRC}  ${LOC_SRC})
  set(SRV_SRC
    ${SRV_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/service/linux/linuxservice.cpp
    ${OS_SRC}
#    ${SPEC_SRC_COMMON}/system/linux/linuxsystem.cpp
    )

   set(SRV_DEFINITIONS
    ${SRV_DEFINITIONS}
    ${OS_DEFINITIONS}
#    "WIN32_LEAN_AND_MEAN"
#    FD_SETSIZE=1024
  )
endif()


# Coping assets (TODO any change&rerun CMake to copy):
FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
FILE(GLOB_RECURSE SpecAssets
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.*
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/*
)

FOREACH(file ${SpecAssets})
    FILE(RELATIVE_PATH
        ITEM_PATH_REL
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${file}
    )
    GET_FILENAME_COMPONENT(dirname ${ITEM_PATH_REL} DIRECTORY)
#    message("File: ${ITEM_PATH_REL}")
#    message("Relative path: ${dirname}")
    FILE(MAKE_DIRECTORY ${SPEC_BUILD_DIR}/assets/${dirname})
#    GET_FILENAME_COMPONENT(filename ${file} NAME)
    FILE(COPY ${file} DESTINATION ${SPEC_BUILD_DIR}/assets/${dirname})
ENDFOREACH()

# Coping custom libs:
FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs)
FILE(GLOB SpecLibs "libs/*.*")
FOREACH(file ${SpecLibs})
    GET_FILENAME_COMPONENT(filename ${file} NAME)
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/${filename} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs)
ENDFOREACH()




