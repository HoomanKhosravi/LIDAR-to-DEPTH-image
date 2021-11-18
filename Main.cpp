#include <iostream>
#include "Point2depth.h"

//This program converts a point cloud into an depth image
//No addtional 3D library is used
//I only use openCV to display and store the resulting depth image
//Author: Hooman Khosravi

int main() {

	Point2Depth point2Depth("pointcloud.txt"); //Initilize the point cloud to rgbd converter and passes the input file contatining the point cloud
	
	point2Depth.readFile(); //Reads the points from the text file 

	point2Depth.projectPoints(); // Projects the point cloud into a camera place and calcualte the depth image 

	point2Depth.displaySaveImage("depth.jpg", 1.0);// Displays and saves the depth image
	point2Depth.displaySaveImage("depth_highContrast.jpg", 5.0);// Displays and saves the high contrast depth image

}