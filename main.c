/* Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty. This file is offered as-is,
 * without any warranty.
 */

/*! @file main.c
 * @brief Main file of the template application. Contains initialization
 * and image acquisition loop.
 */

#include "template.h"
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

/*! @brief This stores all variables needed by the algorithm. */
struct TEMPLATE data;



/*********************************************************************//*!
 * @brief Initialize everything so the application is fully operable
 * after a call to this function.
 * 
 * @return SUCCESS or an appropriate error code.
 *//*********************************************************************/
OscFunction(static Init, const int argc, const char * argv[])
	
	memset(&data, 0, sizeof(struct TEMPLATE));
	
	/******* Create the framework **********/	
	OscCall( OscCreate, 
		&OscModule_cam, 
		&OscModule_bmp, 
		&OscModule_vis, 
		&OscModule_gpio, 
		&OscModule_log, 
		&OscModule_sup);   
	
	OscLogSetConsoleLogLevel(ERROR);
	OscLogSetFileLogLevel(ERROR);

	
	/* Seed the random generator */
	srand(OscSupCycGet());
	
	/* Set the camera registers to sane default values. */
	OscCall( OscCamPresetRegs);
	OscCall( OscCamSetupPerspective, OSC_CAM_PERSPECTIVE_DEFAULT);

	/* Configure camera emulation on host */
#if defined(OSC_HOST) || defined(OSC_SIM)
	OscCall( OscFrdCreateConstantReader, &data.hFileNameReader, TEST_IMAGE_FN);
	OscCall( OscCamSetFileNameReader, data.hFileNameReader);
#endif /* OSC_HOST or OSC_SIM */
	
	/* Set up one frame buffer for maximum image size. Cached memory. */
	OscCall( OscCamSetFrameBuffer, 0, OSC_CAM_MAX_IMAGE_WIDTH*OSC_CAM_MAX_IMAGE_HEIGHT, data.u8FrameBuffer, TRUE);

	/* Initialize picture structures */
	data.pictureGrey.data = data.u8GreyImage;
	data.pictureGrey.width = OSC_CAM_MAX_IMAGE_WIDTH;
	data.pictureGrey.height = OSC_CAM_MAX_IMAGE_HEIGHT;

	data.pictureColor.data = data.u8ColorImage;
	data.pictureColor.width = OSC_CAM_MAX_IMAGE_WIDTH;
	data.pictureColor.height = OSC_CAM_MAX_IMAGE_HEIGHT;
	
OscFunctionCatch()
	/* Destruct framwork due to error above. */
	OscDestroy();
	OscMark_m( "Initialization failed!");
	
OscFunctionEnd()


OscFunction(mainFunction, const int argc, const char * argv[])
	uint8 *pCurRawImg = NULL;
	OSC_ERR err;
	
	/* Initialize system */
	OscCall( Init, argc, argv);
	
	/* Image acquisation loop */
	while( true)
	{		
		OscCall( OscCamSetupCapture, 0);	
		OscCall( OscGpioTriggerImage);
		
		while( true)
		{
			err = OscCamReadPicture( 0, &pCurRawImg, 0, CAMERA_TIMEOUT);

			if(err == SUCCESS)
			{ 
				break;
			}
		}
		
		data.pictureRaw.data = pCurRawImg;
		OscCall( ProcessFrame);
	}	


OscFunctionCatch()
	OscDestroy();
	OscLog(INFO, "Quit application abnormally!\n");
OscFunctionEnd()

/*********************************************************************//*!
 * @brief Program entry
 *
 * @param argc Command line argument count.
 * @param argv Command line argument strings.
 * @return 0 on success
*//*********************************************************************/
int main(const int argc, const char * argv[]) {
	if (mainFunction(argc, argv) == SUCCESS)
		return 0;
	else
		return 1;
}
