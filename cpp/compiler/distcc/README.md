C++ > Compiler > distcc
=======================

```bash
$ time pump make -j -C src/
__________Using distcc-pump from /Users/too1/Development/opt/macports/install/bin
/Users/too1/Development/opt/macports/install/bin/pump: error: pump mode requested, but distcc hosts list does not contain any hosts with ',cpp' option

$ vim ~/.distcc/hosts
...

$ time pump make -j -C src/
__________Using distcc-pump from /Users/too1/Development/opt/macports/install/bin
distcc[27826] (dcc_get_protover_from_features) ERROR: pump mode (',cpp') requires compression (',lzo')
distcc[27826] (dcc_parse_options) ERROR: invalid host options: ,cpp
sweetpea/4,cpp
bigflax/4,cpp
lisianthus/4,cpp
campanula/4,cpp

distcc[27826] (dcc_show_hosts) CRITICAL! Failed to get host list
/Users/too1/Development/opt/macports/install/bin/pump: error: pump mode requested, but distcc hosts list does not contain any hosts with ',cpp' option
```

https://trac.macports.org/ticket/23754


> The problem is caused by the fact that the OS python2.5 (which is what distcc detects by default) is 32-bit only, and hence not compatible with 64-bit shared libraries.

> The enclosed patch adds python26 & python27 variants, which tell distcc to use the MacPorts python installs. These are built 64-bit and so work perfectly with the 64-bit shared libs.

> An alternative solution might be to use the OS X python2.6 install, which is built as a 64- and 32-bit binary, I'll leave that as an exercise for the reader.


```bash
#!/bin/bash

source /export/tmp.hudson-rose/opt/macports/setup.sh

export CCACHE_DIR=/export/tmp.hudson-rose/caches/ccache
ccache --max-size 10G
if [ -n "$(type distcc)" ]; then
    export CCACHE_PREFIX=distcc
    export DISTCC_POTENTIAL_HOSTS='localhost'
fi
```

> Hi Justin,
>
> I use both distcc and ccache. The ccache runs first (g++ points
> to /usr/lib/ccache/g++) and then distcc gets a chance (env. variable
> CCACHE_PREFIX=distcc).
>
> My biggest speedup is from ccache, especially when I choose to rebuild
> everything (like after a merge) by running "make clean && make".
> Unfortunately, ROSE's paradigm of #include "sage3basic.h" makes caching
> less than optimal -- if anyone changes any header file, then most files
> in the cache become out of date.
>
> I've got one machine that's significantly faster than the others, and I
> do most of my devel on that machine (wortheni), so
> DISTCC_HOSTS=localhost/12 there, and something like "localhost/4
> wortheni/12" everywhere else.  But a benefit (for me) of using distcc
> means I can always run "make -j" (i.e., no parallel limit) and distcc
> figures out how many compiles to run.
>
>
> $ cmake ..
>
> # disables ccache but not distcc
> $ CCACHE_DISABLE=yes make -j12 -C src (243 seconds)
>
> # warm up the cache
> # DISTCC_HOSTS is "localhost/12"
> $ make -C src clean
> $ ccache -C # clear entire cache
> $ make -j -C src (253 seconds)
>
> # simulate a recompile
> $ make -C src clean
> $ make -j -C src (66 seconds)
>
> Generating stringify.C takes 30-40 seconds in all three cases.
>
> --Robb

> The order of the hosts is extremely important. distcc is unable to determine
> which hosts are more powerful or under less load and simply distributes the
> compile jobs in order. For jobs that can't be run in parallel, such as
> configure tests, this means the first host in the list will bear the brunt of
> the compiling. If you have machines of varying power, it can make a large
> difference in compile time to put the most powerful machines first and the
> least powerful machine last on the list of hosts.

> Depending on the power of the computer running distcc, you may not want to
> include localhost in the list of hosts at all. Localhost has to do all of
> the preprocessing—a deliberate design choice that means you don't need to
> ensure that you have the same set of libraries and header files on each
> machine—and also all of the linking, which is often hugely processor-intensive
> on a large compile. There is also a certain small amount of processing
> overhead in managing shipping the files around the network to the other
> compilers. As a rule of thumb, the distcc documentation recommends that for
> three to four hosts, localhost probably should be placed last on the list,
> and for greater than five hosts, it should be excluded altogether. 

http://www.linuxjournal.com/article/9814

```bash
$ distccmon-text --help
usage: distccmon-text [DELAY]

Displays current compilation jobs in text form.

If delay is specified, repeatedly updates after that many (fractional)
seconds.  Otherwise, runs just once.
```


CMake:

`RT_LIB NOTFOUND` but linked with 

Follow these instructions for each of your compilation machines:

