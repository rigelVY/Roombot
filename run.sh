#!/bin/bash

#ラズパイとPCをROSで連携させるための設定
#export ROS_IP=`hostname -I`
#export ROS_MASTER_URI=http://192.168.11.14:11311/

#USBの権限がない場合に使用
#sudo chmod a+rw /dev/ttyUSB0


# realsense D435iのセンサデータ出力用launchファイルとroombot_driverのlaunchファイルを実行
gnome-terminal -e "bash -c 'source /opt/ros/kinetic/setup.bash; source ~/ROS_ws/catkin_ws/devel/setup.bash; roslaunch realsense2_camera rs_camera.launch'"
sleep 3s

gnome-terminal -e "bash -c 'source /opt/ros/kinetic/setup.bash; source ~/ROS_ws/Roombot/devel/setup.bash; roslaunch roombot_gazebo move_roombot.launch joy:=true'"