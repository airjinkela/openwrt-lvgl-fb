cmake_minimum_required(VERSION 3.5)

project(cJSON
    VERSION 1.7.19
    LANGUAGES C)

cmake_policy(SET CMP0054 NEW)  # set CMP0054 policy

set(CJSON_LIB cjson)

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.c)
set(INCLUDES .)
# set(CJSON_LIBRARY_TYPE SHARED)

set(CJSON_LIBRARY_TYPE STATIC)

add_library(${CJSON_LIB} ${CJSON_LIBRARY_TYPE} ${HEADERS} ${SOURCES})
target_include_directories(${CJSON_LIB} PUBLIC ${INCLUDES})
