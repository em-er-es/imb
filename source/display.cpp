/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 14.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Display functionality
 * @details 
 * 
 */

/*!
 * @todo 
 */

#include <imb/display.h>

namespace imb {

std::string type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch ( depth ) {
	  case CV_8U:  r = "8U"; break;
	  case CV_8S:  r = "8S"; break;
	  case CV_16U: r = "16U"; break;
	  case CV_16S: r = "16S"; break;
	  case CV_32S: r = "32S"; break;
	  case CV_32F: r = "32F"; break;
	  case CV_64F: r = "64F"; break;
	  default:     r = "User"; break;
	}

	r += "C";
	r += (chans+'0');

	return r;
}


//! Class constructor
Display::Display(void) {
	// Set default display window name
	display_window_name = "IMB";
}

//! Class destructor
Display::~Display(void) {
}

//! Display function
int Display::display_comparison(cv::Mat *image_a, cv::Mat *image_b) {
	display_window_name.append(" - Comparison");
#if DEBUG > 0
	printf("Display: Window name: %s\n", display_window_name.c_str());
#endif

	// Create a comparison image
	cv::Size size_a = image_a->size();
	cv::Size size_b = image_b->size();
#if DEBUG > 0
	printf("Display: Input image sizes: %d, %d; %d, %d\n", size_a.width, size_a.height, size_b.width, size_b.height);
#endif
	cv::Mat image_comparison(size_a.height, size_a.width + size_b.width, CV_8UC4);
#define IMB_DISPLAY_ROI 0
#if IMB_DISPLAY_ROI > 0
	// Move right boundary left
	image_comparison.adjustROI(0, 0, 0, -size_b.width);
	image_a->copyTo(image_comparison);
	// Move left boundary right, move right boundary right
	image_comparison.adjustROI(0, 0, -size_a.width, size_b.width);
	image_b->copyTo(image_comparison);
	// Restore origianl ROI
	image_comparison.adjustROI(0, 0, size_a.width, 0);
#endif
#if DEBUG > 0
	cv::Size adjusted_roi;
	cv::Point adjusted_roi_point;
	image_comparison.locateROI(adjusted_roi, adjusted_roi_point);
	printf("Display: Adjusted ROI: %d, %d, %d, %d; %d, %d\n", adjusted_roi.width, adjusted_roi.height, size_a.width, size_a.height, adjusted_roi_point.x, adjusted_roi_point.y);

	std::string type_a = type2str(image_a->type());
	std::string type_b = type2str(image_b->type());
	printf("Display: Image A: %s\n", type_a.c_str());
	printf("Display: Image B: %s\n", type_b.c_str());
#endif
#if IMB_DISPLAY_ROI == 0
	image_a->copyTo(image_comparison(Rect(0, 0, size_a.width, size_a.height)));
	image_a->copyTo(image_comparison(Rect(size_a.width, 0, size_b.width, size_b.height)));
#endif

	// Create window with flags
	namedWindow(display_window_name, WINDOW_AUTOSIZE & WINDOW_OPENGL & WINDOW_GUI_EXPANDED);

	// Handle key input
	//while((cv::waitKey() & 0xEFFFFF) != 27);
	while (true) {
		char key = waitKey(0); //@todo Check if bit mask still needs to be applied in this case

		if (key == '\27') {
			break;
		}
		else if (key == 'v') {
			printf("Image information: format, size, resolution, depth\nSizes: %d, %d; %d, %d\n", size_a.width, size_a.height, size_b.width, size_b.height);
		}
		else if (key == 'q') {
			break;
		}

		// Display comparison image
		imshow(display_window_name, image_comparison);
	}
	// Close all windows
	//destroyWindow(); //#D#
	destroyAllWindows();
}

} // namespace imb