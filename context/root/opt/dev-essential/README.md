<!--
Copyright @ 2025 Lorimark Solutions, LLC.  All Rights Reserved

This Source Code Form is subject to the terms of the Mozilla
Public License, v. 2.0. If a copy of the MPL was not distributed
with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
-->

<a name="dev-essential"></a>
# dev-essential

<!-- TOC -->
- [dev essential](#dev-essential)
    - [Introduction](#introduction)
    - [Running the Container](#running)
    - [.bashrc hook](#bashrc)
<!-- /TOC -->

<a name="introduction"></a>
## Introduction
This is my dev-kit which includes every dev toolchain I normally use including
 configured editors, compilers, networking management tools, inspection and
 debugger tools, and anything else that might require some sort of host installation
 before I am able to use it.. It is intended to be run as a docker container, hooked
 in to the terminal, offering all the dev tools and editors, without having to install
 everything on a host computer.

The 'context' folder here contains all the parts that are going to be stuffed in to the
 docker image, including any extra files or source projects, anything useful for dev
 work. So note that, if the image is to be rebuilt, there may be some componentry in
 the context folder that may need to be upgraded or updated or added or removed or
 whatever.  The context folder is just the place to put all the extra stuff I want
 at my fingertips when developing.

<a name="running"></a>
## Running the container
The container can be started with a simple 'docker run';

```bash
docker run -it dev-essential
```

This will place you in to the root of the running container.  You can then enter the
 `/opt/dev-essential` folder to access some of the scripts and other useful
 tools parked in there;

```bash
mark@ubuntu24.04:~/projects/dev-essential$ docker run -it --rm dev-essential:1
root@a145f069b115(docker):/$ cd /opt/dev-essential/
root@a145f069b115(docker):/opt/dev-essential$ ll
total 56
drwxrwxr-x 2 root root  4096 Jun  9 09:36 ./
drwxrwxr-x 1 root root  4096 Apr 20 15:47 ../
-rw-rw-r-- 1 root root 11357 Apr 20 11:35 LICENSE
-rw-rw-r-- 1 root root  2033 Jun  9 09:35 README.md   <-- the file you're reading now
-rwxrw-r-- 1 root root   108 Jul 12  2024 attach.sh*  <-- attach to a running container
-rwxrwxr-x 1 root root   715 Jun  9 09:30 build.sh*   <-- build the container
-rwxrwxr-x 1 root root    71 Jun  9 09:29 devess.sh*  <-- script to run once container is running
-rw-r--r-- 1 root root    49 Jun  9 09:29 devess.txt  <-- text for script that's run once container is running
-rwxrwxr-x 1 root root    36 Apr 20 11:46 load.sh*    <-- load an image saved to a .tar.gz file
-rwxrwxr-x 1 root root   947 Apr 22 11:36 run.sh*     <-- run the image with suitable command-line options
-rwxrwxr-x 1 root root    59 Apr 20 11:46 save.sh*    <-- save the image to a .tar.gz to transport to another pc
root@a145f069b115(docker):/opt/dev-essential$
```

In the `/opt/dev-essential` folder are a handful of scripts for loading and running
 and building the container, including attaching to a running container.

The `run.sh` script is normally the script that should be used to launch the container.
 This script has all the necessary hooks to cause the container to run with
 user-level information, and the ability to navigate around the host computer from
 within the container.  This faciliates the launching of the container and allowing
 the user to compile the project on the local host, seemlessly integrating all of the
 compiler tools as if the user were still running within the host machine.

```bash
docker run                             \ <-- run the container
  -it                                  \ <-- leave in terminal mode
  --rm                                 \ <-- remove the container after exit
  --net host                           \ <-- grant access to the host services
  -u $(id -u ${USER}):$(id -g ${USER}) \ <-- set .this. {user} and {group} values
  -v /etc/passwd:/etc/passwd           \ <-- hook `passwd` so we can have the user name
  -v /etc/group:/etc/group             \ <-- hook `group` so we can have group info
  -v /home:/home                       \ <-- map the 'home' folder so we can move freely
  -v /mnt:/mnt                         \ <-- map the `mnt` folder so we can move freely
  -e "TERM=xterm-256color"             \ <-- helps with some of the editor display encoding
  -w $(pwd)                            \ <-- move to the current directory automatically
  dev-essential:1                        <-- give the container name
```



<a name="bashrc"></a>
## Hooking .bashrc
This can be hooked in to the users local .bashrc file to cause the prompt
 to be improved indicating when the user is operating in the container.

Add the following line to your local user .bashrc file;

`[ -f "/.bashrc_container" ] && source "/.bashrc_container"`

This will check if there is a `/.bashrc_container` file available in the root folder,
 and if there is, it will process it in to the bash environment.  The purpose is to
 modify the prompt to include information about the running container.


