FROM ubuntu:focal
RUN apt-get --yes --no-upgrade update
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get --yes --no-upgrade --no-install-recommends install apt-utils
RUN apt-get --yes --no-upgrade --no-install-recommends install autoconf  automake libtool g++ make
RUN apt-get --yes --no-upgrade --no-install-recommends install libgtkmm-3.0-dev
RUN apt-get --yes --no-upgrade --no-install-recommends install x11-apps
RUN apt-get --yes --no-upgrade --no-install-recommends install autoconf-archive
RUN useradd -m -u 1000 -s /bin/bash user
ADD . /home/user/galton-board
RUN chown -R user:user /home/user/galton-board
USER user
WORKDIR /home/user/galton-board
RUN ./autosetup.sh
RUN ./configure
RUN make -j2
ENTRYPOINT ["/bin/sh", "-c", "$0 \"$@\"", "/home/user/galton-board/galton_board"]
