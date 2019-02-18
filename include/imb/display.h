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

#ifndef IMB_DISPLAY_H
#define IMB_DISPLAY_H

#include "opencv2/opencv.hpp"

using namespace cv;
namespace imb {

/*!
 * @brief Display functionality
 */
class Display {
  public:
	//! Class constructor
	Display(void);

	//! Class destructor
	~Display(void);

	//! Filter function pointer
	int (*filter_function)(cv::Mat*, cv::Mat*);

	//! Display function
	int display_comparison(cv::Mat *image_a, cv::Mat *image_b);

	//! Display window name
	std::string display_window_name;

	//! Display mode
	unsigned int mode;

}; // class Display

} // namespace imb

#endif // IMB_DISPLAY_H
