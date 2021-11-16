/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 21.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Filter: Commodore 64 screen emulation
 * @details 
 * 
 */

/*!
 * @todo Fix filter name multiple definitions [F006]
 */

#ifndef IMB_FILTER_C64_H
#define IMB_FILTER_C64_H

//#include "imb/lut_c64.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
namespace imb {

/*!
 * @brief Filter definitions
 * @todo Fix filter name multiple definitions [F006]
 */
namespace Filter {

	//! @
	extern bool switch_compare_rgb;
	extern bool switch_continuous_image_check;
	extern bool switch_vic_ii_late_model;

	//! Filter name
	//! @todo Fix filter name multiple definitions [F006]
	//std::string filter_name;

	/*!
 * @brief Commodore 64 palette filter
 * @reference https://www.pepto.de/projects/colorvic/2001/
 */
	int filterPaletteC64(cv::Mat *input, cv::Mat *output);

} // namespace Filter

} // namespace imb

#endif // IMB_FILTER_C64_H
