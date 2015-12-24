# Teonet application template

## Fork project

Fork and rename this project to create your own Teonet Application.

## Change application name

Rename the ```teomet-tmpl``` to ```your-application-name``` 
and ```teomet_tmpl``` to ```your_application_name``` in files:

    configure.ac
    MakeFile.am
    src/MakeFile.am

## Generate your application sources (first time when got sources from repository)

    ./autogen.sh

## Install Teonet library from repositories

DEB / RPM repository: http://repo.ksproject.org

### UBUNTU

http://repo.ksproject.org/ubuntu/

#### Add repository

sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 8CC88F3BE7D6113C
sudo apt-get install -y software-properties-common
sudo add-apt-repository "deb http://repo.ksproject.org/ubuntu/ teonet main"
sudo apt-get update

#### Install

sudo apt-get install -y libteonet-dev


### CENTOS / RHEL / FEDORA

http://repo.ksproject.org/rhel/x86_64/

#### Add repository

    vi /etc/yum.repos.d/teonet.repo

    [teonet]
    name=Teonet library for RHEL / CentOS / Fedora
    baseurl=http://repo.ksproject.org/rhel/x86_64/
    enabled=1
    gpgcheck=0

#### Refresh

    # yum clean all

#### Install

    yum install libteonet
    ldconfig 


## Make your application 

    make