set -x

#
# build the docker image
#  'add no-cache to rebuild all'
#
rsync -avhq  LICENSE      context/root/opt/dev-essential/
rsync -avhq  README.md    context/root/opt/dev-essential/
rsync -avhq  attach.sh    context/root/opt/dev-essential/
rsync -avhq  build.sh     context/root/opt/dev-essential/
rsync -avhq  load.sh      context/root/opt/dev-essential/
rsync -avhq  run.sh       context/root/opt/dev-essential/
rsync -avhq  save.sh      context/root/opt/dev-essential/

echo "building docker dev-essential image"
date > context/root/.buildtime
# docker build -t="dev-essential:1" --no-cache context
docker build -t="dev-essential:1" context

#
# run the docker
#
echo "TO RUN: docker run -it dev-essential"

