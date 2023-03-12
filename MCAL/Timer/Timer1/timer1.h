/*
 * timer1.h
 *
 * Created: 3/8/2023 11:14:13 AM
 *  Author: basem
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "timer1_reg.h"
#include "timer1_types.h"
#include "std_types.h"
#include "bit_math.h"

void TIMER1_Init(timer1_mode_t mode , timer1_prescaller_t prescaller,
				OCRA_mode_t OCRA_mode, OCRB_mode_t OCRB_mode);

void TIMER1_ICU_Edge(ICU_mode_t edge);
void TIMER1_Enable_ICU_NoiseCanceler(void);
void TIMER1_Disable_ICU_NoiseCanceler(void);

void TIMER1_Set_TCNT1Reg(u16 val);
void TIMER1_Set_OCR1AReg(u16 val);
void TIMER1_Set_OCR1BReg(u16 val);
void TIMER1_Set_ICR1Reg(u16 val);

void TIMER1_Enable_OV_Int(void);
void TIMER1_Disable_OV_Int(void);

void TIMER1_Enable_OCA_Int(void);
void TIMER1_Disable_OCA_Int(void);

void TIMER1_Enable_OCB_Int(void);
void TIMER1_Disable_OCB_Int(void);

void TIMER1_Enable_ICU_Int(void);
void TIMER1_Disable_ICU_Int(void);


/*
void TIMER1_Set_OV_CallBack(fptr ptr ) ;
void TIMER1_Set_CTC_CallBack(fptr ptr ) ;
*/
void TIMER1_Set_ICU_CallBack(fptr ptr ) ;






#endif /* TIMER1_H_ */