FROM ubuntu:22.04

RUN apt update && apt install -y build-essential

COPY Server/server.cpp .

COPY Logger/Logger.cpp .

COPY Logger/Logger.h .

RUN g++ -g server.cpp Logger.cpp -o server

CMD ["./server"]
