C++
===

# GCC Compiler

## Install

http://gcc.gnu.org/wiki/FAQ#configure

`[$GCC/contrib/download_prerequisites](http://c-cpp.r3dcode.com/download/gcc/4/6.2/contrib/download_prerequisites)`

https://gist.github.com/2927038

```bash
#!/bin/bash
source /nfs/apps/gmp/latest/setup.sh
source /nfs/apps/mpc/latest/setup.sh
source /nfs/apps/mpfr/latest/setup.sh
./configure --prefix="${HOME}/opt/gcc/4.6.1 --enable-languages=c,c++,fortran --with-gmp=/nfs/apps/gmp/4.3.2/ --with-mpfr=/nfs/apps/mpfr/3.0.0/ --with-mpc=/nfs/apps/mpc/0.8.2/
make -j16
make -j16 install
```

# Debugging

## Valgrind

```bash
$ valgrind --tool=memcheck <program_name>
```

## GDB

```
(gdb) set print pretty on
```

```bash
$ gdb identityTranslator
(gdb) run -d /export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/build/jorphan -classpath /export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/build/jorphan:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/activation-1.1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/bsf-2.4.0.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/bsf-api-3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/bsh-2.0b5.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/avalon-framework-4.1.4.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xmlgraphics-commons-1.3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-codec-1.6.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-collections-3.2.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-httpclient-3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-io-2.2.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-jexl-1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-jexl-2.1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-lang3-3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-logging-1.1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/commons-net-3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/excalibur-datasource-1.1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/excalibur-instrument-1.0.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/excalibur-logger-1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/excalibur-pool-1.2.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/htmllexer-2.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/htmlparser-2.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/httpclient-4.2.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/httpmime-4.2.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/httpcore-4.2.2.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/oro-2.0.8.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/mail-1.4.4.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/jcharts-0.7.5.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/jdom-1.1.2.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/geronimo-jms_1.1_spec-1.1.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/rhino-1.7R3.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/junit-4.10.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/logkit-2.0.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/serializer-2.7.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/soap-2.3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/jtidy-r938.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xalan-2.7.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xercesImpl-2.9.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xml-apis-1.3.04.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xpp3_min-1.1.4c.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xstream-1.4.2.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/xmlpull-1.1.3.1.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/api/bcmail-jdk15-1.45.jar:/export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/lib/api/bcprov-jdk15-1.45.jar -sourcepath /export/tmp.too1/workspace/rose/java/workspace/rose-builder/rose_workspace/jmeter/apache-jmeter-2.8/src/jorphan -target 1.5 -encoding UTF-8 -g -O -source 1.5 @/tmp/files6571348486763470261

(gdb) bt
#0  0x000000338aa30285 in raise () from /lib64/libc.so.6
#1  0x000000338aa31d30 in abort () from /lib64/libc.so.6
#2  0x00002aaaaf6783c4 in __gnu_cxx::__verbose_terminate_handler ()
    at ../../../../gcc-4.2.4/libstdc++-v3/libsupc++/vterminate.cc:98
#3  0x00002aaaaf676386 in __cxxabiv1::__terminate (handler=0x3641)
    at ../../../../gcc-4.2.4/libstdc++-v3/libsupc++/eh_terminate.cc:43
#4  0x00002aaaaf6763b3 in std::terminate ()
    at ../../../../gcc-4.2.4/libstdc++-v3/libsupc++/eh_terminate.cc:53
#5  0x00002aaaaf67649a in __cxxabiv1::__cxa_throw (obj=<value optimized out>, tinfo=<value optimized out>, 
    dest=<value optimized out>) at ../../../../gcc-4.2.4/libstdc++-v3/libsupc++/eh_throw.cc:76
#6  0x00002aaaac15d8c2 in boost::throw_exception<boost::filesystem2::basic_filesystem_error<boost::filesystem2::basic_path<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, boost::filesystem2::path_traits> > > (e=...) at /home/too1/local/opt/boost/1_45_0/include/boost/throw_exception.hpp:61
#7  0x00002aaaac15d9d2 in boost::filesystem2::exists<boost::filesystem2::basic_path<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, boost::filesystem2::path_traits> > (ph=...)
    at /home/too1/local/opt/boost/1_45_0/include/boost/filesystem/v2/operations.hpp:295
#8  0x00002aaaac15da69 in boost::filesystem2::exists (ph=...)
    at /home/too1/local/opt/boost/1_45_0/include/boost/filesystem/v2/operations.hpp:637
#9  0x00002aaaac31fb0d in CommandlineProcessing::isValidFileWithExecutableFileSuffixes (name=...)
    at ../../../../ROSE/src/frontend/SageIII/sage_support/cmdline.cpp:196
#10 0x00002aaaac31fcea in CommandlineProcessing::isExecutableFilename (name=...)
    at ../../../../ROSE/src/frontend/SageIII/sage_support/cmdline.cpp:133
#11 0x00002aaaac32011a in CommandlineProcessing::generateSourceFilenames (argList=..., binaryMode=false)
    at ../../../../ROSE/src/frontend/SageIII/sage_support/cmdline.cpp:391
#12 0x00002aaaac322b5f in SgProject::processCommandLine (this=0x2aaab4aba010, input_argv=...)
    at ../../../../ROSE/src/frontend/SageIII/sage_support/cmdline.cpp:933
#13 0x00002aaaac2fd390 in SgProject::parse (this=0x2aaab4aba010, argv=...)
    at ../../../../ROSE/src/frontend/SageIII/sage_support/sage_support.cpp:1270
#14 0x00002aaaac4b9908 in SgProject::SgProject (this=0x2aaab4aba010, argv=..., 
    frontendConstantFolding=false) at Cxx_Grammar.C:20562
#15 0x00002aaaae14de5c in frontend (argv=..., frontendConstantFolding=false)
    at ../../../ROSE/src/roseSupport/utility_functions.C:159
#16 0x00002aaaae14e4c2 in frontend (argc=16, argv=0x7fffffffc648, frontendConstantFolding=false)
    at ../../../ROSE/src/roseSupport/utility_functions.C:136
#17 0x00000000004040be in main (argc=16, argv=0x7fffffffc648)
    at ../../../../ROSE/exampleTranslators/documentedExamples/simpleTranslatorExamples/identityTranslator.C:

(gdb) break ../../../../ROSE/src/frontend/SageIII/sage_support/cmdline.cpp:933
```


