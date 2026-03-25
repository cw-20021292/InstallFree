
#ifndef _USER_MAIN_H_
#define _USER_MAIN_H_

#include "Type_Define.h"

#define MODEL_CHP                           0
#define MODEL_CP                            1
#define MODEL_HP                            2
#define MODEL_CPI                           3
#define MODEL_CHPI                          4

void Delay(U16 mu8Time);
void Delay_ms(U16 mu8Time);

void User_Main(void);

#endif

