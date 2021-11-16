FROM ubuntu:20.04

# install OS basics
# do a quiet update and accept all installs
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y \
           g++ cmake libglew-dev libopenal-dev libsdl2-dev \
    && apt-get autoremove \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
