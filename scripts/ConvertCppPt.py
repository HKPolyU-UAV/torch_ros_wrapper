#!/usr/bin/env python3


import rospy
import os
import torch 

import models.tcn as tcn # IMPORT YOUR MODEL!!!

class main():
    def __init__(self, trained_pt_file, save_cpp_pt_file) -> None:
        self.trained_pt_file = trained_pt_file
        
        # Load the model state dictionary
        self.model_state_dict = torch.load(
            self.trained_pt_file, 
            map_location=torch.device('cpu')
        )
        
        self.save_cpp_pt_file = save_cpp_pt_file
        self.load_custom_model()
        self.load_trained_pt()
        self.convert_cpp_pt()
        rospy.loginfo("SUCCESSFUL!")
        pass
    
    ######################## YOUR MODEL HERE!!! ########################
    def load_custom_model(self):
        input_size = 4
        output_size = 3

        self.your_model = tcn.LedvoTcn(
            input_size,
            output_size,
            [64, 64, 64, 64, 128, 128, 128],
            kernel_size=2,
            dropout=0.2,
            activation="GELU"
        )
        pass
    ######################## YOUR MODEL HERE!!! ########################
    
    def load_trained_pt(self):
        # Load the state dictionary into the model
        self.your_model.load_state_dict(self.model_state_dict)
        
        device = torch.device("cpu")
        self.your_model = self.your_model.to(device)
        
        # Set the model to evaluation mode
        self.your_model.eval()
        
        # Create sample input data
        self.sample_input = torch.randn(1, 4, 160).to(device)

        # Perform inference
        with torch.no_grad():
            output = self.your_model(self.sample_input)

        # Print the output
        print("Model Output:", output)
            
    def convert_cpp_pt(self):
        scripted_model = torch.jit.trace(self.your_model, self.sample_input)
        
        if os.path.exists(self.save_cpp_pt_file):
            os.remove(self.save_cpp_pt_file)
            
        scripted_model.save(self.save_cpp_pt_file)

   
if __name__ == "__main__":
    rospy.init_node("convert_cpp_pt")
    rospy.loginfo("COVERT TRAINED PT TO CPP PT!")
    
    trained_pt_file = rospy.get_param("~trained_pt_file")
    save_cpp_pt_file = rospy.get_param("~save_cpp_pt_file")
    
    lala = main(trained_pt_file, save_cpp_pt_file)
    
    


