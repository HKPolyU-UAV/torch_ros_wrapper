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
 * \file torch_ros_wrapper.h
 * \date 07/12/2023
 * \author pattylo
 * \copyright (c) AIRO-LAB @ RCUAS of Hong Kong Polytechnic University
 * \brief classes for torch in ROS
 */

#ifndef LED_H
#define LED_H

#include "tools/essential.h"

#include "tools/RosTopicConfigs.h"

#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>

#include "torch/torch.h"

namespace torch_ros
{
    class torch_ros_wrapperNodelet : public nodelet::Nodelet
    {
            int just_an_example();
            void sub_msg_callback(const std_msgs::Header::ConstPtr& msg);
            
            torch::Tensor tensor = torch::rand({2, 3});


            virtual void onInit()
            {                
                ros::NodeHandle& nh = getMTNodeHandle();
                ROS_INFO("torch_ros_wrapper Initiated...");

                registerRosCommunicate(nh);    
            }

            inline void registerRosCommunicate(ros::NodeHandle& nh)
            {
                RosTopicConfigs configs(nh, "/led");

                ros::Subscriber sub1 = nh.subscribe<std_msgs::Header>
                    ("sub/topic/name", 1, &torch_ros_wrapperNodelet::sub_msg_callback, this);
                
                ros::Publisher pub1 = nh.advertise<std_msgs::Header>
                    ("pub/topic/name", 1, true);
            }
    };
    PLUGINLIB_EXPORT_CLASS(torch_ros::torch_ros_wrapperNodelet, nodelet::Nodelet)
}

#endif