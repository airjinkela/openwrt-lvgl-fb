cmake_minimum_required(VERSION 3.10)
project(mtkspitft)

# Set policy to allow to run the target_link_libraries cmd on targets that are build
# in another directory.
# Currently, the linking is not handled by env_support/cmake/os.cmake
# This means that if a driver is enabled and it requires linking an external library
# it needs to be handled in the top-level project.

cmake_policy(SET CMP0079 NEW)

# Uncomment if the program needs debugging
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 99) # LVGL officially supports C99 and above
set(CMAKE_CXX_STANDARD 17) #C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

set(LIBDIR src/lib)
set(PRJ_MAIN "main" CACHE STRING "Name of the main executable target")

set(LV_BUILD_SET_CONFIG_OPTS ON CACHE BOOL
    "create CMAKE variables from lv_conf_internal.h" FORCE)

add_subdirectory(${LIBDIR}/lvgl)
add_subdirectory(${LIBDIR}/cJSON)
add_subdirectory(${LIBDIR}/mtk-userspace-spi) # 这个没用了 可以删掉


if (CONFIG_LV_USE_FREETYPE)
    message("Including Freetype support")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBFREETYPE REQUIRED freetype2)

    list(APPEND PKG_CONFIG_LIB ${LIBFREETYPE_LIBRARIES})
    list(APPEND PKG_CONFIG_INC ${LIBFREETYPE_INCLUDE_DIRS})
endif()

if (CONFIG_LV_USE_SDL OR CONFIG_LV_USE_DRAW_SDL)

    message("Including SDL2 support")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

    list(APPEND PKG_CONFIG_LIB ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
    list(APPEND PKG_CONFIG_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
endif()

if (CONFIG_LV_USE_FFMPEG)
    message("Including ffmpeg support")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBVAUTIL REQUIRED libavutil)
    pkg_check_modules(LIBVAFORMAT REQUIRED libavformat)
    pkg_check_modules(LIBVAFILTER REQUIRED libavfilter)
    pkg_check_modules(LIBVADEVICE REQUIRED libavdevice)
    pkg_check_modules(LIBVACODEC REQUIRED libavcodec)
    pkg_check_modules(LIBSWSCALE REQUIRED libswscale)
    
    list(APPEND PKG_CONFIG_LIB ${LIBVAUTIL_LIBRARIES}
                                ${LIBVAFORMAT_LIBRARIES}
                                ${LIBVAFILTER_LIBRARIES}
                                ${LIBVADEVICE_LIBRARIES}
                                ${LIBVACODEC_LIBRARIES}
                                ${LIBSWSCALE_LIBRARIES}
                                )
    list(APPEND PKG_CONFIG_INC ${LIBVAUTIL_INCLUDE_DIRS}
                                ${LIBVAFORMAT_INCLUDE_DIRS}
                                ${LIBVAFILTER_INCLUDE_DIRS}
                                ${LIBVADEVICE_INCLUDE_DIRS}
                                ${LIBVACODEC_INCLUDE_DIRS}
                                ${LIBSWSCALE_INCLUDE_DIRS}
                                )
endif()

target_include_directories(lvgl PUBLIC ${PKG_CONFIG_INC})
target_link_libraries(lvgl PUBLIC
                          ${PKG_CONFIG_LIB}
                          m
                          pthread)

add_executable(${PRJ_MAIN} ${PROJECT_SOURCE_DIR}/src/main.c)
target_link_libraries(${PRJ_MAIN}
                              lvgl
                              mtkspi
                              cjson)
