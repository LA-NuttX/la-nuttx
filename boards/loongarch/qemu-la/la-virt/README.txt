1. Download and install toolchain

$ curl -O http://ftp.loongnix.cn/toolchain/gcc/release/loongarch/gcc8/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.1.tar.xz

2. Build and install qemu

$ git clone -b v6.0.0 git@github.com:loongson/qemu.git 
$ cd qemu
$ mkdir build && cd build
$ ../configure --target-list=loongarch64-softmmu --enable-debug
$ make -j8
# You could add the ./build/qemu-system-loongarch64 to your PATH

3.1. Configure and build NuttX for BUILD_FLAT

  $ mkdir ./nuttx; cd ./nuttx
  $ git clone https://github.com/apache/nuttx.git nuttx
  $ git clone https://github.com/apache/nuttx-apps.git apps
  $ cd nuttx
  $ make distclean
  $ ./tools/configure.sh -l la-virt:nsh64
  $ make V=1 -j12

3.2. Configure and build NuttX for BUILD_KERNEL

  $ mkdir ./nuttx; cd ./nuttx
  $ git clone https://github.com/apache/nuttx.git nuttx
  $ git clone https://github.com/apache/nuttx-apps.git apps
  $ cd nuttx
  $ make distclean
  $ ./tools/configure.sh -l la-virt:knsh64 && make -j12 && make export V=1
  $ cd ../apps && ./tools/mkimport.sh -z -x ../nuttx/nuttx-export-*.tar.gz && make import V=1
  $ cd ../nuttx

4. Run the nuttx with qemu

  $ qemu-system-loongarch64 -machine virt -m 4G -cpu la464 -smp 1 -kernel ./nuttx --nographic

5. TODO
          NuttShell (NSH) NuttX-*
          nsh> mount -t hostfs -o fs=. /host
          nsh> cat /host/AUTHORS
          This is a list of all the contributors that have submitted ICLA, SGA
          If you are not on this list and believe you should be, please inform us.

          ICLA
          ====
          ...
          nsh>