sysadmin
========

## VirtualBox

```bash
  $ VBoxManage list vms
  $ VBoxManage showvminfo <vm>
  $ VBoxManage unregister <vm>
  $ VBoxManage controlvm <vm> poweroff
  $ VBoxManage startvm --type headless <vm>
```

```bash
  Step [0] was successfully - saving state

  Waiting for ssh login with user vagrant to sshd on port => 7222 to work
  ......................................................................................................................................................................................................Transferring /home/hudson-rose/Applications/vagrant/fedora/16/x86_64/default/definitions/fedora-16-x86_64/postinstall.sh to postinstall.sh 
  ..

  # Hanging - endless wait for ssh on port 7222
  # https://github.com/jedi4ever/veewee/issues/116
  $ VBoxManage startvm --type headless fedora-16-x86_64
  Waiting for VM "fedora-16-x86_64" to power on...
  VM "fedora-16-x86_64" has been successfully started.
  
  ...
  
  ***echo 'vagrant'|sudo -S sh 'postinstall.sh'
  Executing command: echo 'vagrant'|sudo -S sh 'postinstall.sh'
```

## Vagrant

**Vagrant file options**: http://vagrantup.com/v1/docs/vagrantfile.html

#### Vagran SSH keys

Example `postinstall.sh`:

```bash
#Installing vagrant keys
mkdir /home/vagrant/.ssh
chmod 700 /home/vagrant/.ssh
cd /home/vagrant/.ssh
wget --no-check-certificate 'https://raw.github.com/mitchellh/vagrant/master/keys/vagrant.pub' -O authorized_keys
chown -R vagrant /home/vagrant/.ssh
```

**Important**: disable the SSL certificate check, e.g. `wget --no-check-certificate`.

#### Ubuntu

```bash
sudo apt-get install g++-4.4
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 20
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.5 10
sudo apt-get install git
sudo apt-get install libboost-dev-all
sudo apt-get install libboost.*dev
sudo apt-get install autoconf automake autoproject libtool
  TODO: autoconf2.64 (2.67 config.status error?)
sudo apt-get install gfortran-4.4
sudo apt-get install flex
sudo apt-get install bison
sudo apt-get install ghostscript

apt-get remove --purge
apt-get clean
apt-get autoremove

sudo apt-get install git
sudo apt-get install libboost1.42-all-dev
sudo apt-get install g++-4.4 autoconf2.64 gfortran-4.4 libtool flex bison ghostscript
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 20
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.5 10

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.4 20
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.5 10
```

```bash
  $ ../ROSE/configure --prefix=$(pwd)/../install --with-boost=/usr --without-java
```

**Important**: disable SSH timeout

#### Shared Folder

```Ruby
  # config.vm.share_folder "name-identifier",
  #     "/path/within/your/vm", 
  #     "/path/on/your/real/machine"
  config.vm.share_folder("shared_folder", "${HOME}/shared_folder", "shared_folder", :nfs => false)
```

*Note: `NFS` is faster, but requires the host to have `nfsd` privileges.*

#### Customize VM before boot

For example, increase the VM's memory:

```Ruby
  Vagrant::Config.run do |config|
    # ..
    config.vm.customize ["modifyvm", :id, "--memory", 1024]
  end
```

## Package Management

### Ubuntu

0. Install `devscripts` to make the life of the package manager easier.

   ```bash
     $ sudo apt-get install devscripts
   ```

1. **Search**: get details (versions, etc.) of a package

   ```bash
     $ vagrant@ubuntu-11:~$ rmadison gcc
            gcc | 4:4.2.3-1ubuntu3 |         hardy | amd64, hppa, i386, ia64, lpia, powerpc, sparc
            gcc | 4:4.2.3-1ubuntu6 | hardy-updates | amd64, hppa, i386, ia64, lpia, powerpc, sparc
            gcc | 4:4.4.3-1ubuntu1 |         lucid | amd64, armel, i386, ia64, powerpc, sparc
            gcc | 4:4.5.2-1ubuntu3 |         natty | amd64, armel, i386, powerpc
            gcc | 4:4.6.1-2ubuntu5 |       oneiric | amd64, armel, i386, powerpc
            gcc | 4:4.6.3-1ubuntu5 |       precise | amd64, armel, armhf, i386, powerpc
            gcc | 4:4.7.0-5ubuntu1 |       quantal | amd64, armel, armhf, i386, powerpc
   ```

