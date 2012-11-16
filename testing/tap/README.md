# Test harness

# c++-tap-harness

See Prove testing harness: http://search.cpan.org/~ovid/Test-Harness-3.25/bin/prove
See documentation for the TAP format (Test::Harness::Tap): http://search.cpan.org/~petdance/Test-Harness-2.64/lib/Test/Harness/TAP.pod


## Automake TAP test harness

See `$AUTOMAKE_PREFIX/share/automake-APIVERSION/tap-driver.[pl,sh]` (http://www.gnu.org/software/automake/manual/html_node/Use-TAP-with-the-Automake-test-harness.html).


## c-tap-harness

See great shell script TAP library https://github.com/rra/c-tap-harness/blob/master/tests/tap/libtap.sh.


See example usage:

* `libtap.sh`: https://github.com/rra/c-tap-harness/blob/master/tests/libtap/basic.t
* Unit tests: https://github.com/rra/c-tap-harness/blob/master/tests/libtap/basic

`Makefile.am` - Runs the `runtests` TAP testing harness with the list of `*.t` TAP tests listed in the file `*/tests/TESTS`:

```
# The bits below are for the test suite.
check_PROGRAMS = tests/libtap/basic/c-bail tests/libtap/basic/c-basic  \
  ...
  tests/libtap/basic/c-sysbail tests/libtap/basic/c-tmpdir
tests_libtap_basic_c_bail_LDADD = tests/tap/libtap.a -lm


check-local: $(check_PROGRAMS)
  cd tests && ./runtests -s '$(abs_top_srcdir)/tests' \
      -b '$(abs_top_builddir)/tests' $(abs_top_srcdir)/tests/TESTS
```


`tests/TESTS` - File specifies the TAP test file `*.t`:

```
docs/pod
docs/pod-spelling
harness/basic
harness/env
harness/search
harness/single
libtap/basic
```

## Git

See [Git's testing](https://github.com/git/git/tree/master/t)


Main test library files:

* `$GIT/t/test-lib.sh`
* `$GIT/t/test-lib-functions.sh`

`$GIT/t/aggregate-results.sh`:

Each `*.sh` testing script generates a `*.counts` file:

```
total 19
success 19
fixed 0
broken 0
failed 0
```

## Extracted functions

### Utility

```
say () {
  say_color info "$*"
}
```


### test_expect_failure

```
test_expect_failure () {
  test "$#" = 3 && { test_prereq=$1; shift; } || test_prereq=
  test "$#" = 2 ||
  error "bug in the test script: not 2 or 3 parameters to test-expect-failure"
  export test_prereq
  if ! test_skip "$@"
  then
    say >&3 "checking known breakage: $2"
    if test_run_ "$2" expecting_failure
    then
      test_known_broken_ok_ "$1"
    else
      test_known_broken_failure_ "$1"
    fi
  fi
  echo >&3 ""
}
```

----------------------------------------------------------------

TAP: "Test Anything Protocol"

Tutorials:

* http://www.effectiveperlprogramming.com/blog/1271
* http://szabgab.com/tap--test-anything-protocol.html


See [Use TAP with the Automake test harness](http://www.gnu.org/software/automake/manual/html_node/Use-TAP-with-the-Automake-test-harness.html)
See [Introduction to TAP](http://www.gnu.org/software/automake/manual/html_node/Introduction-to-TAP.html)

See [Scripts-based Testsuite](http://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html)

Examples:

* [Git's testing](https://github.com/git/git/tree/master/t)
* https://github.com/lehmannro/assert.sh
* https://github.com/illusori/bash-tap
* https://github.com/mca-wtsi/sh-tap



## Mailing List (automake@gnu.org)

TAP support documentation:

```
On Wed, 14 Nov 2012, Alexis Praga wrote:

Reading about TAP support in the manual, I decided to try this feature.
Unfortunately, it does not work for versions prior to 1.12.
Could you make it more obvious in the manual ? It seems to assume you run
the latests, which is not always the case.

Manuals always refer to the current software and are bundled with the
software so they are correct for that software version.  Manuals on
the web are put there as a service but may not apply to older
versions.

Also, I would still like to have this feature. Hereis is how I rapidly
implemented it in the top Makefile.am :

TAP_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh
TESTS = foo.test

check:
        @for i in $(TESTS); do \
          $(TAP_LOG_DRIVER) --test-name "$$i" \
             --log-file $$i.log --trs-file $$i.trs -- $$i;\
        done


Do you think this hack can be used without too much surprise ? Otherwise,
what do you recommand (upgrading is not an option) ?

Does it work?  Did you verify with 'make distcheck'?  Why are you not
able to update to Automake 1.12?

For the latest GraphicsMagick release, the tests were converted to use
TAP as provided with Automake 1.12.  TAP seemed to work fine (it was a
definite improvement over original Automake tests) but it was
necessary to add an additional common framework to make TAP tests easy
to implement.  The common framework used by Automake itself could not
be directly borrowed since it is GPLed and not easily redistributable
in packages which are not GPLed.

Bob
--
Bob Friesenhahn
bfriesen@simple.dallas.tx.us, http://www.simplesystems.org/users/bfriesen/
GraphicsMagick Maintainer,    http://www.GraphicsMagick.org/
```


## Misc

[Autotools Bootstrap](http://code.google.com/p/autotools-bootstrap/)