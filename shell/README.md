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


## Interactive

If debugging, print progress indicator.

* For example, use a single dot `.` to produce a stream like `.......` for each
  step:

  ```bash
  $ [[ -n "$DEBUG" ]] && echo -n .
  ```


## Bash

### [The Double-Parentheses Construct](http://tldp.org/LDP/abs/html/dblparens.html)

```
Similar to the let command, the (( ... )) construct permits arithmetic expansion and evaluation.
In its simplest form, a=$(( 5 + 3 )) would set a to 5 + 3, or 8. However, this double-parentheses
construct is also a mechanism for allowing C-style manipulation of variables in Bash,
for example, (( var++ )).
```

### Rename function

See http://stackoverflow.com/a/1203628/870000.

```bash
# copies function named $1 to name $2
copy_function() {
    declare -F $1 > /dev/null || return 1
    eval "$(echo "${2}()"; declare -f ${1} | tail -n +2)"
}
```

Can be used like so:

```bash
$ theirfunc() { echo "do their thing"; }
$ copy_function theirfunc orig_theirfunc
$ theirfunc() { echo "do my thing"; orig_theirfunc; }
$ theirfunc
do my thing
do their thing
```

