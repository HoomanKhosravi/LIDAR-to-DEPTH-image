#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//This class display and save the depth image using openCV
class ImageShow {

	public:
		void displaySaveDepth(double**, std::string, int width, int height, double contrast); //changing the constrast and displaying and storing the depth image

};