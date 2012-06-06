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

```bash
 $ ./configure --with-apr=/path/to/apr/install --with-apri-util=/path/to/apr-util/install
```

**Error**: memmove was not declared in this scope https://issues.apache.org/jira/browse/LOGCXX-360

**Solution**: add `#include <string.h>`

  `socketoutputstream.cpp:52:54: error: 'memcpy' was not declared in this scope`
  + `#include <string.h>`

  `console.cpp`
  + `#include <string.h>`
  + `#include <stdio.h>`

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