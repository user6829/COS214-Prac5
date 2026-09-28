FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Configure apt timeouts and install only strictly needed tools
RUN echo 'Acquire::Retries "3";' > /etc/apt/apt.conf.d/80-retries \
    && echo 'Acquire::http::Timeout "20";' >> /etc/apt/apt.conf.d/80-retries \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
       g++ \
       make \
       valgrind \
       gdb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy project files
COPY . .

# Build the project
RUN make clean && make

CMD ["./main"]