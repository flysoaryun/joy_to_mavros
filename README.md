# joy_to_mavros
This package can transform the joy messages to mavros rc messages and I have already tested it in TBS TANGO remote control. If your use other remote control, you may chage the config/joy.yaml.

1、Build 

Clone the repository and catkin_make(**Ubuntu20.04**):
```
    sudo apt install ros-noetic-joy ros-noetic-mavos ros-noetic-mavros-extras
    cd ~/catkin_ws/src
    git clone https://github.com/flysoaryun/joy_to_mavros.git
    cd ../
    catkin_make
    source ~/catkin_ws/devel/setup.bash
```
---

2、Run
```
    roslaunch joy_to_mavros joy.launch
```
---

