# dev-essential
This is my dev-kit which includes every dev
 toolchain I normally use including configured
 editors.  It is intended to be run as a docker
 container, hooked in to the terminal, offering
 all the dev tools and editors, without having
 to install everything on a host computer.

This project includes all the gcc build stuff
 along with scripts for launching the container
 on a machine and hooking it in to the OS such
 that the running container is recognized as the
 local user.  This makes installing/setting-up/running
 a development environment a breeze.

The 'context' folder here contains all the parts
 that are going to be stuffed in to the docker
 image, including any extra files or source
 projects, anything useful for dev work. So, note
 that if the image is to be rebuilt, there may be
 some componentry in the context folder that may
 need to be upgraded or updated or added or removed
 or whatever.  It's just the place to put all the
 extra stuff I want at my fingertips when developing.

