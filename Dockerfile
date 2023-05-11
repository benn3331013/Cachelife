FROM ubuntu:22.04

RUN apt-get update && apt-get install -y build-essential \
    make \
    libgmp-dev \
    libsdl2-dev \
    && rm -rf /var/lib/apt/lists/*

COPY src /Cachelife/src
COPY include /Cachelife/include
COPY main.c /Cachelife
COPY Makefile /Cachelife

WORKDIR /Cachelife
