C++ > XML
=========

1. **Download** the source tarballs

   ```bash
   $ curl -O http://www.eng.lsu.edu/mirrors/apache//xerces/c/3/sources/xerces-c-3.1.1.tar.gz
   ```

2. **Unpack** the source code

   ```bash
   $ tar -xzf xerces-c-3.1.1.tar.gz
   # => XERCES_SOURCE
   ```

3. **Autotools** setup

   ```bash
   $ source /nfs/apps/autoconf/2.67/
   $ source /nfs/apps/automake/1.9.6/setup.sh
   $ source /nfs/apps/m4/1.4.14/setup.sh

   # Generate `configure` script
   $ ${XERCES_SOURCE}/reconf # runs libtoolize, aclocal, autoheader, automake, autoconf
   ```

3. **[Build and install](http://xerces.apache.org/xerces-c/build-winunix-2.html#UNIX)**

   *Note: official Xerces build documentation seems out-dated*

   ``` bash
   # use a separate build tree to keep things clean
   $ mkdir build-xerces
   $ cd build-xerces

   # Set your Xerces-C++ root path
   $ export XERCESCROOT=$XERCES_SOURCE

   # configure
   $ $XERCES_SOURCE/configure --prefix="/your/desired/install/path/"
   ...
   configure: Report:
   configure:   File Manager: POSIX
   configure:   Mutex Manager: POSIX
   configure:   Transcoder: gnuiconv
   configure:   NetAccessor: curl
   configure:   Message Loader: inmemory

   # build and install
   $ make
   $ make install
   ```

**Problem**: `Permission denied` during `make`

```bash
Compiling xercesc/util/HeaderDummy.cpp
/bin/sh: line 2: .deps/strnicmp.Tpo: Permission denied
make[4]: *** [strnicmp.lo] Error 126
make[4]: *** Waiting for unfinished jobs....
/bin/sh: line 2: .deps/stricmp.Tpo: Permission denied
make[4]: *** [stricmp.lo] Error 126
```

**Solution**: `Permission denied` during `make`

Don't run `make` in the source tree, i.e. build in a separate directory.

4. **Validate installation**

   * `${LLVM_INSTALL}/bin/clang`
   * `${LLVM_INSTALL}/bin/llvm-config`
   * `${LLVM_INSTALL}/include/*/*.inc` files: could be missing if you ran `make install` without running `make` first.
     (Observed on `32-bit RHEL5` and `64-bit Ubuntu`.)

     ```bash
       $ find "${LLVM_INSTALL}" -name "*.inc"
       ${LLVM_INSTALL}/include/clang/AST/AttrImpl.inc
       ...
     ```
