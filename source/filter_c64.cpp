/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 21.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Filter: Commodore 64 screen emulation
 * @details 
 * 
 */

/*!
 * @todo 
 */

#include "imb/common.h"
#include <math.h> // pow, sqrt -- filter_c64
#include <climits> // int_max -- filter_c64

namespace imb {

//! Filter definitions
namespace Filter {

bool switch_compare_rgb; // = true;
bool switch_continuous_image_check; // = false;
bool switch_vic_ii_late_model; // = true;

int filterPaletteC64(cv::Mat *input, cv::Mat *output) { //@todo Rename to filterPaletteC64
	printf("Filter: %s\n", "C64");
	cv::Mat processed_image;
	// Switch between YUV and RGB comparison
	if (switch_compare_rgb) {
		// Convert into YUV color space
		cv::cvtColor(*input, processed_image, COLOR_BGR2YUV);
#if DEBUG > 0
		printf("Filter: Input: %s, converted to YUV: %s\n", type2str(input->type()).c_str(), type2str(processed_image.type()).c_str());
#endif
	} else {
		// Copy processed image
		input->copyTo(processed_image);
#if DEBUG > 0
		printf("Filter: Input: %s, copied\n", type2str(input->type()).c_str());
#endif
	}

	/*
	// VIC luma output levels
	if (vic_ii_model) {
		//std::vector<int> vic_luma {0, 8, 10, 12, 15, 16, 20, 24, 32}; // Multiply by 255 / 32 = 7,96875 ~ 8
		std::vector<int> vic_luma{0, 64, 80, 96, 120, 128, 159, 191, 255};
	} else {
		//std::vector<int> vic_luma {0, 8, 16, 24, 32};
		std::vector<int> vic_luma{0, 64, 128, 192, 255};
	}
	*/
	// VIC chrominance output levels
	// Angle calculations:
	// 360° / 16 * n
	// red: 5; cyan: 5i; purple: 2; green: 2i; blue: 0; yellow: 0i; orange: 6; brown:7; light red: 5; light green: 2i; light blue: 0;
	// No angle colors: black: 0, white: 32; dark grey: 10; grey: 15; light grey: 20;
	// peak = 34,0081334493; u = peak * cos(angle); v = peak * sin(angle);

// LUT 8 bit YUV
uchar lut8yuv[16][3] = {
	{0, 0, 0}, // black
	{255, 0, 0}, // white
	{80, 0, 0}, // red
	{159, 0, 11}, // cyan
	{96, 18, 29}, // purple
	{128, 0, 32}, // green
	{64, 34, 0}, // blue
	{191, 21, 0}, // yellow
	{96, 34, 3}, // orange
	{64, 0, 14}, // brown
	{128, 0, 0}, // light red
	{80, 0, 0}, // dark grey
	{120, 0, 0}, // grey
	{191, 0, 32}, // light green
	{120, 34, 0}, // light blue
	{159, 0, 0}, // light grey
};

// LUT 8 bit RGB
uchar lut8rgb[16][3] = {
	{0, 0, 0}, // black
	{255, 255, 255}, // white
	{58, 102, 22}, // red
	{172, 166, 93}, // cyan
	{129, 72, 132}, // purple
	{164, 114, 102}, // green
	{64, 50, 134}, // blue
	{191, 183, 233}, // yellow
	{99, 80, 165}, // orange
	{80, 68, 0}, // brown
	{105, 150, 70}, // light red
	{80, 80, 80}, // dark grey
	{120, 120, 120}, // grey
	{228, 178, 166}, // light green
	{120, 106, 189}, // light blue
	{159, 159, 159}, // light grey
};

	// Prepare iteration
	int nChannels = processed_image.channels();
	int nRows = processed_image.rows;
	int nCols = processed_image.cols * nChannels;
	unsigned int i, j, l;
	int error = 0;
	int error_min = 0;
	int lutindex = 0;
	uchar *point;

	if (switch_continuous_image_check && processed_image.isContinuous()) {
#if DEBUG > 0
		printf("Filter: Continuous image detected\n");
#endif
		nCols *= nRows;
		nRows = 1;
	}

	// Iterate over image
	for (i = 0; i < nRows; ++i) { // Rows
		point = processed_image.ptr<uchar>(i);
		for (l = 0; l < nCols; l = l + nChannels) { // Columns: Jump by number of channels
			// Set initial error calculation
			error_min = INT_MAX;
			error = 0;
			// Determine error
			for (j = 0; j < 16; ++j) { // LUT
				if (switch_compare_rgb) {
					error = int(sqrt(float(((lut8rgb[j][0] - point[l]) * (lut8rgb[j][0] - point[l])) + ((lut8rgb[j][1] - point[l + 1]) * (lut8rgb[j][1] - point[l + 1])) + ((lut8rgb[j][2] - point[l + 2]) * (lut8rgb[j][2] - point[l + 2])))));
					if (point[l] == 0) {
#if DEBUG > 0
						printf("Filter: Pixel RGB: %d, %d, %d; error %d, minimal: %d; lut8rgb: %d,%d,%d; lutindex: %d\n", point[l], point[l + 1], point[l + 2], error, error_min, lut8rgb[j][0], lut8rgb[j][1], lut8rgb[j][2], lutindex);
#endif
					};
				} else {
					error = int(sqrt(float(((lut8yuv[j][0] - point[l]) * (lut8yuv[j][0] - point[l])) + ((lut8yuv[j][1] - point[l + 1]) * (lut8yuv[j][1] - point[l + 1])) + ((lut8yuv[j][2] - point[l + 2]) * (lut8yuv[j][2] - point[l + 2])))));
#if DEBUG > 0
					printf("Filter: Pixel RGB: %d, %d, %d; error %d, minimal: %d; lut8rgb: %d,%d,%d; lutindex: %d\n", point[l], point[l + 1], point[l + 2], error, error_min, lut8yuv[j][0], lut8yuv[j][1], lut8yuv[j][2], lutindex);
#endif
				}

				// Determine closest YUV value
				// Set minimal error and LUT index
				if (error < error_min) {
					error_min = error;
					lutindex = j;
				}
			} // LUT
#if DEBUG > 0
			if (error_min == INT_MAX) {
				printf("Filter: No assignment: l: %d, error: %d, minimal: %d\n", l, error, error_min);
			}
			if (l % 1000 == 0) {
				printf("Filter: Error: l: %d, minimal: %d, l: %d, lutindex: %d\n", l, error, error_min, lutindex);
				printf("Filter: Loop: l: %d, i: %d, j: %d, lutindex: %d\n", l, i, j, lutindex);
				printf("Filter: Assignment: l: %d, assign index %d: %d, %d, %d\n", l, lutindex, lut8rgb[lutindex][0], lut8rgb[lutindex][1], lut8rgb[lutindex][2]);
			}
#endif
			// Process image
			// Look Up Table for RGB to corresponding YUV value
			// Use OpenCV LUT(input, lut, output) if possible
			point[l] = *lut8rgb[lutindex];
			/*
			point[l] = lut8rgb[lutindex][0];
			point[l + 1] = lut8rgb[lutindex][1];
			point[l + 2] = lut8rgb[lutindex][2];
			*/
		} // Columns
	} // Rows

	// Switch between YUV and RGB comparison
	if (switch_compare_rgb) {
		// Convert back into RGB color space
		cv::cvtColor(processed_image, *output, COLOR_YUV2BGR);
	} else {
		// Copy processed image
		processed_image.copyTo(*output);
	}
	return 0;
} // function filterPaletteC64

} // namespace Filter

} // namespace imb
