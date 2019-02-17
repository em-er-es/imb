/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 14.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Processor block
 * @details 
 * 
 */

/*!
 * @todo 
 */

#ifndef IMB_PROCESSOR_H
#define IMB_PROCESSOR_H

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
namespace imb {

/*!
 * @brief Processor block
 */
class ProcessorBlock {
  public:
	//! Class constructor
	ProcessorBlock(void);

	//! Class destructor
	~ProcessorBlock(void);

	//! Filter function pointer
	int (*filter_function)(cv::Mat*, cv::Mat*);

	//! Filter function
	int filter(cv::Mat *input, cv::Mat *output);

	//! Filter name
	std::string filter_name;

	//! Processor block name
	std::string processor_block_name;

	//! Input image pointer
	cv::Mat *processed_image;

}; // class ProcessorBlock

int filter_c64(cv::Mat *input, cv::Mat *output);

} // namespace imb

#endif // IMB_PROCESSOR_H
