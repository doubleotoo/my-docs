Shell
=====

Terminal colors:
* https://github.com/janlelis/paint


## find

Search for files in `<location>` created within a given `<time_period>`.

``bash
$ find <location> -ctime <time_period>
``

**Examples**:
* Created today: `-ctime 0`
* Created more than 30 days ago: `-ctime +30`
* Created less than 30 days ago: `-ctime -30`
* Created exactly than 30 days ago: `-ctime 30`


## printf

See http://wiki.bash-hackers.org/commands/builtin/printf.

Assign `printf` output to the variable `VAR` instead of printing to `stdout`:

* General Form:

  ```bash
  $ printf -v <VAR> "<STRING>"
  ```

* [Example](https://github.com/lehmannro/assert.sh/blob/master/assert.sh):

  ```bash
  $ printf -v _indent "\n\t"
  ```