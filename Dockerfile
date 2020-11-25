# Instead of building the application directly in your host,
# alternatively you may find simpler to test it in a container.
# Here are the steps for any Linux with a X11 graphical environment:
#
# 1. Install docker:
# $ apt-get install docker
#
# 2. Build a container with the galton_board application:
# $ docker build -t galton_board .
#
# 3. Run the container:
# $ setfacl -m user:1000:r ${HOME}/.Xauthority
# $ docker run --rm -it -v ${HOME}/.Xauthority:/home/user/.Xauthority --net=host -e DISPLAY galton_board
#

FROM ubuntu:focal as base
RUN apt-get --yes --no-upgrade update
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get --yes --no-upgrade --no-install-recommends install apt-utils
RUN apt-get --yes --no-upgrade --no-install-recommends install libgtkmm-3.0

FROM base as builder
RUN apt-get --yes --no-upgrade --no-install-recommends install autoconf automake libtool g++ make autoconf-archive
RUN apt-get --yes --no-upgrade --no-install-recommends install libgtkmm-3.0-dev
ADD autosetup.sh configure.ac LICENSE main.cpp Makefile.am README.md src /root/build/
ADD src /root/build/src/
WORKDIR /root/build
RUN ./autosetup.sh
RUN ./configure
RUN make

FROM base as runner
RUN useradd -m -u 1000 -s /bin/bash user
COPY --from=builder /root/build/galton_board /home/user/
RUN chown -R user:user /home/user/galton_board
USER user
WORKDIR /home/user
CMD /home/user/galton_board
