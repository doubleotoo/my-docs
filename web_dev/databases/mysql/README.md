# MySQL

1. Create the database datadir with `mysql_install_db`

   ```bash
   $ /usr/bin/mysql_install_db  --datadir=/global/u1/t/too1/applications/mysql/datadir
   Installing MySQL system tables...
   120907 14:32:51 [Warning] One can only use the --user switch if running as root

   OK
   Filling help tables...
   120907 14:32:51 [Warning] One can only use the --user switch if running as root

   OK

   To start mysqld at boot time you have to copy
   support-files/mysql.server to the right place for your system

   PLEASE REMEMBER TO SET A PASSWORD FOR THE MySQL root USER !
   To do so, start the server, then issue the following commands:
   /usr/bin/mysqladmin -u root password 'new-password'
   /usr/bin/mysqladmin -u root -h sgn02 password 'new-password'

   Alternatively you can run:
   /usr/bin/mysql_secure_installation

   which will also give you the option of removing the test
   databases and anonymous user created by default.  This is
   strongly recommended for production servers.

   See the manual for more instructions.

   You can start the MySQL daemon with:
   cd /usr ; /usr/bin/mysqld_safe &

   You can test the MySQL daemon with mysql-test-run.pl
   cd mysql-test ; perl mysql-test-run.pl

   Please report any problems with the /usr/bin/mysqlbug script!

   The latest information about MySQL is available on the web at
   http://www.mysql.com
   Support MySQL by buying support/licenses at http://shop.mysql.com
   ```

2. Check populated contents of datadir

   ```bash
   $ ls datadir/
   mysql  test

   $ ls datadir/mysql/
   columns_priv.frm   help_keyword.MYD   proc.MYI                   time_zone_name.frm
   columns_priv.MYD   help_keyword.MYI   procs_priv.frm             time_zone_name.MYD
   columns_priv.MYI   help_relation.frm  procs_priv.MYD             time_zone_name.MYI
   db.frm             help_relation.MYD  procs_priv.MYI             time_zone_transition.frm
   db.MYD             help_relation.MYI  tables_priv.frm            time_zone_transition.MYD
   db.MYI             help_topic.frm     tables_priv.MYD            time_zone_transition.MYI
   func.frm           help_topic.MYD     tables_priv.MYI            time_zone_transition_type.frm
   func.MYD           help_topic.MYI     time_zone.frm              time_zone_transition_type.MYD
   func.MYI           host.frm           time_zone_leap_second.frm  time_zone_transition_type.MYI
   help_category.frm  host.MYD           time_zone_leap_second.MYD  user.frm
   help_category.MYD  host.MYI           time_zone_leap_second.MYI  user.MYD
   help_category.MYI  proc.frm           time_zone.MYD              user.MYI
   help_keyword.frm   proc.MYD           time_zone.MYI

   $ ls datadir/test/
   <empty>
   ```

3. Start the `mysqld`

```bash
$ /usr/bin/mysqld_safe \
  --defaults-file=/global/homes/t/too1/applications/mysql/mysql.config \
  --language=/usr/share/mysql/english
```

4. Connect to `mysql`

```bash
$ mysql --defaults-file=/global/u1/t/too1/applications/mysql/mysql.config -u root -p
```

`mysql.config`:

```
[mysqld]
user=too1
basedir=/global/u1/t/too1/applications/mysql
datadir=/global/u1/t/too1/applications/mysql/data
bind-address = <IP ADDRESS>
port=4450
socket=/global/u1/t/too1/applications/mysql/tmp/mysql.sock

[mysqld_safe]
log-error=/global/u1/t/too1/applications/mysql/log/mysqld.log
pid-file=/global/u1/t/too1/applications/mysql/mysqld.pid

[client]
port=4450
user=too1
socket=/global/u1/t/too1/applications/mysql/tmp/mysql.sock

[mysqladmin]
user=too1
port=4450
socket=/global/u1/t/too1/applications/mysql/tmp/mysql.sock

[mysql]
port=4450
socket=/global/u1/t/too1/applications/mysql/tmp/mysql.sock

[mysql_install_db]
user=too1
port=4450
basedir=/global/u1/t/too1/applications/mysql
datadir=/global/u1/t/too1/applications/mysql/data
socket=/global/u1/t/too1/applications/mysql/tmp/mysql.sock
```
