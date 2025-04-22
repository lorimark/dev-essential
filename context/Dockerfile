# Global Arguments to be reused within some containers
# need to be defined without value in the image-definition
# ARG wtversion=4.10-release
ARG wtversion=master
ARG projectname=WtApplication.wt

# Using a baseimage to set the same in compiling-container as well as runtime-container
# FROM ubuntu:22.04 AS baseimage (might try expirimenting with different versions, 'ubuntu' doesn't work)
FROM ubuntu:22.04 AS baseimage

FROM baseimage AS baseessential

LABEL maintainer="Mark Petryk <mark@lorimarksolutions.com>"

RUN export DEBIAN_FRONTEND=noninteractive

#RUN sed -i -e 's/^APT/# APT/' -e 's/^DPkg/# DPkg/' \
#      /etc/apt/apt.conf.d/docker-clean

# Get started with the build
RUN apt-get update                                            \
 && apt-get install tzdata -y                                 \
 && ln -fs /usr/share/zoneinfo/America/Chicago /etc/localtime \
 && dpkg-reconfigure --frontend noninteractive tzdata

# Installing build essentials
RUN apt-get update       \
 && apt-get install -y   \
    build-essential      \
    curl                 \
    libcurl4-openssl-dev \
    tzdata               \
    cmake                \
    gcc                  \
    git                  \
    lynx                 \
    gdb                  \
    doxygen              \
    graphviz             \
    vim                  \
    sqlite3              \
    mc

# Install Howard Hinnant's date library
RUN git clone https://github.com/HowardHinnant/date.git /opt/date \
 && cd /opt/date                                                  \
 && mkdir build                                                   \
 && cd build                                                      \
 && cmake -DBUILD_TZ_LIB=ON -DCMAKE_INSTALL_PREFIX=/usr/local ..  \
 && make -j$(nproc)                                               \
 && make install

FROM baseessential AS essentials
# Installing Wt-Essentials
RUN apt-get update     \
 && apt-get install -y \
    libboost-all-dev

FROM essentials AS optionals
# Installing Optionals, Using Multiline with \
# Both dev and release packages are listed
# Release Package needs to be installed in the runtime container
RUN apt-get update     \
 && apt-get install -y \
 # OpenSSL, which is used to support the HTTPS protocol in the web client,
 # and the HTTPS protocol in the built-in wthttpd connector.
 # Also for other things in Auth
 # As The App will be behind a reverse proxy within the docker network
 # this is not really relevant
 # openssl=1.1.* \
 # libssl-dev=1.1.1* \
 # Haru Free PDF Library, which is used to provide support for painting to PDF (WPdfImage)
 # libhpdf-2.3.* \
   libhpdf-dev=2.3.0* \
 # GraphicsMagick, for supporting painting to raster images (PNG, GIF, ...) (WRasterImage)
   libgraphicsmagick++1-dev \
 # graphicsmagick=1.4* \
 # Pango, for improved font support in the WPdfImage and WRasterImage paint devices.
 # libpangoft2-1.0-0=1.42.* \
 # libpango1.0-dev=1.42.* \
   libpango1.0-dev \
 # PostgreSQL, for the PostgreSQL backend for Wt::Dbo (Dbo::backend::Postgres).
 # Only Dev Libs neccesary for building Wt
 # libpq-dev=11.5* \
   libpq-dev \
 # LibZ for Compressing
 # zliblg=1:1.2.11*
   zlib1g-dev=1:1.2.11* \
 # OpenGL for 2D and or 3D Rendering? There is no information about it in current Install ReadMe
 # Compiling needs dev Package
 # libglu1-mesa=9.0.0* \
 # libglu1-mesa-dev=9.0.0*
   libglu1-mesa-dev
 # Firebird, for the Firebird backend for Wt::Dbo (Dbo::backend::Firebird).
 # No Experience here
 # firebird-dev \
 # the C API for MySQL (mysqlclient), or the MariaDB connector library, 
 # for the MySQL/MariaDB backend for Wt::Dbo (Dbo::backend::MySQL).
 # No Experience here
 # libmariadb-dev \
 # unixODBC, for the SQL Server backend for Wt::Dbo (Dbo::backend::MSSQLServer).
 # No Experience here
 # unixodbc=2.3.6* \
 # libunwind, for the saving of backtraces in exceptions (useful for debugging).
 # No Experience here
 # libunwind-dev=1.2.1*

