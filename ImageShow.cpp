#include "ImageShow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using std::cout;
using std::endl;


// Using openCV to display and store the depth image
void ImageShow::displaySaveDepth(double** image, std::string filename, const int width, const int height, double constrast)
{

    uint8_t greyArr[900][1440];
    

    //Converting the depth image to uint8 format
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            greyArr[height-j-1][i] = uint8_t(255*( std::min(1.0,constrast*(1-image[i][j]))) ) ;


    
    cv::Mat greyImg = cv::Mat(height,width, CV_8U, &greyArr);
    cv::imwrite(filename, greyImg);   //Saving the image on hard disk
    std::string greyArrWindow = "Depth Image";
    cv::namedWindow(greyArrWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(greyArrWindow, greyImg);   //Displaying the image

    cv::waitKey(0);
    cv::destroyAllWindows();

    

}
