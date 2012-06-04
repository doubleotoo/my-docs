autotools
=========

## Automake

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