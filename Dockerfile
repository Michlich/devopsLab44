FROM debian:bookworm-slim
# Только самое базовое
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    wget \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN make
EXPOSE 8080 8081
CMD ["./programm"]
