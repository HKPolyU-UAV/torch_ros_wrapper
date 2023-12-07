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
 * \file lala.cpp
 * \date 07/12/2023
 * \author pattylo
 * \copyright (c) AIRO-LAB @ RCUAS of Hong Kong Polytechnic University
 * \brief trial file for torch_ros_wrapper
 */

#include "include/tools/essential.h"
#include "torch/script.h"
#include <iostream>
#include <memory>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "torch_ros_wrapper Trial");
    ros::NodeHandle nh("~");

    std::string filename;
    nh.getParam("pt_file_loc", filename);
    std::cout<<filename<<std::endl;

    torch::jit::script::Module module;
    try 
    {
        module = torch::jit::load(filename);
        ROS_GREEN_STREAM("LOAD PT FILE SUCCESSFUL!");
    }
    catch (const c10::Error& e) 
    {
        ROS_RED_STREAM("ERROR! LOAD PT FILE UNSUCCESSFUL!");
        return -1;
    }

    torch::Tensor input_data = torch::randn({1, 4, 160});
    at::Tensor output = module.forward({input_data}).toTensor();
    std::cout << output << std::endl<<std::endl;;

    ros::spin();
    
    return 0;
}