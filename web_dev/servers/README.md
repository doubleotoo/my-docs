Web Development > Servers
=========================

## HowTo Install Redmine in Apache Tomcat

*http://www.redmine.org/projects/redmine/wiki/HowTo_install_Redmine_in_Apache_Tomcat*

/rm


## Apache Tomcat

```bash
$ curl -O http://apache.spinellicreations.com/tomcat/tomcat-7/v7.0.28/bin/apache-tomcat-7.0.28.tar.gz
$ tar xzvf apache-tomcat-7.0.28.tar.gz
```

http://attackofzach.com/?p=52

```bash
$ rvm install jruby-1.6.5.1

$ wget --no-check-certificate https://www.chiliproject.org/attachments/download/344/chiliproject-3.2.2.tar.gz
$ tar xzvf chiliproject-3.2.2.tar.gz
$ cd chiliproject-3.2.2

$ jruby -S gem install -r bundler
Fetching: bundler-1.1.4.gem (100%)
Successfully installed bundler-1.1.4
1 gem installed

<edit Gemfile to include: `rmagick4j >= 0.3.7`>

$ jruby -S bundle install --without test development

$ jruby -S gem list --local

*** LOCAL GEMS ***

actionmailer (2.3.14)
actionpack (2.3.14)
activerecord (2.3.14)
activerecord-jdbc-adapter (1.2.2)
activerecord-jdbcmysql-adapter (1.2.2)
activerecord-jdbcpostgresql-adapter (1.2.2)
activerecord-jdbcsqlite3-adapter (1.2.2)
activeresource (2.3.14)
activesupport (2.3.14)
acts-as-taggable-on (2.1.0)
bouncy-castle-java (1.5.0146.1)
bundler (1.1.4 ruby)
coderay (1.0.7)
fastercsv (1.5.5)
gravatarify (3.0.0)
i18n (0.4.2)
jdbc-mysql (5.1.13)
jdbc-postgres (9.1.901)
jdbc-sqlite3 (3.7.2)
jruby-launcher (1.0.14 java)
jruby-openssl (0.7.7)
json (1.7.3 java)
liquid (2.3.0)
net-ldap (0.2.2)
rack (1.1.3)
rails (2.3.14)
rake (0.9.2.2)
rdoc (3.12)
rmagick4j (0.3.7)
ruby-openid (2.1.8)
rubygems-bundler (1.0.3)
rubytree (0.5.3)
rvm (1.11.3.4)
tzinfo (0.3.33)

$ mysql -u root -p
mysql> create database chiliproject character set utf8;
mysql> create user 'chiliproject'@'localhost' identified by 'chili';
mysql> grant all privileges on chiliproject.* to 'chiliproject'@'localhost';

# Configure the database
$ vim $CHILIPROJET/config/database.yml
production:
  adapter: jdbcmysql
  database: chiliproject
  host: localhost
  username: chiliproject
  password: chili
  encoding: utf8

$ cp configuration.yml.example configuration.yml

# Generate the session store
$ jruby -S bundle exec rake generate_session_store

# Define the application's mysql objects using rake db:migrate
$ RAILS_ENV=production jruby -S bundle exec rake db:migrate

# Load the default installation data
$ RAILS_ENV=production jruby -S bundle exec rake redmine:load_default_data

Select language: bg, bs, ca, cs, da, de, el, en, en-GB, es, eu, fa, fi, fr, gl, he, hr, hu, id, it, ja, ko, lt, lv, mk, mn, nl, no, pl, pt, pt-BR, ro, ru, sk, sl, sr, sr-YU, sv, th, tr, uk, vi, zh, zh-TW [en] 
====================================
Default configuration data loaded.

# Test the initial installation on the rails webrick server
RAILS_ENV=production jruby -S script/server -e production

[rose-dev@rose-git 3.2.2]$ RAILS_ENV=production jruby -S script/server -e production
=> Booting WEBrick
=> Rails 2.3.14 application starting on http://0.0.0.0:3000
NOTE: Gem.source_index is deprecated, use Specification. It will be removed on or after 2011-11-01.
Gem.source_index called from /data/home/rose-dev/development/opt/ruby/rvm/gems/jruby-1.6.6/gems/rails-2.3.14/lib/rails/gem_dependency.rb:21.
=> Call with -d to detach
=> Ctrl-C to shutdown server
[2012-06-26 13:17:54] INFO  WEBrick 1.3.1
[2012-06-26 13:17:54] INFO  ruby 1.8.7 (2012-01-30) [java]
[2012-06-26 13:17:54] INFO  WEBrick::HTTPServer#start: pid=21353 port=3000
```

