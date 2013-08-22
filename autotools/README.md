autotools
=========

## Autoconf

Examples of package configuration wrappers, `pkg-config`:

* LLVM
* https://github.com/vslavik/xmlwrapp

## Autoconf

### AC_CONFIG_SUBDIR

See [AC_CONFIG_SUBDIR_CUSTOM](http://lists.gnu.org/archive/html/autoconf/2011-04/msg00015.html)


## Automake

### Functions
See http://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html#File-Name-Functions.

```Makefile
$(dir names...)
$(notdir names...)
$(suffix names...)
$(basename names...)
$(addprefix prefix, names...)
...

```

### Automatic Variables
See http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html.

$@, $<, etc.

### `%` Stem

```Makefile
OBJECTS=abc.o bca.o cba.o

# This will set a dependency for each .o file 
# as its corresponding .c file.
#
# For example:
#
#     abc.o : %.o : $(SRC)/%.c
#
# would expand to:
#
#     abc.o : abc.o : $(SRC)/abc.c
#
$(OBJECTS) : %.o : $(SRC)/%.c
  <some rules>
```

See http://stackoverflow.com/questions/14573869/passing-target-name-to-a-dependency-in-makefile.

#### Conditionals
* `if..else..endif` statements should **start on column one** (indentation not allowed!)

* You may **only test a single variable** in an if statement, possibly negated using ‘!’.

     ```Automake
       if DEBUG
       DBG = debug
       else !DEBUG
       DBG =
       endif !DEBUG
     ```

* **Do not define or modify `SUBDIRS` conditionally**

  > `SUBDIRS` must be defined unconditionally to include all subdirectories 
  > that might ever be needed, on any system. Otherwise, `make dist` will yield unexpected
  > results

  > The right way to handle conditionally building parts of the codebase  
  > is modify the `Makefile.am` in the directory where the conditionally-
  > built code resides.
  
  > *http://old.nabble.com/conditional-builds-td965715.html*

**References**
* [Usage of Conditionals](http://www.gnu.org/software/automake/manual/html_node/Usage-of-Conditionals.html)

#### Environment

```Automake
# Make the libtap.sh file available to the Shell test scripts
# through an environment variable.
export am_libtap_sh=${abs_top_srcdir}/tests/libtap.sh
```

## Libtool

#### Versioning (`-version-info`)

`configure.ac`:

```Autoconf
dnl +1 : ? : +1  == new interface that does not break old one
dnl +1 : ? : 0   == new interface that breaks old one
dnl  ? : ? : 0   == no new interfaces, but breaks apps
dnl  ? :+1 : ?   == just some internal changes, nothing breaks but might work
dnl                 better
dnl CURRENT : REVISION : AGE
ROSE_LT_VERSION="0:0:0"
AC_SUBST(ROSE_LT_VERSION)
```

`Makefile.am`:

```Automake
librose_la_LDFLAGS = \
  -version-info @LT_VERSION@
```

**References**
* [libtool/Versioning](http://www.gnu.org/software/libtool/manual/html_node/Versioning.html#Versioning)
