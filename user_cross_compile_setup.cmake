# Usage:
# cmake -DCMAKE_TOOLCHAIN_FILE=./user_cross_compile_setup.cmake -B build -S .
# make  -C build -j

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools /home/jkl/openwrts/rjcommunity/MT798X-6.6-24.10-workflow/staging_dir/toolchain-aarch64_cortex-a53_gcc-13.3.0_musl)
set(CMAKE_C_COMPILER ${tools}/bin/aarch64-openwrt-linux-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/aarch64-openwrt-linux-g++)

# If necessary, set STAGING_DIR
# if not work, please try(in shell command): export STAGING_DIR=/home/ubuntu/Your_SDK/out/xxx/openwrt/staging_dir/target
set(ENV{STAGING_DIR} "/home/jkl/openwrts/rjcommunity/MT798X-6.6-24.10-workflow/staging_dir/target-aarch64_cortex-a53_musl")