Deploy to Apache Tomcat

```bash
# Install warbler
$ jruby -S gem install -r warbler
Fetching: jruby-jars-1.6.7.2.gem (100%)
Fetching: jruby-rack-1.1.7.gem (100%)
Fetching: rubyzip-0.9.9.gem (100%)
Fetching: warbler-1.3.5.gem (100%)
Successfully installed jruby-jars-1.6.7.2
Successfully installed jruby-rack-1.1.7
Successfully installed rubyzip-0.9.9
Successfully installed warbler-1.3.5
4 gems installed

# Create a warbler configuration
$ jruby -S warble config
cp /data/home/rose-dev/development/opt/ruby/rvm/gems/jruby-1.6.6/gems/warbler-1.3.5/warble.rb config/warble.rb

# Edit ${CHILIPROJECT}/config/warble.rb
$ git diff
diff --git a/config/warble.rb b/config/warble.rb
index d9735a2..8c11bd4 100644
--- a/config/warble.rb
+++ b/config/warble.rb
@@ -11,7 +11,7 @@ Warbler::Config.new do |config|
   # config.features = %w(gemjar)
 
   # Application directories to be included in the webapp.
-  config.dirs = %w(app config lib log vendor tmp)
+  config.dirs = %w(app config lib log vendor tmp extra files lang)
 
   # Additional files/directories to include, above those in config.dirs
   # config.includes = FileList["db"]
@@ -51,6 +51,11 @@ Warbler::Config.new do |config|
   # unless the vendor/rails directory is present.
   # config.gems += ["activerecord-jdbcmysql-adapter", "jruby-openssl"]
   # config.gems << "tzinfo"
+  config.gems += [
+      "activerecord-jdbcmysql-adapter",
+      "jruby-openssl",
+      "i18n",
+      "rack"]
 
   # Uncomment this if you don't want to package rails gem.
   # config.gems -= ["rails"]
@@ -79,6 +84,7 @@ Warbler::Config.new do |config|
   # Name of the archive (without the extension). Defaults to the basename
   # of the project directory.
   # config.jar_name = "mywar"
+  config.jar_name = "chili"
 
   # Name of the MANIFEST.MF template for the war file. Defaults to a simple
   # MANIFEST.MF that contains the version of Warbler used to create the war file.
@@ -138,6 +144,7 @@ Warbler::Config.new do |config|
   # since 1 runtime(default for threadsafe mode) will be enough.
   # config.webxml.jruby.min.runtimes = 2
   # config.webxml.jruby.max.runtimes = 4
+  config.webxml.jruby.max.runtimes = 4
 
   # JNDI data source name
   # config.webxml.jndi = 'jdbc/rails'

# Install a 1.0.x version of the jruby-rack library
$ jruby -S gem install -r -v=1.0.10 jruby-rack
Fetching: jruby-rack-1.0.10.gem (100%)
Successfully installed jruby-rack-1.0.10
1 gem installed

# Uninstall newer version of jruby-rack
$ jruby -S gem uninstall jruby-rack -v=1.1.7
Successfully uninstalled jruby-rack-1.1.7

# Build the .war file
# warning about 'lang'; maybe in newer versions of ChiliProject there is no lang directory
$ jruby -S warble
warning: application directory `lang' does not exist or is not a directory; skipping
rm -f chili.war
Creating chili.war

