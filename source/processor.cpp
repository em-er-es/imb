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
#include <imb/common.h>
#include <math.h> // pow, sqrt -- filter_c64
#include <climits> // int_max -- filter_c64

namespace imb {

//! Class constructor
ProcessorBlock::ProcessorBlock(void) {
	// Set default processor block name
	processor_block_name = "Processor block";
}

//! Class destructor
ProcessorBlock::~ProcessorBlock(void) {
}

} // namespace imb