# Logging

## Log4cxx

http://logging.apache.org/log4cxx/

### LOG4CXX_<logger> macros

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

### NDC: Nested Diagnostic Contexts `%x`

http://logging.apache.org/log4cxx/apidocs/classlog4cxx_1_1_n_d_c.html

"Pattern Languages of Program Design 3" by Robert C. Martin
http://www.amazon.com/Pattern-Languages-Program-Design-v/dp/0201310112

> a nested diagnostic context, or ndc in short, is an instrument to distinguish interleaved
> log output from different sources. log output is typically interleaved when a server handles
> multiple clients near-simultaneously.

`${LOG4CXX}/src/main/include/log4cxx/ndc.h`:

> ```C++
  /**
   Creates a nested diagnostic context.
   Since java performs no automatic cleanup of objects when a
   scope is left, in log4j push() and pop() must be used
   to manage the NDC. For convenience, log4cxx provides∞
   an NDC constructor and destructor which simply call the push() and
   pop() methods, allowing for automatic cleanup when the current
   scope ends.

>    @param message The new diagnostic context information.
   @see The #push method.
   */
  NDC(const std::string& message);
  
>   ...
  static LogString pop();
  static void push(const std::string& message);
```


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

#### Macro that expands to Macro (not possible!)

http://stackoverflow.com/questions/1135822/escaping-a-symbol-in-a-define-macro

> It is possible to insert a hash token into the preprocessed token stream. You can do it as follows:

> ```C++
#define MACRO(hash, name) hash include name
MACRO(#,"hello")
```

> expands to:

> ```C++
# include "hello"
```

> However, the standard explicitly rules out any further analysis of such line for the existence of preprocessing directives [cpp.rescan]:

> > The resulting completely macro-replaced preprocessing token sequence is not processed as a preprocessing directive even if it resembles one.

## Current function name

* C99 predefined identifier `__func__`.
* [BOOST_CURRENT_FUNCTION](http://www.boost.org/doc/libs/1_49_0/libs/utility/current_function.html)

## File and Line number

http://www.cplusplus.com/doc/tutorial/preprocessor/

# Windows (MSVC)

### Disable warnings

```C++
  #if defined(_MSC_VER)
  #pragma warning ( push )
  #pragma warning ( disable: 4231 4251 4275 4786 )
  #endif
```

## 

Problem:

```bash
/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cxxabi.h:45: error: expected declaration before end of line
```

[-fvisibility=default|internal|hidden|protected](http://gcc.gnu.org/onlinedocs/gcc-4.4.6/gcc/Code-Gen-Options.html)

> Removing the pragma there and on line 45 lets the compiler go on.