$ cd ${TOMCAT_HOME}/webapps
$ mkdir chili
$ cd chili
$ unzip -q /data/home/rose-dev/applications/chiliproject/3.2.2/chili.war
[rose-dev@rose-git chili]$ ls
404.html  dispatch.cgi.example   favicon.ico            javascripts    stylesheets
422.html  dispatch.fcgi.example  htaccess.fcgi.example  META-INF       themes
500.html  dispatch.rb.example    images                 plugin_assets  WEB-INF
```

```bash
$ rvm use jruby-1.6.6
```

## ChiliProject

### LDAP Authentication

Login with `admin/admin`

New authentication mode (LDAP)
Name: PAC/OUN
Host: ldaps-auth.llnl.gov
Port: 636 (LDAPS)
Base DN: ou=People,dc=llnl,dc=gov
Login: uid
First name: givenName
Last name: sN
Email: mail

### Email Notifications
# specific configuration options for production environment
# # that overrides the default ones
```yaml
production:
  delivery_method: :smtp
  smtp_settings:
    address: "smtp.llnl.gov"
    domain: "llnl.gov"
    authentication: :none
```


### Add-ons

* Redmine Pro iOS app: http://itunes.apple.com/us/app/redminepro/id415596033?mt=8



Sqlite3 to MySQL
* http://www.redmine.org/boards/2/topics/12793

```bash
$ curl -O http://www.redmine.org/attachments/download/7545/sqlite3-to-mysql.py
$ sqlite3 redmine.db .dump | ./sqlite3-to-mysql.py -u root -p Changeme1 -d foo | mysql -u root -p foo --default-character-set=utf8
$ RAILS_ENV=production jruby -S bundle exec rake db:migrate
```

Backup MySQL: 10 ways

http://www.noupe.com/how-tos/10-ways-to-automatically-manually-backup-mysql-database.html

#### mysqldump

http://dev.mysql.com/doc/refman/5.0/en/mysqldump.html

```bash
$ mysqldump --user <name> --password=<pass> --all-databases > <file>
```

You can back up directly to another MySQL server using

```bash
$ mysqldump --host=host1 --opt <database> | mysql --host=host2 -C <database>
```

`--opt` stands for optimize

mysqldump ... | gzip > <database>.gz

#### Restoring a Backup

```bash
$ mysql <database> < <backup.sql.dump>
```


### Plugins

Installing
http://www.redmine.org/projects/redmine/wiki/Plugins


---

# hudson-rose-31

RedmineInstall: http://www.redmine.org/projects/redmine/wiki/RedmineInstall

## Install RVM

```bash
$ wget --no-check-certificate  https://get.rvm.io

[hudson-rose@hudson-rose-31]pwd
/export/tmp.hudson-rose/applications/redmine-2.0.3/rvm

[hudson-rose@hudson-rose-31]export rvm_path="$(pwd)"


<Add --insecure to curl commands in ./rvm-installer>

[hudson-rose@hudson-rose-31]./rvm-installer
Downloading RVM from wayneeseguin branch master
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100 1045k  100 1045k    0     0   191k      0  0:00:05  0:00:05 --:--:--  331k

Installing RVM to /export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/
    RVM PATH line found in /home/hudson-rose/.zshrc.
    RVM sourcing line found in /home/hudson-rose/.bash_profile /home/hudson-rose/.zlogin.

# RVM:  Shell scripts enabling management of multiple ruby environments.
# RTFM: https://rvm.io/
# HELP: http://webchat.freenode.net/?channels=rvm (#rvm on irc.freenode.net)
# Cheatsheet: http://cheat.errtheblog.com/s/rvm/
# Screencast: http://screencasts.org/episodes/how-to-use-rvm

# In case of any issues read output of 'rvm requirements' and/or 'rvm notes'

Installation of RVM in /export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/ is almost complete:

  * To start using RVM you need to run `source /export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/scripts/rvm`
    in all your open shell windows, in rare cases you need to reopen all shell windows.

# hudson-rose,
#
#   Thank you for using RVM!
#   I sincerely hope that RVM helps to make your life easier and more enjoyable!!!
#
# ~Wayne


