# Use a lightweight Ubuntu image
FROM ubuntu:20.04

RUN sed -i 's/http:\/\/archive.ubuntu.com/http:\/\/mirror.ubuntu.com\/mirror/' /etc/apt/sources.list

# Install necessary tools
RUN apt-get update && apt-get install -y \
    valgrind \
    gdb \
    clang \
    make \
    vim \
    && rm -rf /var/lib/apt/lists/* \

# Set the working directory in the container
WORKDIR /workspace

# Entry point to run the bash shell
ENTRYPOINT ["/bin/bash"]
