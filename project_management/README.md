Project Management
==================

* [chiliproject/chiliproject](https://github.com/chiliproject/chiliproject)

  Public fork of Redmine

  https://www.chiliproject.org/

  [Deploying to Tomcat](http://attackofzach.com/?p=52)

## Code Review

### Gerrit

[Install J2EE, e.g. Tomcat](http://gerrit.googlecode.com/svn/documentation/2.2.1/install-j2ee.html)

### Github Enterprise

Allow SSH admin access via the web interface: github.llnl.gov/setup

$ ssh admin@github.llnl.gov

$ mysql -u root
<no password required>

Utility scripts:
https://support.enterprise.github.com/entries/21254402-command-line-utilities

$ ghe-*

Downloading logs from your installation (Support Bundle)
https://support.enterprise.github.com/entries/21383598-downloading-logs-from-your-installation

$ ssh admin@github.llnl.gov -- 'ghe-support-bundle -o' > support-bundle.tgz

---

ghe-cleanup-repos

> This utility is used to fix repositories in various bad states (e.g., won't delete through the web UI). This was specifically crafted to fix problems that were caused by a bug in the 11.10.270 release.

Solution: upgrade to 11.10.271

* Added ghe-cleanup-repos utility to cleanup failed repo forks, empty wiki repos, and repos that failed to delete for customers affected by the background job bug mentioned below.


Delete stale database rows: (should use Admin Utility instead)

```bash
mysql> select R.id, R.name, U.login from repositories R, users U where R.owner_id = U.id;
+----+----------------------+---------------+
| id | name                 | login         |
+----+----------------------+---------------+
|  2 | anotherrepo          | aquilino1     |
|  1 | testrepo             | aquilino1     |
|  3 | rose                 | hudson-rose   |
| 16 | rose-1               | hudson-rose   |
|  6 | EDG                  | rose-compiler |
|  4 | rose                 | rose-compiler |
|  7 | vulnerabilitySeeding | rose-compiler |
| 19 | EDG                  | liao6         |
| 11 | rose                 | liao6         |
| 22 | rose2                | liao6         |
|  5 | rose                 | vanka1        |
| 23 | rose                 | ma23          |
| 21 | rose                 | lin32         |
| 14 | rose                 | aananthakris1 |
+----+----------------------+---------------+
14 rows in set (0.00 sec)

mysql> delete from repositories where id=15;
```




