# This is the source code of SpecNet project
#
#  Copyright (c) Dmitriy Bondarenko
#  feel free to contact me: specnet.messenger@gmail.com


# Coping assets (TODO any change&rerun CMake to copy):
FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
FILE(GLOB_RECURSE SpecAssets
    ${CMAKE_CURRENT_SOURCE_DIR}/test_assets/*.*
    ${CMAKE_CURRENT_SOURCE_DIR}/test_assets/*
)

FOREACH(file ${SpecAssets})
    FILE(RELATIVE_PATH
        ITEM_PATH_REL
        ${CMAKE_CURRENT_SOURCE_DIR}/test_assets
        ${file}
    )
    GET_FILENAME_COMPONENT(dirname ${ITEM_PATH_REL} DIRECTORY)
#    message("File: ${ITEM_PATH_REL}")
#    message("Relative path: ${dirname}")
    FILE(MAKE_DIRECTORY ${SPEC_BUILD_DIR}/test_assets/${dirname})
#    GET_FILENAME_COMPONENT(filename ${file} NAME)
    FILE(COPY ${file} DESTINATION ${SPEC_BUILD_DIR}/test_assets/${dirname})
ENDFOREACH()

# Coping custom libs:
#FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs)
#FILE(GLOB SpecLibs "libs/*.*")
#FOREACH(file ${SpecLibs})
#    GET_FILENAME_COMPONENT(filename ${file} NAME)
#    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/${filename} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs)
#ENDFOREACH()




