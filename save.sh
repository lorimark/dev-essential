#
# This will export the image to a .gz file for transport
#  to another pc.  The .gz file can be moved to a new pc
#  also running docker and installed using the load.sh
#  script.
#
#
docker save dev-essential:1 | gzip > dev-essential.tar.gz

