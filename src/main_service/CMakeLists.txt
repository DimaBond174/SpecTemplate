# This is the source code of SpecNet project
#
#  Copyright (c) Dmitriy Bondarenko
#  feel free to contact me: specnet.messenger@gmail.com
#
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# ************** Config **************
# TODO Database module:
ocv_update(SRV_DB "DSQLiteDB" CACHE PATH "SRV Database module")
message("SRV_DB: ${SRV_DB}")

# Database module:
#set(SPEC_DB  DSQLiteDB)

# ************** Prepare **************
include(cmake/prepare.cmake)

# Default object in reverse usage order:
set(SRV_SRC
  ${SRV_SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/adminsocket.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/camsocket.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/specserv.cpp  
  ${SPEC_SRC_COMMON}/network/udt/udtclient.cpp
  ${SPEC_SRC_COMMON}/network/udt/UDTPacket.cpp
  ${SPEC_SRC_COMMON}/network/udt/udt_ipack_builder.cpp
  ${SPEC_SRC_COMMON}/config/json/configjson.cpp
  ${SPEC_SRC_COMMON}/file/fileadapter.cpp
  ${SPEC_SRC_COMMON}/tools/dson.cpp
  ${SPEC_SRC_COMMON}/tools/spec_os.cpp
  ${SPEC_SRC_COMMON}/network/network_base.cpp
  )

message("SRV_SRC: ${SRV_SRC}")
message("SRV_INCLUDE: ${SRV_INCLUDE}")
message("SRV_DEFINITIONS: ${SRV_DEFINITIONS}")
message("SRV_LINK_LIBS: ${SRV_LINK_LIBS}")
message("SRV_PROPERTIES: ${SRV_PROPERTIES}")

# **************   Build   **************
custom_add_executable(${Proj_SERVICE}
    "${SPEC_BUILD_DIR}"
    "${SRV_SRC}"
    "${SRV_INCLUDE}"
    "${SRV_DEFINITIONS}"
    "${SRV_LINK_LIBS}"
    "${SRV_PROPERTIES}")
