1. Download and install toolchain

$ curl -O http://ftp.loongnix.cn/toolchain/gcc/release/loongarch/gcc8/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.1.tar.xz

2. Build and install qemu

$ git clone -b v6.0.0 git@github.com:loongson/qemu.git 
$ cd qemu
$ mkdir build && cd build
$ ../configure --target-list=loongarch64-softmmu --enable-debug
$ make -j8
# You could add the ./build/qemu-system-loongarch64 to your PATH

3.