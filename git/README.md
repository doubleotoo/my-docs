git
===

## Debug

```bash
  $ export GIT_CURL_VERBOSE=1
```

## SSL certificate problem, verify that the CA cert is OK.

Tell cURL to not check for SSL certificates:

1.. Environment variable (temporary)

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
