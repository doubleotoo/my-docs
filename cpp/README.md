C++
===

# Log4cxx

## Log4j.properties

```
log4j.rootLogger=debug, stdout, R

log4j.appender.stdout=org.apache.log4j.ConsoleAppender
log4j.appender.stdout.layout=org.apache.log4j.PatternLayout

# Pattern to output the caller's file name and line number.
log4j.appender.stdout.layout.ConversionPattern=%5p [%t] (%F:%L) - %m%n

log4j.appender.R=org.apache.log4j.RollingFileAppender
log4j.appender.R.File=example.log

log4j.appender.R.MaxFileSize=100KB
# Keep one backup file
log4j.appender.R.MaxBackupIndex=1

log4j.appender.R.layout=org.apache.log4j.PatternLayout
# Print the date in ISO 8601 format
log4j.appender.R.layout.ConversionPattern=%d %p %t %c - %m%n
```

http://logging.apache.org/log4cxx/

# Installation

## Building Apache Log4cxx with Autotools

1. APR: Apache Portable Runtime Library (http://apr.apache.org/)

   ```bash
     $ wget http://www.gtlib.gatech.edu/pub/apache//apr/apr-1.4.6.tar.gz
     $ tar xvzf apr-1.4.6.tar.gz
     $ ./configure --prefix="$(pwd)/../apr/1.4.6"
     $ make -j12
   ```
   
   **apr-util**
   ```bash
     $ wget http://www.gtlib.gatech.edu/pub/apache//apr/apr-util-1.4.1.tar.gz
     $ tar xzvf apr-util-1.4.1.tar.gz
     
     # Hack: Use `$APR_SOURCE` to get `rules.mk`
     $ ./configure --prefix="$(pwd)/../apr-util/1.4.1" --with-apr="$(pwd)/../apr-1.4.6"
     
     # Then, use `$APR_INSTALL` to get `libapr-1.la`
     $ ./configure --prefix="$(pwd)/../apr-util/1.4.1" --with-apr="$(pwd)/../apr/1.4.6"
     $ make -j12
     $ make -j24 install
   ```

2. Apache Log4cxx

   ```bash
     $ tar xzvf apache-log4cxx-0.10.0.tar.gz
     $ ./configure --with-apr="$APR_INSTALL" --with-apr-util=/path/to/apr-util/install
     $ make -j24
     $ make -j24 install
   ```

**Error**: memmove was not declared in this scope https://issues.apache.org/jira/browse/LOGCXX-360

**Solution**: add `#include <string.h>`

  `socketoutputstream.cpp:52:54: error: 'memcpy' was not declared in this scope`
  + `#include <string.h>`

  `console.cpp`
  + `#include <string.h>`
  + `#include <stdio.h>`

#### `GLIBCXX_3.4.11' not found

The problem is that `./core` is linked with the wrong version of `libstdc++.so` in `/usr/lib64`
instead of the one in `/nfs/apps/gcc/4.4.1/lib64`.

```bash
./core: /usr/lib64/libstdc++.so.6: version `GLIBCXX_3.4.11' not found (required by /home/too1/local/opt/apache/log4cxx/apache-log4cxx-0.10.0/../0.10.0/lib/liblog4cxx.so.10)
./core: /usr/lib64/libstdc++.so.6: version `GLIBCXX_3.4.9' not found (required by /home/too1/local/opt/apache/log4cxx/apache-log4cxx-0.10.0/../0.10.0/lib/liblog4cxx.so.10)
```

```bash
$ ldd core
 linux-vdso.so.1 =>  (0x00007fffac3fd000)
 liblog4cxx.so.10 => /home/too1/local/opt/apache/log4cxx/apache-log4cxx-0.10.0/../0.10.0/lib/liblog4cxx.so.10 (0x00002b5aa12cb000)
	libaprutil-1.so.0 => /home/too1/local/opt/apache/log4cxx/apr-util/install/lib/libaprutil-1.so.0 (0x00002b5aa16b0000)
	libexpat.so.0 => /lib64/libexpat.so.0 (0x00000034ac200000)
	libapr-1.so.0 => /home/too1/local/opt/apache/log4cxx/apr/install/lib/libapr-1.so.0 (0x00002b5aa18fb000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00000034af600000)
	librt.so.1 => /lib64/librt.so.1 (0x00000034ade00000)
	libcrypt.so.1 => /lib64/libcrypt.so.1 (0x00000034bc400000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00000034aa600000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00000034a9e00000)
	**libstdc++.so.6 => /nfs/apps/gcc/4.4.1/lib/../lib64/libstdc++.so.6 (0x00002b5aa1b29000)**
	libm.so.6 => /lib64/libm.so.6 (0x00000034a9a00000)
	libgcc_s.so.1 => /nfs/apps/gcc/4.4.1/lib/../lib64/libgcc_s.so.1 (0x00002b5aa1e34000)
	libc.so.6 => /lib64/libc.so.6 (0x00000034a9600000)
	/lib64/ld-linux-x86-64.so.2 (0x00000034a9200000)
```

Check `-rpath` link commands in the actual `g++` link command:

```bash
  $ libtool --debug core...
  <get g++ link command at the end of the output>
  <check that -rpath /nfs/apps/... comes before -rpath /usr/lib64
```

## Building Apache Log4cxx with Apache ant
http://logging.apache.org/log4cxx/building/ant.html

**Error**:
/usr/lib/libexpat.so: could not read symbols: File in wrong format
**Solution**:
 `$ $APR_UTIL/configure --with-expat=builtin`

1. Install cpptasks

```bash
 $ wget http://sourceforge.net/projects/ant-contrib/files/ant-contrib/cpptasks-1.0-beta5/cpptasks-1.0b5.tar.gz/download
 $ tar xzvf cpptask-1.0b5.tar.gz
 $ cd cpptasks-1.0b5
 $ ant
 $ export CLASSPATH=~/cpptasks/cpptasks-1.0b5.jar
```

2. Download apr[-utils]

``bash
 $ tar -xvzf apr-1.2.12.tar.gz
 $ mv apr-1.2.12 apr
 $ tar -xvzf apr-util-1.2.12.tar.gz
 $ mv apr-util-1.2.12 apr-util

3. Install Apache Log4cxx

``bash
 $ cd apache-log4cxx-0.10.0
 $ ant
``

#### Errors
**\#memmove is not defined, nor is there a substitute**
```bash
  [exec] checking for memmove... yes
  [exec] checking for bcopy... yes
```