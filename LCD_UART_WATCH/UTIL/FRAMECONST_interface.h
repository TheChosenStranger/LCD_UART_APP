/*
 * FRAMECONST_interface.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Moamen
 */

#ifndef FRAMECONST_INTERFACE_H_
#define FRAMECONST_INTERFACE_H_

#define FRAMECONST_MAX_FRAME_DATA_LENGTH	4

typedef struct{
	u8 sf;
	u8 id;
	u16 len;
}tProtocolHeader_t;

typedef struct{
	tProtocolHeader_t header;
	u8 frameData[FRAMECONST_MAX_FRAME_DATA_LENGTH + 1];
}tProtocol_t;

typedef struct{
	u8* data;
	u8 EOF;
}frameData_t;
STD_ERROR FRAMECONST_FrameConstructor(frameData_t*,u8,u16,u8*);


#endif /* FRAMECONST_INTERFACE_H_ */