rvm 1.14.3 () by Wayne E. Seguin <wayneeseguin@gmail.com>, Michal Papis <mpapis@gmail.com> [https://rvm.io/]
```

## Install jruby-1.6.7

```bash
[hudson-rose@hudson-rose-31]rvm install jruby-1.6.7
jruby-1.6.7 - #fetching 
jruby-1.6.7 - #downloading jruby-bin-1.6.7, this may take a while depending on your connection...
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100 14.8M  100 14.8M    0     0  1982k      0  0:00:07  0:00:07 --:--:-- 2431k
jruby-1.6.7 - #extracting jruby-bin-1.6.7 to /export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/src/jruby-1.6.7
jruby-1.6.7 - #extracted to /export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/src/jruby-1.6.7
Building Nailgun
jruby-1.6.7 - #installing to /export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/rubies/jruby-1.6.7
jruby-1.6.7 - #importing default gemsets (/export/tmp.hudson-rose/applications/redmine-2.0.3/rvm/gemsets/)
Copying across included gems
```

## Install jruby gem: bundler

```bash
[hudson-rose@hudson-rose-31]jruby -S gem install -r bundler
Successfully installed bundler-1.1.4
1 gem installed
```

## `bundle install`

```bash
<edit Gemfile to include: `rmagick4j >= 0.3.7`>

$ jruby -S bundle install --without test development
Fetching gem metadata from http://rubygems.org/.......
Using rake (0.9.2.2) 
Installing i18n (0.6.0) 
Installing multi_json (1.3.6) 
Installing activesupport (3.2.6) 
Installing builder (3.0.0) 
Installing activemodel (3.2.6) 
Installing erubis (2.7.0) 
Installing journey (1.0.4) 
Installing rack (1.4.1) 
Installing rack-cache (1.2) 
Installing rack-test (0.6.1) 
Installing hike (1.2.1) 
Installing tilt (1.3.3) 
Installing sprockets (2.1.3) 
Installing actionpack (3.2.6) 
Installing mime-types (1.19) 
Installing polyglot (0.3.3) 
Installing treetop (1.4.10) 
Installing mail (2.4.4) 
Installing actionmailer (3.2.6) 
Installing arel (3.0.2) 
Installing tzinfo (0.3.33) 
Installing activerecord (3.2.6) 
Installing activerecord-jdbc-adapter (1.2.2) 
Installing jdbc-mysql (5.1.13) 
Installing activerecord-jdbcmysql-adapter (1.2.2) 
Installing jdbc-postgres (9.1.901) 
Installing activerecord-jdbcpostgresql-adapter (1.2.2) 
Installing jdbc-sqlite3 (3.7.2) 
Installing activerecord-jdbcsqlite3-adapter (1.2.2) 
Installing activeresource (3.2.6) 
Using bouncy-castle-java (1.5.0146.1) 
Using bundler (1.1.4) 
Installing coderay (1.0.7) 
Installing fastercsv (1.5.5) 
Using jruby-openssl (0.7.7) 
Installing json (1.7.3) 
Installing net-ldap (0.3.1) 
Installing rack-ssl (1.3.2) 
Installing rdoc (3.12) 
Installing thor (0.15.3) 
Installing railties (3.2.6) 
Installing rails (3.2.6) 
Installing prototype-rails (3.2.1) 
Installing ruby-openid (2.1.8) 
Installing rack-openid (1.3.1) 
Your bundle is complete! Use `bundle show [gemname]` to see where a bundled gem is installed.
Post-install message from rdoc:
Depending on your version of ruby, you may need to install ruby rdoc/ri data:

<= 1.8.6 : unsupported
 = 1.8.7 : gem install rdoc-data; rdoc-data --install
 = 1.9.1 : gem install rdoc-data; rdoc-data --install
>= 1.9.2 : nothing to do! Yay!

$ jruby -S gem list --local

*** LOCAL GEMS ***

actionmailer (3.2.6)
actionpack (3.2.6)
activemodel (3.2.6)
activerecord (3.2.6)
activerecord-jdbc-adapter (1.2.2)
activerecord-jdbcmysql-adapter (1.2.2)
activerecord-jdbcpostgresql-adapter (1.2.2)
activerecord-jdbcsqlite3-adapter (1.2.2)
activeresource (3.2.6)
activesupport (3.2.6)
arel (3.0.2)
bouncy-castle-java (1.5.0146.1)
builder (3.0.0)
bundler (1.1.4 ruby)
coderay (1.0.7)
erubis (2.7.0)
fastercsv (1.5.5)
hike (1.2.1)
i18n (0.6.0)
jdbc-mysql (5.1.13)
jdbc-postgres (9.1.901)
jdbc-sqlite3 (3.7.2)
journey (1.0.4)
jruby-launcher (1.0.14 java)
jruby-openssl (0.7.7)
json (1.7.3 java)
mail (2.4.4)
mime-types (1.19)
multi_json (1.3.6)
net-ldap (0.3.1)
polyglot (0.3.3)
prototype-rails (3.2.1)
rack (1.4.1)
rack-cache (1.2)
rack-openid (1.3.1)
rack-ssl (1.3.2)
rack-test (0.6.1)
rails (3.2.6)
railties (3.2.6)
rake (0.9.2.2)
rdoc (3.12)
ruby-openid (2.1.8)
rubygems-bundler (1.0.3)
rvm (1.11.3.4)
sprockets (2.1.3)
thor (0.15.3)
tilt (1.3.3)
treetop (1.4.10)
tzinfo (0.3.33)
```

## Setup MySQL

```bash
$ mysql -u root -p
mysql> create database redmine character set utf8;
mysql> create user 'redmine'@'localhost' identified by '<password>';
mysql> grant all privileges on redmine.* to 'redmine'@'localhost';
```

## Configure the Redmine Database
```bash
$ cp $REDMINE/config/database.yml.example $REDMINE/config/database.yml

$ vim $REDMINE/config/database.yml
production:
  adapter: mysql
  database: redmine
  host: localhost
  username: redmine
  password: <password>
  encoding: utf8
```

##

```bash
$ cp configuration.yml.example configuration.yml
$ vi configuration.yml
<add SMTP email configuration, attachment (files) storage path, etc.>
```

# Generate the session store (Redmine 2.x)
$ jruby -S bundle exec rake generate_secret_token

# Define the application's mysql objects using rake db:migrate
$ RAILS_ENV=production jruby -S bundle exec rake db:migrate

# Load the default installation data
$ RAILS_ENV=production jruby -S bundle exec rake redmine:load_default_data

Select language: bg, bs, ca, cs, da, de, el, en, en-GB, es, eu, fa, fi, fr, gl, he, hr, hu, id, it, ja, ko, lt, lv, mk, mn, nl, no, pl, pt, pt-BR, ro, ru, sk, sl, sr, sr-YU, sv, th, tr, uk, vi, zh, zh-TW [en]$
====================================
Default configuration data loaded.

# Test the initial installation on the rails webrick server (Redmine 2.x)
$ RAILS_ENV=production jruby -S script/rails server webrick -e production


## Logging configuration


## Daily Backups

```bash
# Database
/usr/bin/mysqldump -u <username> -p<password> <redmine_database> | gzip > /path/to/backup/db/redmine_`date +%y_%m_%d`.gz

# Attachments
rsync -a /path/to/redmine/files /path/to/backup/files
```

[hudson-rose@hudson-rose-31]sqlite3 ~/opt/redmine/REDMINE/db/redmine.db .dump | ./sqlite3-to-mysql.py -u root -p Changeme1 -d redmine | mysql -u root -p redmine --default-character-set=utf8

$ RAILS_ENV=production jruby -S bundle exec rake db:migrate



http://www.kartar.net/2008/08/migrating-a-rails-database-from-sqlite3-to-mysql/

http://rubygems.org/gems/yaml_db

[hudson-rose@hudson-rose-31]jruby -S gem install yaml_db
Fetching: yaml_db-0.2.3.gem (100%)
Successfully installed yaml_db-0.2.3
1 gem installed

