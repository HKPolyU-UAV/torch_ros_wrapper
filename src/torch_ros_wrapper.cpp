/*
    This file is part of torch_ros_wrapper - the non-robocentric dynamic landing system for quadrotor

    torch_ros_wrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    torch_ros_wrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with torch_ros_wrapper.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * \file torch_ros_wrapper.cpp
 * \date 07/12/2023
 * \author pattylo
 * \copyright (c) AIRO-LAB, RCUAS of Hong Kong Polytechnic University
 * \brief classes for vision-based relative localization for UAV and UGV based on LED markers
 */

#include "include/torch_ros_wrapper.h"

void torch_ros::torch_ros_wrapperNodelet::sub_msg_callback(const std_msgs::Header::ConstPtr &msg)
{
    std_msgs::Header msg_ = *msg;
}

int torch_ros::torch_ros_wrapperNodelet::just_an_example()
{
    return 6666;
}