#include "Point2depth.h"
#include <string>
#include <fstream>
#include <iostream>
#include "ImageShow.h"

using std::string;
using std::ifstream;
using std::ofstream;

// Constructor, load the file name and dynamically creat the template depth image
Point2Depth::Point2Depth(string filename) {

	fileName = filename;

	//Creating the 2D image based on the resolution
	image = new double* [img_resolution[0]];
	for (int i = 0; i < img_resolution[0]; i++)
	{
		image[i] = new double[img_resolution[1]];
		
	}
	for (int i = 0; i < img_resolution[0]; i++)
		for (int j = 0; j < img_resolution[1]; j++)
			image[i][j] = 1.0; /// the depth is initially set to max depth: 1.0
}

//reads the point cloud from text file
void Point2Depth::readFile(void)
{

	ifstream fin(fileName);

	double x, y, z;

	while (fin >> x >> y >> z) {
		pointsXYZ.push_back( vector3D(x,y,z)  );

	}

}
//converts the point cloud into the depth image
void Point2Depth::projectPoints(void)
{
	double maxXYZ[3];  // contains the max value for x,y, and z values which is used for cropping and normalizing the image
	double minXYZ[3];  //// contains the min value for x,y, and z values which is used for cropping and normalizing the image
	bool first = true; // a flag used to give initial value to max and min values based on the first point
	
	
	for (auto it = pointsXYZ.begin(); it != pointsXYZ.end(); it++)
	{
		//for everypoint it calculate the inteception point on the camera plane from the ray from each point to the camera point (0,0,0)

		vector3D p = *it;
		double t = focal_length / p.val[2];  // calculate the "t" at which the point ray intercept the Z-plane (camera plane)
		
		for(int i =0; i< 2; i++) p.val[i] = t * p.val[i];  //calculate the X and Y cordinate on the image plane. the Z value is not changed and will be used later as a measure of depth
		
		*it = p;

		if (first) {
			for (int i = 0; i < 3; i++) maxXYZ[i] = minXYZ[i] = p.val[i];  /// initilizing the max and min values
			first = false;
		}
		else {
			//updating min and max values, this is later used to crop and normilize the depth image
			for (int i = 0; i < 3; i++) maxXYZ[i] = std::max(maxXYZ[i], p.val[i]);
			for (int i = 0; i < 3; i++) minXYZ[i] = std::min(minXYZ[i], p.val[i]); 
		}
		
	}
	
	//This part convert the X and Y values on the camera plane, to pixel values accroding to the resolution
	for (auto it = pointsXYZ.begin(); it != pointsXYZ.end(); it++)
	{
		vector3D p = *it;
		for (int i = 0; i < 2; i++) {
			double len = maxXYZ[i] - minXYZ[i];
			p.val[i] = std::round((img_resolution[i]-1)*(p.val[i] - minXYZ[i])/(len)); // normalize the X and Y values between 0-1 and then multipyling by the resolution, therefore covnerting to proper pixel values

		}
		*it = p;
		
		
		//normalizng the depth value (Z), so the farthest point is at 1 and closest is at 0,, then choosing the nearest value for each pixel to ensure visibility
		image[int(p.val[0])][int(p.val[1])] = std::min(image[int(p.val[0])][int(p.val[1])] , (p.val[2]-minXYZ[2])/(maxXYZ[2]- minXYZ[2]) );
		
	}
	
}

//Dispaly and saves the image while allowing for changing the constrast
void Point2Depth::displaySaveImage(std::string filename, double contrast)
{
	ImageShow imshow;

	imshow.displaySaveDepth(image, filename, img_resolution[0], img_resolution[1], contrast);

}
