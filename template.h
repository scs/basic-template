/* Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty. This file is offered as-is,
 * without any warranty.
 */

/*! @file template.h
 * @brief Global header file for the template application.
 */
#ifndef TEMPLATE_H_
#define TEMPLATE_H_

/*--------------------------- Includes -----------------------------*/
#include <stdio.h>
#include "oscar.h"

/*--------------------------- Settings ------------------------------*/
/*! @brief Timeout (ms) when waiting for a new picture. */
#define CAMERA_TIMEOUT 1

/*! @brief The file name of the test image on the host. */
#define TEST_IMAGE_FN "test.bmp"

/*------------------- Main data object and members ------------------*/



/*! @brief The structure storing all important variables of the application.
 * */
struct TEMPLATE
{
	/*! @brief The frame buffer for the frame capture device driver.*/
	uint8 u8FrameBuffer[ OSC_CAM_MAX_IMAGE_HEIGHT*OSC_CAM_MAX_IMAGE_WIDTH];
	struct OSC_PICTURE pictureRaw;
	/*! @brief A buffer to hold a full size color image. */
	uint8 u8ColorImage[ 3*OSC_CAM_MAX_IMAGE_WIDTH*OSC_CAM_MAX_IMAGE_HEIGHT];
	struct OSC_PICTURE pictureColor;
	/*! @brief A buffer to hold a quarter size grey image. */
	uint8 u8GreyImage[ OSC_CAM_MAX_IMAGE_WIDTH*OSC_CAM_MAX_IMAGE_HEIGHT/4];
	struct OSC_PICTURE pictureGrey;
		
#if defined(OSC_HOST) || defined(OSC_SIM)
	/*! @brief File name reader for camera images on the host. */
	void *hFileNameReader;
#endif /* OSC_HOST or OSC_SIM */
	/*! @brief The last raw image captured. Always points to the frame
	 * buffer. */
	uint8* pRawImg;

};

extern struct TEMPLATE data;

/*-------------------------- Functions --------------------------------*/

/*********************************************************************//*!
 * @brief Process a newly captured frame.
 * 
 * In the case of this template, this consists just of debayering the
 * image and writing the result to the result image buffer. Debayer
 * to full size color and quater size grey is applied. This should be
 * the starting point where you add your code.
 * 
 * @return SUCCESS or appropriate error code.
 *//*********************************************************************/
OSC_ERR ProcessFrame(void);

#endif /*TEMPLATE_H_*/
