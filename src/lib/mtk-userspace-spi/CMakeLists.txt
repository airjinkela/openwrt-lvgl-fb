cmake_minimum_required(VERSION 3.10)

project(mtkspi
    VERSION 0.0.1
    LANGUAGES C)

cmake_policy(SET CMP0054 NEW)

file(GLOB LIB_MTK_SPI_SOURCES *.c)
file(GLOB LIB_MTK_SPI_HEADERS *.h)
set(LIB_MTK_SPI_INCLUDES .)


add_library(mtkspi STATIC ${LIB_MTK_SPI_HEADERS} 
                          ${LIB_MTK_SPI_SOURCES})

target_include_directories(mtkspi PUBLIC
                                   ${LIB_MTK_SPI_INCLUDES})
