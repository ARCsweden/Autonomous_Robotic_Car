# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

# Set up ROS2 repo
RUN apt update && apt install -y \
    software-properties-common \
    curl \
    && rm -rf /var/lib/apt/lists/*
RUN add-apt-repository universe

# Add GPG key
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
    -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Upgrade Ubuntu
RUN apt update && apt upgrade -y \
    && rm -rf /var/lib/apt/lists/*

# Install ROS2 (Iron Irwini)
RUN apt update && apt install -y \
    ros-dev-tools \
    ros-iron-desktop \
    && rm -rf /var/lib/apt/lists/*
