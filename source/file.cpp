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
 * @todo Finilize save procedure [D002]
 */

#include <imb/file.h>

namespace imb {

//! Image file load procedure
int FileOperations::load(std::string filename) {
#if DEBUG > 0
	printf("FileOperations: Load: Filename %s\n", filename.c_str());
#endif
	input_matrix = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);

	if (input_matrix.empty()) {
		fprintf(stderr, "Input file %s could not be loaded\n", filename.c_str());
		exit(EXIT_FAILURE);
	}
}

//! Image file save procedure
//!
//! @todo Finilize save procedure [D002]
int FileOperations::save(std::string filename) {
#if DEBUG > 0
	printf("FileOperations: Save: Filename %s\n", filename.c_str());
#endif
}

#if DEBUG > 0
//! OpenCV version check
int FileOperations::openCVVersionCheck(void) {
	printf("FileOperations: OpenCV version check: %s\n", CV_VERSION);
	//	std::cout << "FileOperations:\n\tOpenCV version: " << CV_VERSION << "\n\tMajor version: " << CV_MAJOR_VERSION << "\n\tMinor version: " << CV_MINOR_VERSION << "\n\tSubminor version: " << CV_SUBMINOR_VERSION << std::endl;

	return CV_MAJOR_VERSION;
};
#endif

} // namespace imb