```bash
$ port install distcc
--->  Fetching archive for expat
--->  Fetching expat
--->  Attempting to fetch expat-2.1.0.tar.gz from http://downloads.sourceforge.net/project/expat/expat/2.1.0
--->  Verifying checksum(s) for expat
--->  Extracting expat
--->  Configuring expat
--->  Building expat
--->  Staging expat into destroot
--->  Installing expat @2.1.0_0
--->  Cleaning expat
--->  Deactivating expat @2.0.1_1
--->  Cleaning expat
--->  Activating expat @2.1.0_0
--->  Cleaning expat
--->  Computing dependencies for distcc
--->  Fetching archive for distcc
--->  Fetching distcc
--->  Attempting to fetch distcc-3.1.tar.bz2 from http://distcc.googlecode.com/files/
--->  Verifying checksum(s) for distcc
--->  Extracting distcc
--->  Applying patches to distcc
--->  Configuring distcc
--->  Building distcc
--->  Staging distcc into destroot
--->  Installing distcc @3.1_0
--->  Activating distcc @3.1_0
--->  Cleaning distcc
```

```bash
sealavender $ export DISTCC_POTENTIAL_HOSTS='localhost motomo-mlt'
```

```bash
sealavender $ mkdir -p ~/.distcc
sealavender $ cat >> ~/.distcc/hosts <<-EOF
localhost
motomo-mlt
EOF
```

> `localhost 192.168.80.100/6,lzo`

>  This option increases the jobs sent to 192.168.80.100 to six, and it enables use of lzo compression.

```bash
$ distccd --daemon --allow '128.15.212.1'
```


```bash
$ gcc test.cpp
Undefined symbols:
  "___gxx_personality_v0", referenced from:
  etc...
```

Solution: use the C++ compiler since your code is C++ (.cpp)
```bash
$ g++ test.cpp
```

```bash
sealavender $ time make -j4 -C src/
  LINK    testSharedRoseLib
[INFO] [../../../master/scripts/check_boost_linkage.sh] Boost is being linked from '/Users/too1/Development/opt/macports/install/lib/' in '.libs/testSharedRoseLib'
[INFO] Testing whether a simple program linked with ROSE can be run (a warning will be issued because the translator is being run without an input file):
i686-apple-darwin10-g++-4.2.1: no input files
distcc[21036] ERROR: compile (null) on localhost failed
[INFO] Success!

real36m50.515s
Users44m6.174s
sys4m53.284s
```

With warmed up cache:

```bash
$ time make -j24 -C src
...
[INFO] Success!

14m
```

```bash
$ ../../master/configure --prefix=${HOME}/Development/projects/rose/install/master CC="distcc gcc" CXX="distcc g++" --with-boost="/Users/$USER/Development/opt/macports/install" --with-gfortran="/Users/$USER/Development/opt/macports/install/bin/gfortran-mp-4.4" --with-alternate_backend_fortran_compiler=gfortran-mp-4.4 GFORTRAN_PATH="/Users/$USER/Development/opt/macports/install/bin/gfortran-mp-4.4"
```

CMake configure:

