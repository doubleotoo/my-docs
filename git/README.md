git
===

## Install

```bash
  $ wget http://git-core.googlecode.com/files/git-1.8.1.tar.gz
  $ tar xzvf git-1.8.1.tar.gz
  $ cd git-1.8.1
  
  $ cat INSTALL
  
  $ ./configure --prefix="$(pwd)/../install/1.8.1"
  $ make PROFILE=BUILD install  # optimized installation
```


## Debug

```bash
  $ export GIT_CURL_VERBOSE=1
```

For HTTPS errors, see https://help.github.com/articles/https-cloning-errors.

## SSL certificate problem, verify that the CA cert is OK.

Tell cURL to not check for SSL certificates:

1. Environment variable (temporary)

    ```bash
      $ env GIT_SSL_NO_VERIFY=true git pull
    ```

2. git-config

   ```bash
     # set local configuration
     $ git config --local http.sslVerify false

     # set global configuration
     $ git config --global http.sslVerify false
   ```

## Rebase

[Rebasing Merge Commits](http://notes.envato.com/developers/rebasing-merge-commits-in-git/)

```bash
  $ git fetch origin
  $ git rebase --preserve-merges origin/master
```

```bash
  $ git pull --rebase # can't supply --preserve-merges
```

## Diff

In-browser diff: [rubychan/water](https://github.com/rubychan/water)
