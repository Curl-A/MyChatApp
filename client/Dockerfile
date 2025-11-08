FROM ubuntu:22.04

RUN apt update && apt install build-essential

WORKDIR /app

COPY client/client.cpp .

COPY Logger/Logger.cpp .

COPY Logger/Logger.h .

RUN g++ -g client.cpp Logger.cpp -o client

CMD ["./client"]
