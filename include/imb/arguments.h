/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 09.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Arguments parsing
 * @details 
 * 
 */

/*!
 * @todo 
 */

#ifndef IMB_ARGUMENTS_H
#define IMB_ARGUMENTS_H

#include <ctype.h>
#include <getopt.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace imb {

/*!
 * @brief Argument parsing
 */
class ArgumentParser {
  private:
	//! Arguments parser short options
	const char *arguments_parser_short_options;
	//! Arguments parser long options
	//! @todo Fix the arguments_parser_long_options routine [F001]
	//const struct option *arguments_parser_long_options;

  public:
	//! Class constructor
	ArgumentParser(void);
	//! Class destructor
	~ArgumentParser(void);

	/*!
	 * @brief Arguments flow control structure
	 * @details Holds various switches, counters, dictionary/mapping items to control the flow of the program set by argument parsing
	 */
	struct FlowControl {
		bool verbose_flag = false;
		bool switch_scan_lines = false;
		bool switch_luminance_mixing = false;
		bool switch_luminance_3_levels = true;
		bool switch_luminance_7_levels = false;
		std::string name_input;
		std::string name_output;
	} flow_control_;

	/*!
	 * @brief Arguments parsing using GNU's getopt_long
	 */
	int argumentsParsing(int arguments_count, char **arguments_vector);

}; // class ArgumentParser

} // namespace imb

#endif // IMB_ARGUMENTS_H
