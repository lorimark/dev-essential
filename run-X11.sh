#
# This runs the container, hooking it in to
#  the local file system for logging and other things.
#
# This includes support for X11 display applications
#

docker run                             \
  -it                                  \
  --rm                                 \
  --env DISPLAY=$DISPLAY               \
  --env XAUTHORITY=$XAUTHORITY         \
  --net host                           \
  -u $(id -u ${USER}):$(id -g ${USER}) \
  -v /tmp/.X11-unix:/tmp/.X11-unix     \
  -v $XAUTHORITY:$XAUTHORITY           \
  -v /etc/passwd:/etc/passwd           \
  -v /etc/group:/etc/group             \
  -v /home:/home                       \
  -v /mnt:/mnt                         \
  -e "TERM=xterm-256color"             \
  -w $(pwd)                            \
  dev-essential:1

