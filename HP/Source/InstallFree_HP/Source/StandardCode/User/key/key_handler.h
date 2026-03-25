#ifndef __KEY_HANDLER_H__
#define __KEY_HANDLER_H__

U8 IsValidKeyCondition(U16 mu16Key);
void* GetKeyEventList(void);

U8 GetKeyEventListSize(void);
U8 SetSelectWater( U8 mu8Id );
U8 SetSelectWaterHot( U8 mu8Id );

U8 GetAllLedStart(void);

#endif /* __KEY_HANDLER_H__ */
