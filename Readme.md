## Prepare
```BASH
git submodule update --init --recursive                        
```

## Host Build

```BASH
cmake -B build -S .
make -C build -j
```

## Corss Build
```BASH
export STAGING_DIR=...../staging_dir/target-xxxx
cmake -DCMAKE_TOOLCHAIN_FILE=./user_cross_compile_setup.cmake -B build -S .
make -C build -j
```
