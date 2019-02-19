/*!
 * @file
 * @author Ernest Skrzypczyk <emeres.code@onet.eu>
 * @version 0.2.1
 * @date 19.02.19
 * @copyright Ernest Skrzypczyk
 * @brief Image processing blocks
 * @details Common instance
 * 
 */

/*!
 * @todo 
 */

#ifndef IMB_COMMON_H
#define IMB_COMMON_H

#include "opencv2/opencv.hpp"

using namespace cv;
namespace imb {

/*!
 * @brief Type to string for OpenCV matrices
 * @reference https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv
 */
std::string type2str(int type);

} // namespace imb

#endif // IMB_COMMON_H
