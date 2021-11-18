#pragma once
#include<string>
#include <vector>

using std::string;

// Converts a point cloud to a depth image
class Point2Depth {
	
public:
	class vector3D {    // This nested class is used to store 3D vectors 

		public:
			double val[3];
		
			vector3D(double x, double y, double z) {
				val[0] = x;	val[1] = y;	val[2] = z;
			}

	};

	string fileName; //point cloud input
	std::vector<vector3D> pointsXYZ; //contains the 3D points

	const int img_resolution[2] = { 1440,900 }; //resolution of the output image
	double focal_length = 1.0; // focal lenght, distance between the camera point and plane
	double **image; // 2D array containing the depth image
	

	Point2Depth(string filename); //constructor which load the point cloud file name
	void readFile(void); //read the point cloud from the text
	void projectPoints(void); // convert the point cloud into the depth image
	void displaySaveImage(std::string filename, double contrast); // changes the constrast of the depth image, displays and stores it on the hard disk



};