git
===

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
