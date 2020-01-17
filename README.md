# C library for accessing [Request Tracker's REST 1.0](https://rt-wiki.bestpractical.com/wiki/REST) interface

# Building

## Getting and preparing for configuration

```sh
$ git clone git://darapsa.org/librtclient.git
$ cd librtclient
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
$ CC=/usr/local/aarch64-linux-android/bin/aarch64-linux-android-clang ./configure --host=aarch64-linux-android
```

or

```sh
$ CC=/usr/local/arm-linux-androideabi/bin/arm-linux-androideabi-clang ./configure --host=arm-linux-androideabi
```

or so on.

## Compiling and linking

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
```
