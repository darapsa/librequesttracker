# C library for accessing [Request Tracker's REST 1.0](https://rt-wiki.bestpractical.com/wiki/REST) interface

# Building

## Getting and preparing for configuration

```sh
$ git clone git://darapsa.org/librtclient.git
$ cd librtclient
$ libtoolize
$ autoreconf --install
```

## Optionally setting environment values

```sh
$ export CFLAGS="${CFLAGS} -g -DDEBUG -DANDROID -fPIC" # PIC might be needed later on android_armv7
$ export LDFLAGS="${LDFLAGS} -llog" # Android liblog
```

## Configuring for various target hosts

```sh
$ ./configure
```

or

```sh
$ CC=/usr/local/aarch64-linux-android/bin/aarch64-linux-android-clang RANLIB=/usr/local/aarch64-linux-android/bin/aarch64-linux-android-ranlib ./configure --host=aarch64-linux-android --prefix=/usr/local/aarch64-linux-android/sysroot/usr
```

or

```sh
$ CC=/usr/local/arm-linux-androideabi/bin/arm-linux-androideabi-clang RANLIB=/usr/local/arm-linux-androideabi/bin/arm-linux-androideabi-ranlib ./configure --host=arm-linux-androideabi --prefix=/usr/local/arm-linux-androideabi/sysroot/usr
```

or

```sh
$ CC=/usr/local/i686-linux-androideabi/bin/i686-linux-androideabi-clang RANLIB=/usr/local/i686-linux-androideabi/bin/i686-linux-androideabi-ranlib ./configure --host=i686-linux-androideabi --prefix=/usr/local/i686-linux-androideabi/sysroot/usr
```

or

```sh
$ CC=/usr/local/x86_64-linux-androideabi/bin/x86_64-linux-androideabi-clang RANLIB=/usr/local/x86_64-linux-androideabi/bin/x86_64-linux-androideabi-ranlib ./configure --host=x86_64-linux-androideabi --prefix=/usr/local/x86_64-linux-androideabi/sysroot/usr
```

or so on.

## Compiling, linking, and installing

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
$ sudo make install
```
