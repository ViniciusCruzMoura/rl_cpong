FROM ubuntu:22.04 as build

COPY configure.sh .
RUN ./configure.sh

CMD echo 'usage: ./build.sh run'
