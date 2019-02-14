/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 09.02.19
 * @copyright Ernest Skrzypczyk
 * @brief File operations
 * @details 
 * 
 */

/*!
 * @todo 
 */

#ifndef IMB_FILE_H
#define IMB_FILE_H

#include "opencv2/opencv.hpp"
#include <string>

using namespace cv;
namespace imb {

/*!
 * @brief File operations
 */
class FileOperations {
  public:
	//! Class constructor
	FileOperations(void);

	//! Class destructor
	~FileOperations(void);

	//! Image file load procedure
	int load(std::string filename);

	//! Image file save procedure
	int save(std::string filename);

	//! Input image matrix
	cv::Mat input_matrix;

	//! Output image matrix
	cv::Mat output_matrix;

	//! Input image filename
	std::string input;

	//! Output image filename
	std::string output;

#if DEBUG > 0
	//! OpenCV version check
	int openCVVersionCheck(void);
#endif

}; // class FileOperations

} // namespace imb

#endif // IMB_FILE_H
