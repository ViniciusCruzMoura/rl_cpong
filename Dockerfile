FROM ubuntu:22.04 as build

RUN apt -y update \
    && apt -y install build-essential \
        gcc \
        git \
        cmake \
        libasound2-dev \
        libx11-dev \
        libxrandr-dev \
        libxi-dev \
        libgl1-mesa-dev \
        libglu1-mesa-dev \
        libxcursor-dev \
        libxinerama-dev \
        libwayland-dev \
        libxkbcommon-dev
RUN git clone --depth 1 https://github.com/raysan5/raylib.git raylib \
    && cd raylib/src/ \
    && make PLATFORM=PLATFORM_DESKTOP \
    && make install \
    && cd ../../ \
    && rm -rf raylib/

CMD echo 'usage: ./build.sh'
