#ifndef DEFINES_H
#define DEFINES_H

#define QRECOG_VERSION "1.0"

#define WIDTH                   600
#define HEIGHT                  400



//enum { VIEW1, VIEW2, NO_VIEW };


//enum { STORY_MODE, ARCADE_MODE, SURVIVOR_MODE, EDITOR_MODE };

//enum { COLOR_DISABLED, COLOR_RED, COLOR_GREEN, COLOR_BLUE };

// Re-define for compatibility purposes
//#ifndef GL_CLAMP_TO_EDGE
//    #define GL_CLAMP_TO_EDGE      0x812F
//#endif

/*****************************************************************
 * Compatibility for pcl version
 *      define PCL_1_8 to compile with 1.8 pcl version
 *      undefine PCL_1_8 to compile with 1.7/.2 pcl version
 */
#define PCL_1_8 0

//****************************************************************

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

/******************************************************************
 * Compatibility with RGB/RGBA function:
 *      define ENABLE_ONLY_RGB_FUNC:
 *          - enable mincut segmentation preview
 *          - disable opengev lib (can't work with RGB points at now)
 *      define ENABLE_ONLY_RGB_FUNC:
 *          - disable mincut segmentation preview
 *          - enable opengev lib
 */
//#define ENABLE_ONLY_RGB_FUNC 0

//******************************************************************

#ifndef ENABLE_ONLY_RBG_FUNC
    typedef pcl::PointXYZRGBA PointType;
#else
    typedef pcl::PointXYZRGB PointType;
#endif

typedef pcl::PointCloud<PointType> cloudType;
typedef cloudType::Ptr cloudPtrType;

#endif // DEFINES_H