FROM optionals AS wt-source
ARG wtversion
ENV WT_Version=${wtversion}
WORKDIR /opt/wt-source
RUN git clone --single-branch --branch ${WT_Version} https://github.com/emweb/wt.git wt-${WT_Version}

FROM wt-source AS wt-compiled
ARG wtversion
ENV WT_Version=${wtversion}
WORKDIR /opt/wt-source/wt-${WT_Version}/build

#
# To set up Wt build environment
#
# 1. install build tools;
#      build-essential
#      cmake
#      libboost-all-dev
#      doxygen
#      imagemagick
#      php5-imagick
#      graphicsmagick
#      libssl-dev
#      libgraphicsmagick++1-dev
#      libhpdf-dev
#      libpango1.0-dev
#      libghc-openglraw-dev
#      libpqxx3-dev
#      freeglut3-dev
#
# 2. install and build wt
#      mkdir ~/projects/wt
#      cd ~/projects
#      git clone git://github.com/kdeforche/wt.git
#      cd wt
#      mkdir build
#      cd build
#  -DCMAKE_BUILD_TYPE=Debug \
RUN cmake                                           \
    -DCMAKE_INSTALL_PREFIX=/opt/Wt4                 \
    -DWT_WRASTERIMAGE_IMPLEMENTATION=GraphicsMagick \
    -DCONNECTOR_FCGI=OFF                            \
    -DBUILD_EXAMPLES=OFF                            \
    -DENABLE_WTTEST=OFF                             \
    -DENABLE_QT4=OFF                                \
    -DENABLE_QT5=OFF                                \
    -DENABLE_HARU=TRUE                              \
    ..
RUN make -j4
RUN make install

#
# stuff a console prompt that will cause the prompt to
#  indicate that this is running from a container
#
run /bin/bash -c "echo \"PS1='${debian_chroot:+($debian_chroot)}\[\033[01;31m\]\u@\h(docker)\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '\" >> /root/.bashrc "

RUN ldconfig

COPY root /

# The following is a code snip that can be added to the
#  host machine .bashrc file.  When this docker image
#  is launched, it will process the local user .bashrc
#  file and pick up this modified prompt.
##
## If running ~inside~ a docker container, and if there is a
##  containername file, include this file on the prompt
##
#if test -f /.dockerenv; then
#  if test -f /.containername; then
#    PS1="D:$(cat /.containername)-> $PS1"
#  fi
#  if test -f /.containerinfo; then
#    cat /.containerinfo
#  fi
#fi


# FROM baseimage AS wt-runtime
# # Install all the libraries from the top, but not the dev Package
# RUN apt-get update                 \
#  && apt-get install -y             \
#     libboost-thread1.71.0          \
#     libboost-program-options1.71.0 \
#     libboost-filesystem1.71.0      \
#     libhpdf-2.3.0=2.3.0*           \
#     graphicsmagick=1.4*            \
#     libpangoft2-1.0-0              \
#     libpq5                         \
#     libglu1-mesa                   \
#     zlib1g=1:1.2.11*
# 
# ARG wtversion
# ENV WT_Version ${wtversion}
# COPY --from=wt-compiled /home/wt-source/wt-${WT_Version}/resources /home/docroot/resources
# COPY --from=wt-compiled /usr/local/lib /usr/local/lib




# 
# FROM wt-compiled AS project-build
# #CMAKE Executable Name to run
# ARG projectname
# COPY Wt-Project /home/wt-project/
# RUN chmod +x /home/wt-project/startScript.sh
# WORKDIR /home/wt-project/build
# RUN cmake ../
# RUN make -j4 
# RUN mkdir -p /home/app  \
#     && mv /home/wt-project/build/source/${projectname} /home/app/ \
#     && mv /home/wt-project/startScript.sh /home/app/
# 
# 
# FROM wt-runtime AS application
# ARG projectname
# # Project_Name is used in startScript.sh
# ENV Project_Name=$projectname
# COPY Wt/wt_config.xml /home/
# COPY --from=project-build /home/app /home/
# COPY Wt-Project/approot /home/approot
# COPY Wt-Project/docroot /home/docroot
# COPY Wt/Bootstrap_Additions/ /home/docroot/resources/
# ENTRYPOINT [ "/home/startScript.sh" ]

