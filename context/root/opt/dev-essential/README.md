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
    - [.bashrc hook](#bashrc)
<!-- /TOC -->

<a name="introduction"></a>
## Introduction
This is my dev-kit which includes every dev toolchain I normally use including
 configured editors. It is intended to be run as a docker container, hooked in to
 the terminal, offering all the dev tools and editors, without having to install
 everything on a host computer.

This project includes all the gcc build stuff along with scripts for launching
 the container on a machine and hooking it in to the OS such that the running
 container is recognized as the local user. This makes installing/setting-up/running
 a development environment a breeze.

The 'context' folder here contains all the parts that are going to be stuffed in to the
 docker image, including any extra files or source projects, anything useful for dev
 work. So, note that if the image is to be rebuilt, there may be some componentry in
 the context folder that may need to be upgraded or updated or added or removed or
 whatever.  It's just the place to put all the extra stuff I want at my fingertips
 when developing.

<a name="bashrc"></a>
## Hooking .bashrc
This can be hooked in to the users local .bashrc file to cause the prompt
 to be improved indicating when the user is operating in the container.

Add the following line to your local user .bashrc file;

`[ -f "/.bashrc_container" ] && source "/.bashrc_container"`

This will check if there is a `/.bashrc_container` file available in the root folder,
 and if there is, it will process it in to the bash environment.  The purpose is to
 modify the prompt to include information about the running container.


