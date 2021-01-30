FROM debian:latest AS base
RUN apt update \
    && apt upgrade -y --no-install-recommends \
    && apt install -y --no-install-recommends \
        apt-transport-https \
        ca-certificates \
        wget \
        gnupg \
    && echo "deb https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/Debian_10/ ./" >> /etc/apt/sources.list \
    && wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/Debian_10/Release.key -O- | apt-key add \
    && apt update \
    && apt install -y --no-install-recommends \
        libzmq3-dev  \
        libcapnp-dev \
    && apt purge -y \
        wget \
        gnupg \
    && apt autoremove -y \
    && apt autoclean -y \
    && rm -rf /var/lib/apt/lists/* \
    && useradd -m monitor

FROM base AS build
RUN apt update \
    && apt install -y --no-install-recommends \
        build-essential \
        capnproto \
        pkg-config \
        cmake \
        python3 \
        python3-pip \
        python3-setuptools \
    && pip3 install --upgrade --no-cache-dir \
        pip \
        setuptools \
        conan \
    && conan profile new default --detect \
    && conan profile update settings.compiler=gcc default \
    && conan profile update settings.compiler.libcxx=libstdc++11 default \
    && conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
WORKDIR /opt/build
COPY . /opt/build
RUN cmake . && make

FROM base
COPY --chown=monitor:monitor --from=build /opt/build/task-allocation-monitor /usr/bin/
COPY --chown=monitor:monitor --from=homeserver:5000/thesis/alica-messages-client:latest /usr/bin/alica-messages-client /usr/bin/
USER monitor
CMD ["bash"]