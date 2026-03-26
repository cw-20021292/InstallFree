#ifndef __HEATER_H__
#define __HEATER_H__

#define  HEATER_MODE_NONE     0
#define  HEATER_MODE_FORCED   1

void InitHeater(void);

void SetHeaterMode(U8 mu8Mode);
U8 GetHeaterMode(U8 mu8Mode);

void SetHeaterForcedOnOff(U8 mu8OnOff);
U8 GetHeaterOnOff(void);

void   ResetHeaterWifiOnTime(void);
U32   GetHeaterWifiOnTime(void);

U32   GetHeaterOnTime(void);
U32   GetHeaterOffTime(void);

U16 GetHeaterOnTimeDiagnosis(void);
void SetHeaterOnTimeDiagnosis(U32 mu32Time);

U8 GetStartSendHeaterWifiOnTime(void);
void SetStartSendHeaterWifiOnTime(U8 mu8Val);

void ControlHeater(U8 mu8OnOff);



#endif /* __HEATER_H__ */
