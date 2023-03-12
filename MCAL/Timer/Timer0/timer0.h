/*
 * timer.h
 *
 * Created: 3/4/2023 10:48:46 PM
 *  Author: basem
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "timer0_reg.h"
#include "timer0_types.h"
#include "std_types.h"
#include "bit_math.h"

void TIMER0_Init(timer0_mode_t mode , timer0_prescaller_t prescaller);
void TIMER0_OC0Mode(oc0_mode_t);
void TIMER0_SetTimerReg(u8 val);
void TIMER0_SetCompareVal(u8 val);
void TIMER0_EnableOVInt(void);
void TIMER0_DisableOVInt(void);
void TIMER0_EnableCTCInt(void);
void TIMER0_DisableCTCInt(void);
void TIMER0_SetOVCallBack(fptr ptr ) ;
void TIMER0_SetCTCCallBack(fptr ptr ) ;

#endif /* TIMER_H_ */