
# Installing pre-requisistes
```bash
sudo apt install docker.io docker-compose
sudo usermod -a -G docker $USER
```

# Building
```bash
docker-compose build
```

# Running (interactive console)
```bash
docker-compose up --d
docker-compose exec ros2 bash
```

Can now interact with the external (persistent) filesystem in the `/data` directory (the current directory is mounted).

Do the following in the image to get started (builds the `cpp_test` package in the ARC repo):

```bash
. /opt/ros/iron/setup.bash
cd /data

colcon build --symlink-install
. install/setup.bash

ros2 run cpp_test listener&
ros2 run cpp_test talker&
```
