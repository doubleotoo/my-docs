svn
===

## Error validating server cerftificate

### Problem

**Problem reocurrs even if I enter the “p” option**:

```bash
$ svn_load_dirs.1.4.5.pl: /nfs/apps/subversion/1.5.5/bin/svn log -r HEAD --username liaoch https://outreach.scidac.gov/svn/rose failed with this output:
Error validating server certificate for 'https://outreach.scidac.gov:443':
 - The certificate is not issued by a trusted authority. Use the
   fingerprint to validate the certificate manually!
Certificate information:
 - Hostname: outreach.scidac.gov
 - Valid: from Thu, 14 Oct 2010 14:35:19 GMT until Mon, 14 Oct 2013 14:35:19 GMT
 - Issuer: Cyber Security Program, Livermore, CA, US
 - Fingerprint: 3e:d0:b2:3c:10:cc:b6:5c:55:af:fc:41:72:04:22:7c:b8:a2:65:6d
(R)eject, accept (t)emporarily or accept (p)ermanently? svn: OPTIONS of 'https://outreach.scidac.gov/svn/rose': Server certificate verification failed: issuer is not trusted (https://outreach.scidac.gov)
```

### Solution

```bash
  $ rm ~/.subversion/auth/svn.ssl.server/*
```

http://svnbook.red-bean.com/en/1.5/svn.serverconfig.httpd.html#svn.serverconfig.httpd.authn.sslcerts