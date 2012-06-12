sysadmin
========

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

