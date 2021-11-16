/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 09.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Image processing blocks
 * @details Main instance
 * 
 */

/*!
 * @todo Implement filter function pointer procedure [D004]
 * @todo 
 */

#include <imb/imb.h>

int main(int arguments_count, char **arguments_vector) {
#if DEBUG > 0
	printf("Main: Initial\n");
#endif
	// Set class instance and manupulate
	imb::ArgumentParser argument_parser;
	int argument_parsing = argument_parser.argumentsParsing(arguments_count, arguments_vector);
#if DEBUG > 1
	printf("Main: Argument parsing = %d\n", argument_parsing);
#endif
#if DEBUG > 0
	printf("Main: Set arguments: %d, %d, %s, %s\n", argument_parser.flow_control_.switch_scan_lines, argument_parser.flow_control_.switch_vic_ii_late_model, argument_parser.flow_control_.name_input.c_str(), argument_parser.flow_control_.name_output.c_str());
#endif

	// OpenCV version check
	imb::FileOperations file_operations;
#if DEBUG > 0
	int opencv_version = file_operations.openCVVersionCheck();
	printf("Main: Check OpenCV version = %d\n", opencv_version);
#endif

	// Set input and output filenames
#if DEBUG > 0
	file_operations.input = argument_parser.flow_control_.name_input;
	file_operations.output = argument_parser.flow_control_.name_output;
	printf("Main: Argument input file = %s\n", argument_parser.flow_control_.name_input.c_str());
	printf("Main: File operations input file = %s\n", file_operations.input.c_str());
#endif

	// Load file
	file_operations.load(argument_parser.flow_control_.name_input);

	// Create a processor block
	//!@todo Implement filter function pointer procedure [D004]
	imb::ProcessorBlock processor_block;
	printf("Main: Processor block filter name = %s\n", processor_block.processor_block_name.c_str());
	processor_block.processor_block_name = "Commodore 64 processor block";
	printf("Main: Processor block filter name = %s\n", processor_block.processor_block_name.c_str());
	processor_block.filter_function = imb::Filter::filterPaletteC64;
	//extern bool switch_vic_ii_late_model;
	imb::Filter::switch_compare_rgb = argument_parser.flow_control_.switch_compare_rgb;
	imb::Filter::switch_vic_ii_late_model = argument_parser.flow_control_.switch_vic_ii_late_model;
#if DEBUG > 0
	printf("Main: RGB comparison = %d\n", imb::Filter::switch_compare_rgb);
	printf("Main: VIC model = %d\n", imb::Filter::switch_vic_ii_late_model);
#endif
	processor_block.filter_function(&file_operations.input_matrix, &file_operations.output_matrix);

	// Display output image
	if (argument_parser.flow_control_.switch_display) {
		imb::Display display;
		display.display_comparison(&file_operations.input_matrix, &file_operations.output_matrix);
	}

	// Save file
	file_operations.save(argument_parser.flow_control_.name_output);
}
