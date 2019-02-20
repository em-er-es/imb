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

#include <imb/processor.h>

namespace imb {

//! Class constructor
ProcessorBlock::ProcessorBlock(void) {
	// Set default filter name
	filter_name = "Processor block";
}

//! Class destructor
ProcessorBlock::~ProcessorBlock(void) {
}

//! Image file load procedure
int ProcessorBlock::filter(cv::Mat *input, cv::Mat *output) {
#if DEBUG > 0
	printf("ProcessorBlock: Filter: %s\n", filter_name.c_str());
#endif
}

int filter_c64(cv::Mat *input, cv::Mat *output) { //@todo Rename to filterPaletteC64
	printf("ProcessorBlock: Filter: %s\n", "C64");
	//cv::Mat *operation;
	cv::cvtColor(*input, *output, COLOR_BGR2GRAY);
	cv::cvtColor(*output, *output, COLOR_GRAY2BGR);
}

} // namespace imb
