# ROS basics

The ARC will use ROS2 (Robotic Operating System) as the framework for internal communication and building up structure between different functions.

The specific version of ROS2 we use is Galactic, which is available for Ubuntu 20.04. For instructions on how to install, tutorials and guides, see: https://docs.ros.org/en/galactic/index.html

## Installation

Follow the instructions in the documentation to install ROS2. The easiest is to use Ubuntu 20.04 and install from binary packages (https://docs.ros.org/en/galactic/Installation/Ubuntu-Install-Debians.html#setup-sources and onwards).

Make sure to add `source /opt/ros/galactic/setup.bash` to your `~/.bashrc` to set up the ROS2 environment automatically. Your ROS2 installation can be verified with these commands:

```
$ env | grep -i ros
ROS_VERSION=2
ROS_PYTHON_VERSION=3
ROS_DISTRO=galactic
```

## Getting started

It's recommended to go through the basic tutorials if you are new to ROS: https://docs.ros.org/en/galactic/Tutorials.html

# Working with nodes in ROS

The primary programming languages supported by ROS2 are C++ and Python. A system can be built from collections of nodes written in either langauge, where each node is a separate process that communicate through the use of topics.

## Interprocess communication

ROS2 uses a publish-subcribe protocol called DDS. It communications information between nodes over sockets. Every node can publish information on a number of topics (a data channel with a defined type and name). Multiple nodes can publish to the same topic, and multiple nodes can subscribe and read information from a given topic.

Examples of topics can be a velocity, a position/direction, or something as complex as a pointcloud from a depth camera.

Topics can be put in namespaces, so you can have multiple topics with the same name, but collected under a namespace. Example: `/motor_L/speed` and `/motor_R/speed`.

Two other mechanisms of communication are used: services and actions. Look through the tutorials to find out which one fits the best in a given situation. In general:

* Topics are channels for streaming a specific type of data.
* Services are one-time call, and can be seen as remote function calls.
* Actions are collections of topics that can be used to monitor the status of an ongoing operation.


## Organizing your project

As the number of ROS nodes in your project grows, it can be a good idea to use some features of ROS2:

* Use predefined datatypes for topics. ROS2 is intended for Robotics, so many useful datatypes and even nodes are already present in the default installation.
* Use ros-launch files to set up a hierarchy of nodes, so your project can be run with a single command. The launch files can set up nodes and configure namespaces/topics in a simple manner.
* Make use of the inspection tools of ROS2: rqt, rviz, rosbag etc. Seeing a graph of what topics are present in your system, which nodes publish/subscribe to them and what data flows through the system can greatly speed up debugging in complex systems.
* ROS nodes and datatypes are organized in ROS packages. Split up your project in multiple reusable packages.
* Instead of using raw print statements for debugging your nodes, use the ROS logger functionality. It allows for getting a timestamped log where all events in the system, regardless of what node caused them, can be collected.

## Optimizing your project

ROS will send data between different nodes using the network. If you are only on the local computer, this will be pretty fast, but it can still introduce some performance issue since the data of large topics still needs to be copied between processes.

ROS2 has a concept called nodelets, which is a collection of c++ ROS nodes that execute as a single process, making the calling of topics as lightweight as calling a function/passing around a pointer. If the project has a lot of latency due to huge amounts of data being passed around, this can be a potential way to speed things up.

## Creating packages

ROS2 has multiple package build methods. The recommended build types are `ament_cmake` and `ament_python`. To create a new template-based package, run `ros2 pkg create`.

## Building packages

ROS2 uses the package builder `colcon`. First start by ensuring that ROS2 itself is sourced. Invoke the build with the command:

```
colcon build --symlink-install
```

This will elaborate the contents of the `src` directory and generate the `build`, `install` and `log` directories.

To run any tests associated with the package, run:

```
colcon test
```

A package overlay that has been built can be sourced with:

```
. install/setup.bash
```

