# Usage:
# cmake -DCMAKE_TOOLCHAIN_FILE=./user_cross_compile_setup.cmake -B build -S .
# make  -C build -j

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(TOOLCHAIN_DIR /home/jkl/openwrts/rjcommunity/MT798X-6.6-24.10-workflow/staging_dir/toolchain-aarch64_cortex-a53_gcc-13.3.0_musl)
set(TARGET_DIR    /home/jkl/openwrts/rjcommunity/MT798X-6.6-24.10-workflow/staging_dir/target-aarch64_cortex-a53_musl)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-openwrt-linux-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-openwrt-linux-g++)

set(CMAKE_SYSROOT ${TARGET_DIR})
set(CMAKE_FIND_ROOT_PATH
    ${TOOLCHAIN_DIR}
    ${TARGET_DIR}
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(ENV{PKG_CONFIG_SYSROOT_DIR} ${TARGET_DIR})
set(ENV{PKG_CONFIG_PATH}
    "${TARGET_DIR}/usr/lib/pkgconfig:${TARGET_DIR}/usr/share/pkgconfig"
)

# If necessary, set STAGING_DIR
# if not work, please try(in shell command): export STAGING_DIR=/home/ubuntu/Your_SDK/out/xxx/openwrt/staging_dir/target
set(ENV{STAGING_DIR} ${TARGET_DIR})
