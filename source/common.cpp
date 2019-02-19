/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 19.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Image processing blocks
 * @details Common functionality
 * 
 */

/*!
 * @todo 
 */

#include <imb/common.h>

namespace imb {

//! Type to string for OpenCV matrices
std::string type2str(int type) {
	std::string format;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar channels = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
		case CV_8U:
			format = "8U";
			break;
		case CV_8S:
			format = "8S";
			break;
		case CV_16U:
			format = "16U";
			break;
		case CV_16S:
			format = "16S";
			break;
		case CV_32S:
			format = "32S";
			break;
		case CV_32F:
			format = "32F";
			break;
		case CV_64F:
			format = "64F";
			break;
		default:
			format = "User";
			break;
	}

	format += "C";
	format += (channels + '0');

	return format;
}

} // namespace imb