```bash
$ FC=/Users/too1/Development/opt/macports/install/bin/gfortran-mp-4.4 cmake ../../master/
-- The CXX compiler identification is GNU
-- The C compiler identification is GNU
-- Checking whether CXX compiler has -isysroot
-- Checking whether CXX compiler has -isysroot - yes
-- Checking whether CXX compiler supports OSX deployment target flag
-- Checking whether CXX compiler supports OSX deployment target flag - yes
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Checking whether C compiler has -isysroot
-- Checking whether C compiler has -isysroot - yes
-- Checking whether C compiler supports OSX deployment target flag
-- Checking whether C compiler supports OSX deployment target flag - yes
-- Check for working C compiler: /usr/bin/gcc
-- Check for working C compiler: /usr/bin/gcc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for ROSE source tree type
-- Check for ROSE source tree type - Git
-- Found Git: /Users/too1/Development/opt/macports/install/bin/git 
-- Detecting ROSE SCM version information (from Git)
-- The ROSE SCM version identifier is eb375d02355e61ecbd9a9cf26dbeb2db9322c676
-- The ROSE SCM version Unix timestamp is 1340365453
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:362 ] Boost not in cache
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:365 ] _boost_TEST_VERSIONS = 1.36.0;1.37;1.37.0;1.38.0;1.39.0;1.40.0;1.40.0;1.40;1.39.0;1.39;1.38.0;1.38;1.37.0;1.37;1.36.1;1.36.0;1.36
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:367 ] Boost_USE_MULTITHREADED = TRUE
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:369 ] Boost_USE_STATIC_LIBS = TRUE
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:428 ] Declared as CMake or Environmental Variables:
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:430 ]   BOOST_ROOT = 
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:432 ]   BOOST_INCLUDEDIR = 
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:434 ]   BOOST_LIBRARYDIR = 
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:436 ] _boost_TEST_VERSIONS = 1.36.0;1.37;1.37.0;1.38.0;1.39.0;1.40.0;1.40.0;1.40;1.39.0;1.39;1.38.0;1.38;1.37.0;1.37;1.36.1;1.36.0;1.36
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:485 ] Include debugging info:
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:487 ]   _boost_INCLUDE_SEARCH_DIRS = C:/boost/include;C:/boost;/boost/include;/boost;/sw/local/include
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:489 ]   _boost_PATH_SUFFIXES = boost-1_36_0;boost-1_37;boost-1_37_0;boost-1_38_0;boost-1_39_0;boost-1_40_0;boost-1_40_0;boost-1_40;boost-1_39_0;boost-1_39;boost-1_38_0;boost-1_38;boost-1_37_0;boost-1_37;boost-1_36_1;boost-1_36_0;boost-1_36
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:513 ] location of version.hpp: /Users/too1/Development/opt/macports/install/include/boost/version.hpp
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:532 ] version.hpp reveals boost 1.47.0
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:625 ] guessed _boost_COMPILER = -xgcc42
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:635 ] _boost_MULTITHREADED = -mt
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:652 ] _boost_STATIC_TAG = 
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:654 ] _boost_ABI_TAG = d
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:687 ] _boost_LIBRARIES_SEARCH_DIRS = /Users/too1/Development/opt/macports/install/include/lib;/Users/too1/Development/opt/macports/install/include/../lib;C:/boost/lib;C:/boost;/boost/boost_1_47_0/lib;/boost/boost_1_47/lib;/boost/lib;/boost;/sw/local/lib
-- [ /Users/too1/Development/projects/rose/master/cmake/modules/FindBoost.cmake:816 ] Boost_FOUND = TRUE
-- Boost version: 1.47.0
-- Found the following Boost libraries:
--   date_time
--   filesystem
--   program_options
--   regex
--   system
--   wave
--   thread
-- The Fortran compiler identification is GNU
-- Check for working Fortran compiler: /Users/too1/Development/opt/macports/install/bin/gfortran-mp-4.4
-- Check for working Fortran compiler: /Users/too1/Development/opt/macports/install/bin/gfortran-mp-4.4  -- works
-- Detecting Fortran compiler ABI info
-- Detecting Fortran compiler ABI info - done
-- Checking whether /Users/too1/Development/opt/macports/install/bin/gfortran-mp-4.4 supports Fortran 90
-- Checking whether /Users/too1/Development/opt/macports/install/bin/gfortran-mp-4.4 supports Fortran 90 -- yes
-- >>>>>>>>>>>>>>>>>>>>>>>>> Smaller generated files disabled
-- Check if the system is big endian
-- Searching 16 bit integer
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Check size of unsigned short
-- Check size of unsigned short - done
-- Using unsigned short
-- Check if the system is big endian - little endian
-- Looking for argz.h
-- Looking for argz.h - not found
-- Looking for argz_append
-- Looking for argz_append - not found
-- Looking for argz_create_sep
-- Looking for argz_create_sep - not found
-- Looking for argz_insert
-- Looking for argz_insert - not found
-- Looking for argz_next
-- Looking for argz_next - not found
-- Looking for argz_stringify
-- Looking for argz_stringify - not found
-- Looking for byteswap.h
-- Looking for byteswap.h - not found
-- Looking for closedir
-- Looking for closedir - found
-- Looking for ctype.h
-- Looking for ctype.h - found
-- Looking for c_asm.h
-- Looking for c_asm.h - not found
-- Looking for dlfcn.h
-- Looking for dlfcn.h - found
-- Looking for dladdr
-- Looking for dladdr - found
-- Looking for dlerror
-- Looking for dlerror - found
-- Looking for dl.h
-- Looking for dl.h - not found
-- Looking for vprintf
-- Looking for vprintf - found
-- Looking for _dyld_func_lookup
-- Looking for _dyld_func_lookup - not found
-- Looking for dirent.h
-- Looking for dirent.h - found
-- Looking for errno.h
-- Looking for errno.h - found
-- Looking for ffi.h
-- Looking for ffi.h - not found
-- Looking for getcwd
-- Looking for getcwd - found
-- Looking for gethrtime
-- Looking for gethrtime - not found
-- Looking for getpagesize
-- Looking for getpagesize - found
-- Looking for getwd
-- Looking for getwd - found
-- Looking for sys/time.h
-- Looking for sys/time.h - found
-- Looking for index
-- Looking for index - found
-- Looking for intrinsics.h
-- Looking for intrinsics.h - not found
-- Looking for inttypes.h
-- Looking for inttypes.h - found
-- Looking for C++ include aspell.h
-- Looking for C++ include aspell.h - not found
-- Looking for C++ include aspell/aspell.h
-- Looking for C++ include aspell/aspell.h - not found
-- Looking for include files HAVE_IO_H
-- Looking for include files HAVE_IO_H - not found.
-- Looking for include files HAVE_LIMITS_H
-- Looking for include files HAVE_LIMITS_H - found
-- Looking for include files HAVE_LOCALE_H
-- Looking for include files HAVE_LOCALE_H - found
-- Looking for include files HAVE_PROCESS_H
-- Looking for include files HAVE_PROCESS_H - not found.
-- Looking for include files HAVE_STDLIB_H
-- Looking for include files HAVE_STDLIB_H - found
-- Looking for include files HAVE_SYS_STAT_H
-- Looking for include files HAVE_SYS_STAT_H - found
-- Looking for include files HAVE_SYS_TIME_H
-- Looking for include files HAVE_SYS_TIME_H - found
-- Looking for include files HAVE_SYS_UTIME_H
-- Looking for include files HAVE_SYS_UTIME_H - not found.
-- Looking for include files HAVE_SYS_SOCKET_H
-- Looking for include files HAVE_SYS_SOCKET_H - found
-- Looking for include files HAVE_UNISTD_H
-- Looking for include files HAVE_UNISTD_H - found
-- Looking for include files HAVE_PTHREAD_H
-- Looking for include files HAVE_PTHREAD_H - found
-- Looking for include files HAVE_UTIME_H
-- Looking for include files HAVE_UTIME_H - found
-- Looking for include files HAVE_STRING_H
-- Looking for include files HAVE_STRING_H - found
-- Looking for include files HAVE_STRINGS_H
-- Looking for include files HAVE_STRINGS_H - found
-- Looking for include files HAVE_MACHINE_ENDIAN_H
-- Looking for include files HAVE_MACHINE_ENDIAN_H - found
-- Looking for mach_absolute_time
-- Looking for mach_absolute_time - found
-- Looking for include files HAVE_MACH_MACH_TIME_H
-- Looking for include files HAVE_MACH_MACH_TIME_H - found
-- Looking for include files HAVE_MACH_O_DYLD_H
-- Looking for include files HAVE_MACH_O_DYLD_H - found
-- Looking for include files HAVE_MEMORY_H
-- Looking for include files HAVE_MEMORY_H - found
-- Looking for mktime
-- Looking for mktime - found
-- Looking for mmap
-- Looking for mmap - found
-- Looking for open
-- Looking for open - found
-- Looking for chmod
-- Looking for chmod - found
-- Looking for close
-- Looking for close - found
-- Looking for dcgettext
-- Looking for dcgettext - not found
-- Looking for popen
-- Looking for popen - found
-- Looking for pclose
-- Looking for pclose - found
-- Looking for _open
-- Looking for _open - not found
-- Looking for _close
-- Looking for _close - not found
-- Looking for _popen
-- Looking for _popen - not found
-- Looking for _pclose
-- Looking for _pclose - not found
-- Looking for getpid
-- Looking for getpid - found
-- Looking for gettext
-- Looking for gettext - not found
-- Looking for _getpid
-- Looking for _getpid - not found
-- Looking for mkdir
-- Looking for mkdir - found
-- Looking for _mkdir
-- Looking for _mkdir - not found
-- Looking for putenv
-- Looking for putenv - found
-- Looking for mktemp
-- Looking for mktemp - found
-- Looking for mkstemp
-- Looking for mkstemp - found
-- Looking for fcntl
-- Looking for fcntl - found
-- Looking for strerror
-- Looking for strerror - found
-- Looking for stpcpy
-- Looking for stpcpy - found
-- Looking for strcasecmp
-- Looking for strcasecmp - found
-- Looking for strdup
-- Looking for strdup - found
-- Looking for strtoul
-- Looking for strtoul - found
-- Looking for alloca
-- Looking for alloca - not found
-- Looking for __fsetlocking
-- Looking for __fsetlocking - not found
-- Looking for mempcpy
-- Looking for mempcpy - not found
-- Looking for __argz_count
-- Looking for __argz_count - not found
-- Looking for __argz_next
-- Looking for __argz_next - not found
-- Looking for __argz_stringify
-- Looking for __argz_stringify - not found
-- Looking for setlocale
-- Looking for setlocale - found
-- Looking for tsearch
-- Looking for tsearch - found
-- Looking for getegid
-- Looking for getegid - found
-- Looking for getgid
-- Looking for getgid - found
-- Looking for getuid
-- Looking for getuid - found
-- Looking for wcslen
-- Looking for wcslen - found
-- Looking for mkfifo
-- Looking for mkfifo - found
-- Looking for alloca
-- Looking for alloca - not found.
-- Looking for asprintf
-- Looking for asprintf - found
-- Looking for wprintf
-- Looking for wprintf - not found.
-- Looking for snprintf
-- Looking for snprintf - found
-- Looking for printf
-- Looking for printf - found
-- Looking for pid_t
-- Looking for pid_t - not found.
-- Looking for intmax_t
-- Looking for intmax_t - not found.
-- Looking for uintmax_t
-- Looking for uintmax_t - not found.
-- Looking for LC_MESSAGES
-- Looking for LC_MESSAGES - found
-- Check size of intmax_t
-- Check size of intmax_t - done
-- Check size of long double
-- Check size of long double - done
-- Check size of long long
-- Check size of long long - done
-- Check size of wchar_t
-- Check size of wchar_t - done
-- Check size of wint_t
-- Check size of wint_t - failed
-- Looking for include files HAVE_NDIR_H
-- Looking for include files HAVE_NDIR_H - not found.
-- Looking for opendir
-- Looking for opendir - found
-- Looking for readdir
-- Looking for readdir - found
-- Looking for read_real_time
-- Looking for read_real_time - not found
-- Looking for shl_load
-- Looking for shl_load - not found
-- Looking for strcoll
-- Looking for strcoll - found
-- Looking for strcspn
-- Looking for strcspn - found
-- Looking for strftime
-- Looking for strftime - found
-- Looking for strlcat
-- Looking for strlcat - found
-- Looking for strlcpy
-- Looking for strlcpy - found
-- Looking for strspn
-- Looking for strspn - found
-- Looking for strstr
-- Looking for strstr - found
-- Looking for strtod
-- Looking for strtod - found
-- Looking for strtol
-- Looking for strtol - found
-- Looking for include files HAVE_SYS_DIR_H
-- Looking for include files HAVE_SYS_DIR_H - found
-- Looking for include files HAVE_SYS_DL_H
-- Looking for include files HAVE_SYS_DL_H - not found.
-- Looking for time_base_to_time
-- Looking for time_base_to_time - not found
-- Looking for clock_gettime
-- Looking for clock_gettime - not found
-- Looking for dl in dl
-- Looking for dl in dl - not found
-- Check size of char
-- Check size of char - done
-- Check size of double
-- Check size of double - done
-- Check size of float
-- Check size of float - done
-- Check size of long double
-- Check size of long double - done
-- Check size of long long
-- Check size of long long - done
-- Check size of void*
-- Check size of void* - done
-- Check size of short
-- Check size of short - done
-- Check size of int
-- Check size of int - done
-- Check size of long
-- Check size of long - done
-- Checking whether system has ANSI C header files
-- Looking for include files StandardHeadersExist
-- Looking for include files StandardHeadersExist - found
-- Performing Test memchrExists
-- Performing Test memchrExists - Success
-- Performing Test freeExists
-- Performing Test freeExists - Success
-- ANSI C header files - found
-- Looking for include files TIME_WITH_SYS_TIME
-- Looking for include files TIME_WITH_SYS_TIME - found
-- Check size of struct tm
-- Check size of struct tm - done
-- Performing Test HAVE_DECL_ISTREAMBUF_ITERATOR
-- Performing Test HAVE_DECL_ISTREAMBUF_ITERATOR - Success
-- Performing Test HAVE_ICONV_CONST
-- Performing Test HAVE_ICONV_CONST - Failed
-- Performing Test SIZEOF_WCHAR_T_IS_2
-- Performing Test SIZEOF_WCHAR_T_IS_2 - Failed
-- Performing Test SIZEOF_WCHAR_T_IS_4
-- Performing Test SIZEOF_WCHAR_T_IS_4 - Success
-- Performing Test HAVE_MYSQL_OPT_EMBEDDED_CONNECTION
-- Performing Test HAVE_MYSQL_OPT_EMBEDDED_CONNECTION - Failed
-- MySQL not found.
-- MySQL Embedded not found.
-- CMAKE_BINARY_DIR:         /Users/too1/Development/projects/rose/build/master-cmake
-- CMAKE_CURRENT_BINARY_DIR: /Users/too1/Development/projects/rose/build/master-cmake
-- CMAKE_SOURCE_DIR:         /Users/too1/Development/projects/rose/master
-- CMAKE_CURRENT_SOURCE_DIR: /Users/too1/Development/projects/rose/master
-- PROJECT_BINARY_DIR: /Users/too1/Development/projects/rose/build/master-cmake
-- PROJECT_SOURCE_DIR: /Users/too1/Development/projects/rose/master
-- EXECUTABLE_OUTPUT_PATH: 
-- LIBRARY_OUTPUT_PATH:     
-- CMAKE_MODULE_PATH: /Users/too1/Development/projects/rose/master/cmake/Users/too1/Development/projects/rose/master/cmake/modules
-- CMAKE_COMMAND: /Users/too1/Development/opt/macports/install/bin/cmake
-- CMAKE_ROOT: /Users/too1/Development/opt/macports/install/share/cmake-2.8
-- CMAKE_CURRENT_LIST_FILE: /Users/too1/Development/projects/rose/master/CMakeLists.txt
-- CMAKE_CURRENT_LIST_LINE: 363
-- CMAKE_INCLUDE_PATH: 
-- CMAKE_LIBRARY_PATH: 
-- CMAKE_SYSTEM: Darwin-10.8.0
-- CMAKE_SYSTEM_NAME: Darwin
-- CMAKE_SYSTEM_VERSION: 10.8.0
-- CMAKE_SYSTEM_PROCESSOR: i386
-- UNIX: 1
-- WIN32: 
-- APPLE: 1
-- MINGW: 
-- CYGWIN: 
-- BORLAND: 
-- MSVC: 
-- MSVC_IDE: 
-- MSVC60: 
-- MSVC70: 
-- MSVC71: 
-- MSVC80: 
-- CMAKE_COMPILER_2005: 
-- CMAKE_SKIP_RULE_DEPENDENCY: 
-- CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: 
-- CMAKE_SKIP_RPATH: NO
-- CMAKE_VERBOSE_MAKEFILE: FALSE
-- CMAKE_SUPPRESS_REGENERATION: 
-- CMAKE_C_FLAGS:  -fexceptions -DHAVE_CONFIG_H -g -fPIC -fvisibility=hidden
-- CMAKE_CXX_FLAGS:  -fexceptions -DHAVE_CONFIG_H -g -fPIC -fvisibility=hidden
-- CMAKE_BUILD_TYPE: 
-- BUILD_SHARED_LIBS: 
-- CMAKE_C_COMPILER: /usr/bin/gcc
-- CMAKE_CXX_COMPILER: /usr/bin/c++
-- CMAKE_COMPILER_IS_GNUCC: 1
-- CMAKE_COMPILER_IS_GNUCXX : 1
-- CMAKE_AR: /usr/bin/ar
-- CMAKE_RANLIB: /usr/bin/ranlib
-- Found OpenSSL: /usr/lib/libssl.dylib
-- checking for module 'sqlite3'
--   found sqlite3, version 3.7.8
StatusLooking for JAVA ...
-- Found Java: /usr/bin/java (found version "1.6.0.31")
StatusLooking for flex ...
-- Found Flex: /usr/bin/flex 2.5.35
StatusLooking for BISON ...
-- Found Bison: /Users/too1/Development/opt/macports/install/bin/bison
CMAKE_C_COMPILER= /usr/bin/gcc^
BACKEND_C_COMPILER_NAME_WITHOUT_PATH=gcc^
BACKEND_CXX_COMPILER= /usr/bin/c++
BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH= c++
Starting to run: /Users/too1/Development/projects/rose/master/config/create_system_headers c++ ./include-staging/c++_HEADERS /Users/too1/Development/projects/rose/master
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
compilerName   = c++
compilerBinDir = .
roseHome       = /Users/too1/Development/projects/rose/master
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Generating  /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/rose_edg_required_macros_and_functions.h
processing header file directory /usr/include/c++/4.2.1 to be mapped to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs1
/usr/include/c++/4.2.1 needs        5 change(s)
/usr/include/c++/4.2.1 needs to be copied and modified
Done copying
Processing complex header file (commenting out private constructor) at /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs1/./complex
Processing c++config header file (removing use of visibility attribute) at /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs1/./i686-apple-darwin10/bits/c++config.h
Processing c++config header file (removing use of visibility attribute) at /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs1/./powerpc-apple-darwin10/bits/c++config.h
Processing complex header file (commenting out private constructor) at /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs1/./tr1/complex
Processing c++config header file (removing use of visibility attribute) at /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs1/./x86_64-apple-darwin10/bits/c++config.h
processing header file directory /usr/include/c++/4.2.1/i686-apple-darwin10/x86_64 to be mapped to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs2
/usr/include/c++/4.2.1/i686-apple-darwin10/x86_64 needs        1 change(s)
/usr/include/c++/4.2.1/i686-apple-darwin10/x86_64 needs to be copied and modified
Done copying
Processing c++config header file (removing use of visibility attribute) at /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs2/./bits/c++config.h
processing header file directory /usr/include/c++/4.2.1/backward to be mapped to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs3
/usr/include/c++/4.2.1/backward needs        0 change(s)
/usr/include/c++/4.2.1/backward does not need any changes
processing header file directory /usr/lib/gcc/i686-apple-darwin10/4.2.1/include to be mapped to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs4
/usr/lib/gcc/i686-apple-darwin10/4.2.1/include needs        0 change(s)
/usr/lib/gcc/i686-apple-darwin10/4.2.1/include does not need any changes
Verified "/usr/include/sys/cdefs.h" exists ... (referenced by ROSE specific "sys/cdefs.h" header file)
system_headers_directory = /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs should be used instead of target_parent_dir = 
Copying /Users/too1/Development/projects/rose/master/config/rose_specific_cdefs.h to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/c++_HEADERS/hdrs/sys to fix __gconv_info incomplete definition problem ...
Starting to run: /Users/too1/Development/projects/rose/master/config/create_system_headers gcc ./include-staging/gcc_HEADERS /Users/too1/Development/projects/rose/master
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
compilerName   = gcc
compilerBinDir = .
roseHome       = /Users/too1/Development/projects/rose/master
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Generating  /Users/too1/Development/projects/rose/build/master-cmake/include-staging/gcc_HEADERS/rose_edg_required_macros_and_functions.h
processing header file directory /usr/lib/gcc/i686-apple-darwin10/4.2.1/include to be mapped to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/gcc_HEADERS/hdrs1
/usr/lib/gcc/i686-apple-darwin10/4.2.1/include needs        0 change(s)
/usr/lib/gcc/i686-apple-darwin10/4.2.1/include does not need any changes
Verified "/usr/include/sys/cdefs.h" exists ... (referenced by ROSE specific "sys/cdefs.h" header file)
system_headers_directory = /Users/too1/Development/projects/rose/build/master-cmake/include-staging/gcc_HEADERS/hdrs should be used instead of target_parent_dir = 
Copying /Users/too1/Development/projects/rose/master/config/rose_specific_cdefs.h to /Users/too1/Development/projects/rose/build/master-cmake/include-staging/gcc_HEADERS/hdrs/sys to fix __gconv_info incomplete definition problem ...
StatusRunning tests ...
StatusEnabling QT ...
-- META_EXE_LOC = /Users/too1/Development/projects/rose/build/master-cmake/src/ROSETTA/src/CxxGrammarMetaProgram
-- Smaller Generated Files Disabled
-- >>>>>>>>>>>>>>>>>>>>>> smallerGeneratedFiles : OFF
Commented out use of OpenAnalysis in Windows.
StatusFinished ...
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/too1/Development/projects/rose/build/master-cmake
```

