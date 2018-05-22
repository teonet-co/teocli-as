# TeocliAS application

## 1. Description


## 2. Installation

## Clone git repository  to get code
    git clone git@github.com:teonet-co/TeocliAS.git
    cd TeocliAS
    git submodule update --init


## 2.1 Install Teonet library from repositories

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

### SUSE

#### Add repository

    zypper ar -f http://repo.ksproject.org/opensuse/x86_64/ teonet

#### Install
    
    zypper in -y libteonet
    ldconfig

## 2.2 AngelScript Sources Installation

Download AngelScript sources from official web site: http://www.angelcode.com/angelscript/downloads.html  
or  
Get the AngelScript sources from this project dist folder.  
  
Unzip source folder archive to $PROJECT_HOME/../angelscript folder  
  
Run make:  

    cd $PROJECT_HOME/../angelscript/sdk/angelscript/projects/gnuc
    make

## 3. Generate your application sources (first time when got sources from repository)

    ./autogen.sh

## 3.1. Using autoscan to Create configure.ac

Use [autoscan](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/html_node/autoscan-Invocation.html)
to update (or create new one) projects configure.ac

## 4. Make your application 

    make

## 5. Run 
    
    cd src
    ./teocli_as 

The applications output looks like this:   
```
Teocli AngelScript ver 0.0.1

===========
Executing function 'void main()' of the script.
---
Hello world!
main: System has been running for 1.20452e+06.113 seconds
---
The script finished successfully.

===========
Executing function 'float calc(float, float)' of the script.
---
Received: 3.14159, 2.71828
calc: System has been running for 1.20452e+06.113 seconds
---
The script function returned: 8.53973

Press any key to quit.
```
