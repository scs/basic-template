/* Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty. This file is offered as-is,
 * without any warranty.
 */

/*! @file process_frame.c
 * @brief Contains the actual algorithm and calculations.
 */

/* Definitions specific to this application. Also includes the Oscar main header file. */
#include "template.h"

OscFunction(ProcessFrame)
	enum EnBayerOrder enBayerOrder;

	/* Debayer to full size color image. Color sensor assumed. */
	OscCall( OscCamGetBayerOrder, &enBayerOrder, 0, 0);
	OscCall( OscVisDebayer, data.pictureRaw.data, OSC_CAM_MAX_IMAGE_WIDTH, OSC_CAM_MAX_IMAGE_HEIGHT, enBayerOrder, data.pictureColor.data);

	/* Or debayer to quarter size grey image. Color sensor assumed. */
	OscCall( OscVisVectorDebayerGrey, &data.pictureRaw, &data.pictureGrey);


	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* |                                                                 */
	/* |                    Add your code here                           */
	/* |                                                                 */
	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
OscFunctionEnd()