```bash
$ time make -j2 -C src
Scanning dependencies of target generate_rosePublicConfig
Scanning dependencies of target ROSE_PREPROCESSOR
[  0%] Generating ../rosePublicConfig.h
[  0%] Generating lex.yy.C
/Users/too1/Development/projects/rose/master/src/frontend/SageIII/preproc-c.ll:773: warning, rule cannot be matched
/Users/too1/Development/projects/rose/master/src/frontend/SageIII/preproc-c.ll:800: warning, rule cannot be matched
[  1%] Built target generate_rosePublicConfig
Scanning dependencies of target OMPPARSER
[  1%] Generating ompparser.C
[  1%] Generating files for preprocessor
[  1%] Built target ROSE_PREPROCESSOR
[  1%] Generating omp-lex.yy.C
```

Monitor `distcc` build, refreshing every 5 seconds:

```bash
$ distccmon-text 5
 56348  Compile     hpdf_page_.tmp.sealavender.lln                localhost[0]
 56339  Compile     decl_spec.tmp.sealavender.llnl                localhost[1]
 56303  Compile     templates.tmp.sealavender.llnl               motomo-mlt[1]
 56364  Compile     hpdf_pages.tmp.sealavender.lln               motomo-mlt[2]

 56755  Compile     trans_corr.tmp.sealavender.lln                localhost[0]
 56739  Compile     symbol_tbl.tmp.sealavender.lln               motomo-mlt[1]
```

