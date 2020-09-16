FROM debian:latest

WORKDIR /opt/task-allocation-monitor
COPY ./build /opt/task-allocation-monitor

RUN apt update \
    && apt install -y \
    wget \
    gnupg \
    && echo "deb https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/Debian_10/ ./" >> /etc/apt/sources.list \
    && wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/Debian_10/Release.key -O- | apt-key add \
    && apt update \
    && apt install -y \
    libzmq3-dev  \
    libcapnp-dev \
    && mv /opt/task-allocation-monitor/task-allocation-monitor /usr/bin/ \
    && useradd -m monitor \
    && apt remove -y \
    wget \
    gnupg\
    && apt autoremove -y \
    && apt autoclean -y \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /opt/task-allocation-monitor

USER monitor

CMD ["bash"]