# PyTorch ROS Wrapper
This is a ros wrapper package for PyTorch.

## Prerequisite
- Make sure ROS is all set.
- We ran the package on ROS NOETIC.

## Installation
- **Git Clone**. Run:
    ```
    mkdir ws && cd ws
    mkdir src && cd src
    git clone lala
    ```
- **PyTorch**. Please first go to [here](https://pytorch.org/get-started/locally/), and select ```Python``` to install PyTorch. You should be running some command like this:
    ```
    pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu
    ```
    Then do:
    ```
    pip3 install --upgrade PyTorch
    ```
- **libtorch**. Go to [here](https://pytorch.org/get-started/locally/) again, and select ```C++/Java``` to install libtorch. The website should give you a link. Make sure it is ```Download here (cxx11 ABI)``` not ```Download here (Pre-cxx11 ABI)```, as per [issue here](https://github.com/pytorch/pytorch/issues/49450). Then, with the given link, do the following:
    ```
    cd ~/ws/src/torch_ros_wrapper/
    wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-2.1.1%2Bcpu.zip
    unzip libtorch-cxx11-abi-shared-with-deps-2.1.1+cpu.zip 
    cd ~/ws && catkin_make
    ```
    Please adjust the command according to your zip filename. And please make sure the file hierarchy is correct, as we defined the following in ```CMakeLists.txt```:
    ```
    set(Torch_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libtorch/share/cmake/Torch/")
    ```
## Usage
This package provide 2 functions:
- **Convert**. You can convert your model from PyTorch trained .pt to libtorch (C++) accessible .pt by running the following:
    ```
    roslaunch torch_ros_wrapper convertTrainedPt.launch
    ```
    *Remarks*: 
    - Place your ```.pt``` file under ```/launch/model/```
    - Please modify rosparam in ```convertTrainedPt.launch``` accordingly to your ```.pt``` filename.
    - Under ```/scripts/models/```, please place your PyTorch script. Here, we put a ```tcn.py```.
    - In ```/scripts/ConvertCppPt.py```, please first do ```import {your_model}``` at the top of the script. Then under function ```def load_custom_model(self):```, please instantiate ```self.your_model```.
    
    After running the above, you should be able to see ```model_cpp.pt``` under ```/launch/model/```.
- **RUN in ROS**. We provide 2 launch files for running libtorch. 1 in ```rosnode```, 1 in ```rosnodelet```. Just run:
    ```
    roslaunch torch_ros_wrapper TorchRosNode.launch # or
    roslaunch torch_ros_wrapper TorchRosNodelet.launch
    ```
    The ```rosnode``` will try to load the ```model_cpp.pt``` that we just created, while ```rosnodelet``` does nothing. You can modify further.

## Maintainer
[pattylo](https://github.com/pattylo) @ AIRO-LAB @ RCUAS, HKPolyU