4. **Instal**l a package

   ```bash
     $ sudo apt-get install g++-4.4
   ```

5. Check contents of an installed package

   ```bash
     $ sudo apt-get install apt-file
   ```

   ```bash
     $ apt-file search g++-4.4
     distcc: /usr/lib/distcc/g++-4.4
     distcc: /usr/lib/distcc/x86_64-linux-gnu-g++-4.4
     g++-4.4: /usr/bin/g++-4.4
     g++-4.4: /usr/bin/x86_64-linux-gnu-g++-4.4
     g++-4.4: /usr/share/doc/g++-4.4
     g++-4.4: /usr/share/man/man1/g++-4.4.1.gz
     g++-4.4: /usr/share/man/man1/x86_64-linux-gnu-g++-4.4.1.gz
     g++-4.4-arm-linux-gnueabi: /usr/bin/arm-linux-gnueabi-g++-4.4
     g++-4.4-arm-linux-gnueabi: /usr/share/doc/g++-4.4-arm-linux-gnueabi
     g++-4.4-arm-linux-gnueabi: /usr/share/man/man1/arm-linux-gnueabi-g++-4.4.1.gz
     g++-4.4-multilib: /usr/share/doc/g++-4.4-multilib
     hardening-wrapper: /usr/bin/g++-4.4
   ```

6. `update-alternatives`: choose default package version

   *Reference: http://askubuntu.com/questions/26498/choose-gcc-and-g-version*

```bash
  # 1. Set `/usr/bin/gcc` to be version 4.4
  $ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 20
  update-alternatives: using /usr/bin/gcc-4.4 to provide /usr/bin/gcc (gcc) in auto mode.

  # 2. `gcc-4.5` has priority 10 which is lower than `gcc-4.4`
  $ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.5 10

  # 3. Configure alternatives
  $ sudo update-alternatives --config gcc
  There are 2 choices for the alternative gcc (providing /usr/bin/gcc).

    Selection    Path              Priority   Status
  ------------------------------------------------------------
  * 0            /usr/bin/gcc-4.4   20        auto mode
    1            /usr/bin/gcc-4.4   20        manual mode
    2            /usr/bin/gcc-4.5   10        manual mode

  Press enter to keep the current choice[*], or type selection number:
```

## Fedora

### Yum

**Commands**: http://yum.baseurl.org/wiki/YumCommands

#### How to fix the “Cannot retrieve repository metadata (repomd.xml)” error in Fedora?
http://digitizor.com/2009/06/17/how-to-fix-the-cannot-retrieve-repository-metadata-repomd-xml-error-in-fedora-11/

#### Installing older software

```bash
$ yum downgrade <pkg>
```

> [I]t is possible to install alternate versions of gcc on Fedora. Just not from packages -- you'll need the source,
> available from http://gcc.gnu.org/. Look to download gcc-4.5.3.tar.gz from one of the download mirrors.

> Download and unpack the gcc source tarball. Make sure your Fedora 16 has the packages necessary for building:

> ```bash
    $ yum install gcc mpfr-devel libmpc libmpc-devel glibc-devel
  ```
  
> Then create a new, empty build directory and build gcc with a suffix of 45 -- you'll build compilers
> `gcc45` and `g++45` for example. You might want a new, separate install directory like `/usr/local/gcc45/`

> ```bash
    $ ${GCC}/configure --prefix=/usr/local --program-suffix=45 --enable-languages=c,c++
    $ make
    $ sudo make install
  ```
  
#### `Failed to fetch <PACKAGE> Hash Sum mismatch`

```bash
  $ sudo apt-get clean
```

You could try deleting and reloading the package lists:

```bash
  $ sudo rm -rf /var/lib/apt/lists/* 
  $ sudo apt-get update
```

Change site mirror: https://wiki.ubuntu.com/Mirrors

```bash
  $ sudo vi /etc/apt/sources.list
  $ sudo apt-get update
```
