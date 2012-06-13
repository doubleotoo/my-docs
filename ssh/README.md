SSH
===

## ``~/.ssh/config`

```bash
  # == ControlMaster
  #
  # Authenticate once; subsequent sessions will not require a password
  # 1. Apply the following directives to all hosts
  # 2. First time you connect to a host, make it the master
  #    session
  # 3. Put the socket file at this path, identified by
  #    remote username, remote host, and the session's port
  #
  # == ControlPersist (OpenSSH 5.6+: `$ port install openssh`)
  #
  # ControlPersist addresses one annoyance with ControlMaster: the master session
  # needs to stay open to keep the socket file alive.  With ControlPersist, the
  # socket will stay around for a fixed amount of time regardless of whether you
  # close the master session or not.  ssh accomplishes this by spawning a daemon
  # to keep the master connection alive, and the daemon simply dies after its
  # time limit has expired.
  #
  # == SSH can silently hang!
  #
  # 1. Kill all existing ssh sessions
  #
  #   `local $ killall ssh`
  #
  #   (Newer versions of SSH rename the ControlPersist process to start
  #   with "ssh:".)
  #
  # 2. Remove the offending socket file in `/tmp/<socket_file>`
  Host *
  ControlMaster auto
  ControlPath /tmp/%r@%h:%p
  ControlPersist 12h

  # github
  Host github.com
       User git
       Hostname github.com
       IdentityFile ~/.ssh/github/id_rsa

  # heroku
  Host heroku.com
       User git
       Hostname heroku.com
       IdentityFile ~/.ssh/heroku/id_rsa
```

