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

**References**
* [Usage of Conditionals](http://www.gnu.org/software/automake/manual/html_node/Usage-of-Conditionals.html)