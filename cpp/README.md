C++
===

# Log4cxx

## LOG4CXX_<logger> macros

```bash
  $ vim $LOG4CXX/src/main/include/log4cxx/logger.h
```

For example, the macro `LOG4CXX_DEBUG`:

```C++
  /**
  Logs a message to a specified logger with the DEBUG level.

  @param logger the logger to be used.
  @param message the message string to log.
  */
  #define LOG4CXX_DEBUG(logger, message) { \
          if (LOG4CXX_UNLIKELY(logger->isDebugEnabled())) {\
             ::log4cxx::helpers::MessageBuffer oss_; \
             logger->forcedLog(::log4cxx::Level::getDebug(), oss_.str(oss_ << message), LOG4CXX_LOCATION); }}
```

`$LOG4CXX/src/main/include/log4cxx/helpers/messagebuffer.h`:

```C++  
  class LOG4CXX_EXPORT MessageBuffer {
    ...
    // => `LOG4CXX_DEBUG(logger, "e^10 = " << std::scientific << exp(10.0));`
    std::ostream& operator<<(...);
  }
```

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
     
     # **Hack**: Use `$APR_SOURCE` to get `rules.mk`
     $ ./configure --prefix="$(pwd)/../apr-util/1.4.1" --with-apr="$(pwd)/../apr-1.4.6"
     
     # Then, use `$APR_INSTALL` to get `libapr-1.la`
     $ ./configure --prefix="$(pwd)/../apr-util/1.4.1" --with-apr="$(pwd)/../apr/1.4.6" --with-expat=builtin
     $ make -j12
     $ make -j24 install
   ```

2. Apache Log4cxx

   *Note: must keep `APR` build trees because `apr-config` references it (due to above hack)*

   ```bash
     $ tar xzvf apache-log4cxx-0.10.0.tar.gz
     $ ./configure --with-apr="$APR_INSTALL" --with-apr-util=/path/to/apr-util/install
     $ make -j24
     $ make -j24 install
     
     $ ldd log4cxx/0.10.0/lib/liblog4cxx.so
	linux-vdso.so.1 =>  (0x00007fff003fd000)
	libaprutil-1.so.0 => /home/too1/local/opt/apache/apr-util-1.4.1/../apr-util/1.4.1/lib/libaprutil-1.so.0 (0x00002af489357000)
	libexpat.so.0 => /home/too1/local/opt/apache/apr-util-1.4.1/../apr-util/1.4.1/lib/libexpat.so.0 (0x00002af489578000)
	libapr-1.so.0 => /home/too1/local/opt/apache/apr-1.4.6/../apr/1.4.6/lib/libapr-1.so.0 (0x00002af48979a000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00002af4899f1000)
	librt.so.1 => /lib64/librt.so.1 (0x00002af489bf6000)
	libcrypt.so.1 => /lib64/libcrypt.so.1 (0x00002af489dff000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00002af48a037000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00002af48a253000)
	**libstdc++.so.6 => /usr/lib64/libstdc++.so.6 (0x00002af48a457000)**
	libm.so.6 => /lib64/libm.so.6 (0x00002af48a757000)
	libc.so.6 => /lib64/libc.so.6 (0x00002af48a9db000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00002af48ad32000)
	/lib64/ld-linux-x86-64.so.2 (0x00000034a9200000)
   ```
   
   ```bash
     $ mkdir workspace
     $ cd workspace
     $ vi test.cpp
     $ export LD_LIBRARY_PATH=$(pwd)/../log4cxx/0.10.0/lib:$LD_LIBRARY_PATH
     $ g++ hello.cpp -I../log4cxx/0.10.0/include -L../log4cxx/0.10.0/lib -llog4cxx
     $ ./a.out 
     0 [0x2b48c9dba6e0] FATAL MyApp null - Entering application.
     0 [0x2b48c9dba6e0] INFO MyApp null - Exiting application.
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

## Pre-processor Macros

#### Macro "Blocks"

[C multi-line macro: do/while(0) vs scope block](http://stackoverflow.com/questions/1067226/c-multi-line-macro-do-while0-vs-scope-block)

> Answer found in google's first hit: http://bytes.com/groups/c/219859-do-while-0-macro-substitutions

> Andrey Tarasevich:

> The whole idea of using 'do/while' version is to make a macro which will expand into a regular statement, not into a compound statement. This is done in order to make the use of function-style macros uniform with the use of ordinary functions in all contexts.

> Consider the following code sketch

> ```C++
if (<condition>)
  foo(a);
else
  bar(a);
```

> where 'foo' and 'bar' are ordinary functions. Now imagine that you'd like to replace function 'foo' with a macro of the above nature

> ```C++
if (<condition>)
  CALL_FUNCS(a);
else
 bar(a);
```

> Now, if your macro is defined in accordance with the second approach (just '{' and '}') the code will no longer compile, because the 'true' branch of 'i' is now represented by a compound statement. And when you put a ';' after this compound statement, you finished the whole 'if' statement, thus orphaning the 'else' branch (hence the compilation error).

> One way to correct this problem is to remember not to put ';' after macro "invocations"

> ```C++
if (<condition>)
  CALL_FUNCS(a)
else
  bar(a);
```

> This will compile and work as expected, but this is not uniform. The more elegant solution is to make sure that macro expand into a regular statement, not into a compound one. One way to achieve that is to define the macro as follows

> ```C++
#define CALL_FUNCS(x) \
do { \
  func1(x); \
  func2(x); \
  func3(x); \
} while (0)
```

> Now this code

> ```C++
if (<condition>)
  CALL_FUNCS(a);
else
  bar(a);
```

> will compile without any problems.

> However, note the small but important difference between my definition of 'CALL_FUNCS' and the first version in your message. I didn't put a ';' after '} while (0)'. Putting a ';' at the end of that definition would immediately defeat the entire point of using 'do/while' and make that macro pretty much equivalent to the compound-statement version.

> I don't know why the author of the code you quoted in your original message put this ';' after 'while (0)'. In this form both variants are equivalent. The whole idea behind using 'do/while' version is not to include this final ';' into the macro (for the reasons that I explained above).