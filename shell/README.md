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
