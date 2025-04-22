#
# This runs the container, hooking it in to
#  the local file system for logging and other things.
#
# NOTE: it is possible to hook the local user .bashrc
#        file such that when this image is launched,
#        the local .bashrc will get processed and the
#        console prompt will be modified to clearly
#        indicate we are inside a container;
#
# add this to your .bashrc
## if test -f /.dockerenv; then
##   if test -f /.containername; then
##     PS1="D:$(cat /.containername)-> $PS1"
##   fi
##   if test -f /.containerinfo; then
##    cat /.containerinfo
##   fi
## fi

docker run                             \
  -it                                  \
  --rm                                 \
  --net host                           \
  -u $(id -u ${USER}):$(id -g ${USER}) \
  -v /etc/passwd:/etc/passwd           \
  -v /etc/group:/etc/group             \
  -v /home:/home                       \
  -v /mnt:/mnt                         \
  -e "TERM=xterm-256color"             \
  -w $(pwd)                            \
  dev-essential:1

