#include "Global_Header.h"
#include "heater.h"

#define  MAX_TIME 60000UL // sec

typedef struct _heater_water_
{
    /* COMMAND */
    U8 Mode;         // Command mode
    U8 ForcedOnOff;  // Forced mode - onoff command

    U32 OnTime;      // @1sec
    U32 OffTime;     // @1sec

    U16 OnTimeMin;   // for diagnosis

    U8  StartSendWifiOnTime;     // ���� on-> ���� off ������ on time   wifi �۽�
    U32 OnTimeForWifi;              // @1sec On time for wifi
} Heater_T;

Heater_T  Heater;


void InitHeater(void)
{
    Heater.Mode         = HEATER_MODE_NONE;
    
    Heater.ForcedOnOff  = OFF;

    Heater.OnTime       = 0;
    Heater.OffTime      = 0;

    Heater.OnTimeMin       = 0;  
    Heater.OnTimeForWifi      = 0;
    Heater.StartSendWifiOnTime = FALSE;
}

void SetHeaterMode(U8 mu8Mode)
{
    Heater.Mode = mu8Mode;
}

U8 GetHeaterMode(U8 mu8Mode)
{
    return Heater.Mode;
}

void SetHeaterForcedOnOff(U8 mu8OnOff)
{
    Heater.ForcedOnOff = mu8OnOff;
}

U8 GetHeaterOnOff(void)
{
    if( Get_Heater_Status( HEATER_ID_HOT_TANK ) == TRUE )
    {
        return ON;
    }

    return FALSE;
}

void   ResetHeaterWifiOnTime(void)
{
    Heater.OnTimeForWifi = 0; 
}

U32   GetHeaterWifiOnTime(void)
{
    return Heater.OnTimeForWifi;   // @ 1sec
}

U32   GetHeaterOnTime(void)
{
    return Heater.OnTime;   // @ 1sec
}

U32   GetHeaterOffTime(void)
{
    return Heater.OffTime;
}

U16 GetHeaterOnTimeDiagnosis(void)
{
    return Heater.OnTimeMin;   
}

void SetHeaterOnTimeDiagnosis(U32 mu32Time)
{
    Heater.OnTimeMin = (U16)((mu32Time)/(60));   // Trans sec -> min
}

U8 GetStartSendHeaterWifiOnTime(void)
{
    return Heater.StartSendWifiOnTime;   
}

void SetStartSendHeaterWifiOnTime(U8 mu8Val)
{
    Heater.StartSendWifiOnTime = mu8Val;
}

static void StartSendHeaterWifiOnTime(void)
{
    if(Heater.OnTimeForWifi != 0)
    {
        Heater.StartSendWifiOnTime = TRUE; 
    }
}

void ControlHeater(U8 mu8OnOff)
{
    // if( Heater.Mode == HEATER_MODE_FORCED )
    // {
    //     mu8OnOff = Heater.ForcedOnOff;
    // }

    if( mu8OnOff == TRUE )
    {
        Set_HeaterPort( HEATER_ID_HOT_TANK, ON );

        if( Heater.OnTime < MAX_TIME )
        {
            Heater.OnTime++;
            // Heater.OnTimeForWifi++; // for Wifi
            // SetHeaterOnTimeDiagnosis(Heater.OnTime);    // Trans sec -> min (for diagnosis)
        }
        Heater.OffTime = 0;
    }
    else 
    {
        // StartSendHeaterWifiOnTime();  // For Wifi

        // Turn Off Heater
        Set_HeaterPort( HEATER_ID_HOT_TANK, OFF );

        // Count Off timer
        Heater.OnTime = 0;
        if( Heater.OffTime < MAX_TIME )
        {
            Heater.OffTime++;
        }
    }
}
