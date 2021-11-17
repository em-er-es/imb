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
 * @todo Fix the arguments_parser_long_options initialization routine in class constructor, possibly via initialization lists [F001]
 */

#include <imb/arguments.h>

namespace imb {

//! Class constructor
//!
//! @todo Fix the arguments_parser_long_options initialization routine in class constructor, possibly via initialization lists [F001]
ArgumentParser::ArgumentParser(void) {
	//! Short options
	arguments_parser_short_options = "abcCdDhi:mo:rRv";

	// Set defaults
	flow_control_.name_input = "input.png";
	flow_control_.name_output = "output.png";
}

//! Class destructor
ArgumentParser::~ArgumentParser(void) {
}

//! Arguments parsing
int ArgumentParser::argumentsParsing(int arguments_count, char **arguments_vector) {
#if DEBUG > 0
	printf("ArgumentParser: Initial\n");
#endif

	//! Long options
	//! @todo Fix the arguments_parser_long_options initialization routine in class constructor, possibly via initialization lists [F001]
	const struct option arguments_parser_long_options[] = {
		{"brief", no_argument, NULL, 0},
		{"display", no_argument, &flow_control_.switch_display, 1},
		{"no-display", no_argument, &flow_control_.switch_display, 0},
		{"help", no_argument, NULL, 'h'},
		{"input", required_argument, NULL, 'i'},
		{"output", required_argument, NULL, 'o'},
		{"verbose", no_argument, NULL, 1},
		{0, 0, 0, 0},
	};

	//! Argument index
	int index = 0;
	//! Argument switch
	int argument;
	//! Error message control
	//! @details 0: Enable error messages
	//! @details 1: Disable error messages
	opterr = 0;

	// Parse arguments
	while ((argument = getopt_long(arguments_count, arguments_vector, arguments_parser_short_options, arguments_parser_long_options, &index)) != -1) {
#if DEBUG > 0
		printf("ArgumentParser: Switch: %c\n", argument);
#endif
		switch (argument) {
			case -1:
				printf("ArgumentParser: All command-line options parsed\n");
				break;
			case 0:
				printf("ArgumentParser: Long option return\n");
				break;
			case 'a':
#if DEBUG > 1
				printf("ArgumentParser: Switch: %c, decimal: %d, index: %d\n", argument, argument, index);
#endif
				flow_control_.switch_scan_lines = true;
				break;
			case 'c':
				flow_control_.switch_color_mixing = true;
				break;
			case 'C':
				flow_control_.switch_continuous_image_check = true;
				break;
			case 'd':
				flow_control_.switch_display = 1;
				break;
			case 'D':
				flow_control_.switch_display = 0;
				break;
			case 'h':
				printf("Usage: %s [-acCdDhmrRv] -i input -o output\n\t-a\tScan lines\n\t-c\tColor mixing\n\t-C\tContinuous image check\n\t-d/D\tEnable/Disable input and output comparison display\n\t-h\tThis help\n\t-i\tInput image (default: input.png)\n\t-m\tVIC II model selector (default: latest)\n\t-o\tOutput image (default: output.png)\n\t-r/R\tEnable/Disable RGB comparison (default: enabled)\n\t-v\tVerbose\n", arguments_vector[0]);
				exit(EXIT_SUCCESS);
			case 'i':
				if (isprint(argument)) {
					flow_control_.name_input = std::string(optarg);
					break;
				} else {
					fprintf(stderr, "Option -%c requires an alphanumerical argument.\n", argument);
					exit(EXIT_FAILURE);
				}
			case 'm':
				flow_control_.switch_vic_ii_late_model = false;
				break;
			case 'o':
				if (isprint(argument)) {
					flow_control_.name_output = std::string(optarg);
					break;
				} else {
					fprintf(stderr, "Option -%c requires an alphanumerical argument.\n", argument);
					exit(EXIT_FAILURE);
				}
			case 'r':
				flow_control_.switch_compare_rgb = true;
				break;
			case 'R':
				flow_control_.switch_compare_rgb = false;
				break;
			case 'v':
				flow_control_.verbose_flag = true;
				break;
			case ':':
			case '?':
				if ((optopt == 'i') or (optopt == 'o')) {
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				} else if (optopt == '-') {
					fprintf(stderr, "Please use single hyphen options only.\n");
				} else if (isprint(optopt)) {
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				} else {
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				}
#if DEBUG > 0
				fprintf(stderr, "%s: invalid option -- %c : %c : %s\n", arguments_vector[0], argument, optopt, optarg);
#endif
				fprintf(stderr, "Use '%s -h or --help' for more information.\n", arguments_vector[0]);
				exit(EXIT_FAILURE);
			default:
				abort();
		}
	}

#if DEBUG > 0
	printf("ArgumentParser: Flags: a = %d, m = %d, c = %d, input: %s, output: %s\n", flow_control_.switch_scan_lines, flow_control_.switch_vic_ii_late_model, flow_control_.switch_color_mixing, flow_control_.name_input.c_str(), flow_control_.name_output.c_str());
#endif

	for (index = optind; index < arguments_count; index++)
		printf("Non-option argument: %s\n", arguments_vector[index]);
	return 0;
}

} // namespace imb