1. **Download** the [source tarball](https://code.google.com/p/distcc/)

   ```bash
   $ curl -O http://distcc.googlecode.com/files/distcc-3.2rc1.tar.gz
   ```

2. **Unpack** the source code

   ```bash
   $ tar -xzf distcc-3.2rc1.tar.gz
   # => DISTCC_SOURCE
   ```

3. **[Build and install](https://code.google.com/p/distcc/)**

   ``` bash
   # use a separate build tree to keep things clean
   $ mkdir build-distcc
   $ cd build-distcc

   # configure
   $ ${DISTCC_SOURCE}/configure --prefix=${HOME}/Development/opt/distcc/3.2rc1

   # build and install
   $ make
   $ make install
   ```

**Problem (OS X)**: `command 'gcc-4.2' failed`

```bash
gcc-4.2: -E, -S, -save-temps and -M options are not allowed with multiple -arch flags
error: command 'gcc-4.2' failed with exit status 1
make: *** [include-server] Error 1
```

## With ROSE

1. Create symbolic links from `distcc` to `gcc` and `g++`

    ```bash
    $ mkdir bin/
    $ ln -s ~/opt/distcc/3.2rc1/bin/distcc gcc
    $ ln -s ~/opt/distcc/3.2rc1/bin/distcc g++
    ```

2. Configure ROSE
3. Build ROSE

    ```bash
    $ /usr/bin/time pump make -j72
    ```

Run `top` on `distccd` server:

```bash
$ top
top - 09:13:19 up 28 days, 22:15,  1 user,  load average: 0.57, 0.27, 0.83
Tasks: 463 total,   2 running, 459 sleeping,   0 stopped,   2 zombie
Cpu(s):  0.0%us,  0.2%sy,  3.2%ni, 96.5%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:  24675800k total, 22975712k used,  1700088k free,  1282512k buffers
Swap: 26738680k total,      268k used, 26738412k free, 19764236k cached

  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND                                         
 7414 too1      30   5  406m 312m  27m R 80.0  1.3   0:02.41 cc1plus                                         
 3423 too1      20   5 19160  828  532 S  1.3  0.0   0:00.06 distccd                                         
 3447 too1      20   5 19160  828  532 S  0.3  0.0   0:00.03 distccd  
 ...
```


Run `distccmon-text` on client side (where compilation is running):

```bash
$ ~/opt/distcc/3.2rc1/bin/distccmon-text 1.5
 32486  Compile     fixupSelfReferentialMacros.C                  localhost[0]
 32432  Compile     markForOutputInCodeGeneration.                localhost[1]
 32498  Compile     fixupTypeReferences.C                         localhost[2]
 32478  Compile     astPostProcessing.C                           localhost[3]

 32486  Compile     fixupSelfReferentialMacros.C                  localhost[0]
 32478  Compile     astPostProcessing.C                           localhost[3]

 32478  Compile     astPostProcessing.C                           localhost[3]

 32478  Compile     astPostProcessing.C                           localhost[3]

 32478  Compile     astPostProcessing.C                           localhost[3]

 32478  Compile     astPostProcessing.C                           localhost[3]


   551  Preprocess                                                localhost[0]
   552  Preprocess                                                localhost[1]
   553  Preprocess                                                localhost[2]
   558  Preprocess                                                localhost[3]
   560  Preprocess                                                localhost[4]
   563  Preprocess                                                localhost[5]
   562  Preprocess                                                localhost[6]
   565  Preprocess                                                localhost[7]

   551  Preprocess                                                localhost[0]
   552  Preprocess                                                localhost[1]
   553  Preprocess                                                localhost[2]
   558  Preprocess                                                localhost[3]
   560  Preprocess                                                localhost[4]
   563  Preprocess                                                localhost[5]
   562  Preprocess                                                localhost[6]
   565  Preprocess                                                localhost[7]

   553  Compile     generateUniqueName.C                     hudson-rose-26[0]
   563  Compile     sageBuilder_fortran.C                    hudson-rose-26[1]
   551  Compile     sageBuilder.C                            hudson-rose-28[0]
   558  Compile     sageInterface_type.C                     hudson-rose-28[1]
   562  Compile     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Compile     sageInterface.C                          hudson-rose-29[0]
   560  Compile     abiStuff.C                               hudson-rose-29[1]
   565  Compile     sageBuilderAsm.C                         hudson-rose-29[2]
   566  Preprocess                                                localhost[2]

   553  Compile     generateUniqueName.C                     hudson-rose-26[0]
   563  Compile     sageBuilder_fortran.C                    hudson-rose-26[1]
   566  Compile     sageInterface_asm.C                      hudson-rose-26[2]
   551  Compile     sageBuilder.C                            hudson-rose-28[0]
   558  Compile     sageInterface_type.C                     hudson-rose-28[1]
   562  Compile     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Compile     sageInterface.C                          hudson-rose-29[0]
   560  Compile     abiStuff.C                               hudson-rose-29[1]
   565  Compile     sageBuilderAsm.C                         hudson-rose-29[2]

   566  Compile     sageInterface_asm.C                      hudson-rose-26[2]
   551  Compile     sageBuilder.C                            hudson-rose-28[0]
   558  Compile     sageInterface_type.C                     hudson-rose-28[1]
   562  Compile     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Compile     sageInterface.C                          hudson-rose-29[0]
   565  Compile     sageBuilderAsm.C                         hudson-rose-29[2]
   553  Compile     generateUniqueName.C                          localhost[0]
   560  Compile     abiStuff.C                                    localhost[1]
   563  Compile     sageBuilder_fortran.C                         localhost[2]

   566  Compile     sageInterface_asm.C                      hudson-rose-26[2]
   551  Receive     sageBuilder.C                            hudson-rose-28[0]
   558  Receive     sageInterface_type.C                     hudson-rose-28[1]
   562  Receive     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Compile     sageInterface.C                          hudson-rose-29[0]
   553  Compile     generateUniqueName.C                          localhost[0]
   560  Compile     abiStuff.C                                    localhost[1]
   563  Compile     sageBuilder_fortran.C                         localhost[2]
   565  Compile     sageBuilderAsm.C                              localhost[3]

   566  Receive     sageInterface_asm.C                      hudson-rose-26[2]
   551  Receive     sageBuilder.C                            hudson-rose-28[0]
   558  Receive     sageInterface_type.C                     hudson-rose-28[1]
   562  Receive     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Compile     sageInterface.C                          hudson-rose-29[0]
   553  Compile     generateUniqueName.C                          localhost[0]
   560  Compile     abiStuff.C                                    localhost[1]
   563  Compile     sageBuilder_fortran.C                         localhost[2]
   565  Compile     sageBuilderAsm.C                              localhost[3]

   566  Receive     sageInterface_asm.C                      hudson-rose-26[2]
   551  Receive     sageBuilder.C                            hudson-rose-28[0]
   558  Receive     sageInterface_type.C                     hudson-rose-28[1]
   562  Receive     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Compile     sageInterface.C                          hudson-rose-29[0]
   553  Compile     generateUniqueName.C                          localhost[0]
   560  Compile     abiStuff.C                                    localhost[1]
   563  Compile     sageBuilder_fortran.C                         localhost[2]
   565  Compile     sageBuilderAsm.C                              localhost[3]

   566  Receive     sageInterface_asm.C                      hudson-rose-26[2]
   551  Receive     sageBuilder.C                            hudson-rose-28[0]
   558  Receive     sageInterface_type.C                     hudson-rose-28[1]
   562  Receive     sageInterfaceAsm.C                       hudson-rose-28[2]
   552  Receive     sageInterface.C                          hudson-rose-29[0]
   ...
```
