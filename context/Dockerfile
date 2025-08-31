# Global Arguments to be reused within some containers
# need to be defined without value in the image-definition
ARG wtversion=4.10-release
# ARG wtversion=4.11-release
# ARG wtversion=master
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
    dbus                 \
    curl                 \
    wget                 \
    tar                  \
    rsync                \
    iputils-ping         \
    nodejs               \
    npm                  \
    libpci3              \
    libegl1              \
    libcurl4-openssl-dev \
    libssl-dev           \
    libtinyxml2-dev      \
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
    dnsutils             \
    mc

# Installing pandoc and tools to convert README.md to pdf
RUN apt-get update       \
 && apt-get install -y   \
    pandoc               \
    texlive              \
    texlive-latex-extra

# Install rust
RUN curl https://sh.rustup.rs -sSf | RUSTUP_HOME=/opt/rust CARGO_HOME=/opt/rust bash -s -- -y
# RUN curl https://sh.rustup.rs -sSf | bash -s -- -y --no-modify-path --default-toolchain stable --profile default --prefix /opt/rust

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

RUN mkdir -p /opt/wt-source/wt-4.10-release/doc/reference/
RUN touch /opt/wt-source/wt-4.10-release/doc/reference/wt.qch
RUN cmake                                           \
    -DCMAKE_INSTALL_PREFIX=/opt/Wt4                 \
    -DWT_WRASTERIMAGE_IMPLEMENTATION=GraphicsMagick \
    -DCONNECTOR_FCGI=OFF                            \
    -DBUILD_EXAMPLES=OFF                            \
    -DENABLE_WTTEST=OFF                             \
    -DENABLE_QT4=OFF                                \
    -DENABLE_QT5=OFF                                \
    -DINSTALL_DOCUMENTATION=ON                      \
    -DENABLE_HARU=TRUE                              \
    ..
RUN make -j4
RUN make install

#
# Install GUI type utilities
#
FROM wt-compiled AS firefox
RUN apt-get update       \
 && apt-get install -y   \
#    dbus                 \
    x11-apps             \
    libgtk-3-0           \
    libdbus-glib-1-2     \
    libxt6               \
    libxss1              \
    libnss3              \
    libasound2           \
    libpci3              \
    libegl1              \
 && apt clean

# Download Firefox from Mozilla (not Snap!)

ENV DEBIAN_FRONTEND=noninteractive
ENV FIREFOX_VERSION=latest

RUN wget -O /tmp/firefox.tar.xz "https://download.mozilla.org/?product=firefox-${FIREFOX_VERSION}&os=linux64&lang=en-US"
RUN tar -xf /tmp/firefox.tar.xz -C /opt/
RUN ln -s /opt/firefox/firefox /usr/bin/firefox

#
# stuff a console prompt that will cause the prompt to
#  indicate that this is running from a container
#
RUN /bin/bash -c "echo \"PS1='${debian_chroot:+($debian_chroot)}\[\033[01;31m\]\u@\h(docker)\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '\" >> /root/.bashrc "

RUN ldconfig

COPY root /

RUN ln -s /opt/dev-essential/devess.sh /bin/devess

WORKDIR /

