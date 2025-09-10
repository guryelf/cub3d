# Use Ubuntu 22.04 as base image
FROM ubuntu:22.04

# Install dependencies: build tools, X11, and MLX requirements
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    libx11-dev \
    libxext-dev \
    libbsd-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /cub3d

# Copy project files
COPY src/ src/
COPY include/ include/
COPY libft/ libft/
COPY minilibx-linux/ minilibx-linux/
COPY Makefile .
COPY map.cub .

# Build libft and minilibx-linux
RUN make -C libft
RUN make -C minilibx-linux

# Build the project
RUN make

# Set environment for X11 forwarding
ENV DISPLAY=host.docker.internal:0

# Default command: run cub3d with map.cub
CMD ["./cub3d", "map.cub"]