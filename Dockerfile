FROM debian:12
RUN apt-get update && apt-get install -y \
    ca-certificates \
    make \
    g++ \
    && rm -rf /var/lib/apt/lists/*
COPY programm_1.0_all.deb /app/programm_1.0_all.deb
COPY main.cpp /app/main.cpp
COPY Makefile /app/Makefile
RUN dpkg -i /app/programm_1.0_all.deb || \
    (apt-get update && apt-get install -f -y && dpkg -i /app/programm_1.0_all.deb)
RUN rm /app/programm_1.0_all.deb
WORKDIR /app


