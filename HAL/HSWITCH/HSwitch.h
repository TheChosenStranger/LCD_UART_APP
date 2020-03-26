/*
 * Switch.h
 *
 *  Created on: Mar 26, 2020
 *      Author: Norhan Nassar
 */

#ifndef SWITCH_H_
#define SWITCH_H_

typedef void (*SwitchCbf_t)(u8* data);

extern void runnable(SwitchCbf_t s);
extern void doit ();


#endif /* SWITCH_H_ */
