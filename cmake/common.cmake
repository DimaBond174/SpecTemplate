# This is the source code of SpecNet project
#
#  Copyright (c) Dmitriy Bondarenko
#  feel free to contact me: specnet.messenger@gmail.com

# Configuration of the assembly
#   according to the selected components:

if("${SRV_DB}" STREQUAL "DSQLiteDB")
    message(STATUS "SQLiteDB was chosen ")
    add_library(sqlite3
     STATIC
     ${SPEC_SRC_COMMON}/db/sqlite/sqlite3/sqlite3.c
     ${SPEC_SRC_COMMON}/db/sqlite/sqlite3/sqlite3.h
    )

   set(SQLDB_INCLUDE
      ${SPEC_SRC_COMMON}/db/sqlite/sqlite3
      )
    #if (SPEC_TESTS STREQUAL "ON")
    #    set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS " -fPIC  ")
    #endif()

    set(SQLDB_LIBS
        sqlite3
        #dl
    )
    set(SQLDB__SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/server/db/sqlite/sqlitedb.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/server/db/sqlite/sqlitedb.h
        )
endif()

# Encryption configuration
set(SSL_INCLUDE
       ${SPEC_SRC_COMMON}/encrypt/boringssl/include
       )

  add_library( crypto
                STATIC
                IMPORTED )
  add_library( decrepit
                STATIC
                IMPORTED )
  add_library( ssl
                STATIC
                IMPORTED )

  set(SSL_LIBS
                decrepit
                ssl
                crypto
            )

  if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        set_target_properties( # Specifies the target library.
            crypto
            PROPERTIES IMPORTED_LOCATION
            ${SPEC_LIB_DIR}/libcrypto.a )
        set_target_properties( # Specifies the target library.
            decrepit
            PROPERTIES IMPORTED_LOCATION
            ${SPEC_LIB_DIR}/libdecrepit.a )
        set_target_properties( # Specifies the target library.
            ssl
            PROPERTIES IMPORTED_LOCATION
            ${SPEC_LIB_DIR}/libssl.a )
  elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
        set_target_properties( # Specifies the target library.
            crypto
            PROPERTIES IMPORTED_LOCATION
            ${SPEC_LIB_DIR}/crypto.lib )
        set_target_properties( # Specifies the target library.
            decrepit
            PROPERTIES IMPORTED_LOCATION
            ${SPEC_LIB_DIR}/decrepit.lib )
        set_target_properties( # Specifies the target library.
            ssl
            PROPERTIES IMPORTED_LOCATION
            ${SPEC_LIB_DIR}/ssl.lib )
    endif()

# OS configuration
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
   message(STATUS "Linux was chosen ")
   set(OS_INCLUDE
       ${SPEC_SRC_COMMON}/system/linux
       )

   set(OS_SRC
     ${SPEC_SRC_COMMON}/system/linux/linuxsystem.cpp
     )

   set(OS_LIBS
             dl
            pthread
            stdc++fs
         )

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
   message(STATUS "Windows was chosen ")
   set(OS_INCLUDE
       ${SPEC_SRC_COMMON}/system/windows
       )

  set(OS_SRC
    ${SPEC_SRC_COMMON}/system/windows/windowssystem.cpp
    )

   set(OS_DEFINITIONS
    "WIN32_LEAN_AND_MEAN"
    FD_SETSIZE=1024
  )
endif()

