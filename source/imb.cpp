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
	printf("Main: Set arguments: %d, %d, %s, %s\n", argument_parser.flow_control_.switch_scan_lines, argument_parser.flow_control_.switch_luminance_3_levels, argument_parser.flow_control_.name_input.c_str(), argument_parser.flow_control_.name_output.c_str());
#endif

// OpenCV version check
#if DEBUG > 0
	imb::FileOperations file_operations;
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
	namedWindow("OpenCV - Input", CV_WINDOW_AUTOSIZE);
	// Display input image
	if (argument_parser.flow_control_.switch_display) {
		imshow("OpenCV - ImageInput", file_operations.input_matrix);
		waitKey(0);
		destroyWindow("OpenCV - Input");
	}

	// Create a processor block
	imb::ProcessorBlock processor_block;
	printf("Main: Processor block filter name = %s\n", processor_block.filter_name.c_str());
	processor_block.filter_name = "C64 filter";
	printf("Main: Processor block filter name = %s\n", processor_block.filter_name.c_str());
	processor_block.filter_function = imb::filter_c64;
	processor_block.filter_function(&file_operations.input_matrix, &file_operations.output_matrix);

	// Display output image
	if (argument_parser.flow_control_.switch_display) {
		imshow("OpenCV - ImageOutput", file_operations.output_matrix);
		waitKey(0);
		destroyWindow("OpenCV - Output");
	}
	file_operations.save(argument_parser.flow_control_.name_output);
}
