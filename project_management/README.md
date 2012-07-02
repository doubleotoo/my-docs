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

$ ssh admin@enterprise-server -- 'ghe-support-bundle -o' > support-bundle.tgz

---

ghe-cleanup-repos

> This utility is used to fix repositories in various bad states (e.g., won't delete through the web UI). This was specifically crafted to fix problems that were caused by a bug in the 11.10.270 release.

Solution: upgrade to 11.10.271

* Added ghe-cleanup-repos utility to cleanup failed repo forks, empty wiki repos, and repos that failed to delete for customers affected by the background job bug mentioned below.

