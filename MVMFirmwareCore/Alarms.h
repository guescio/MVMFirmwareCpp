// Alarms.h

#ifndef _ALARMS_h
#define _ALARMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "HAL.h"
#include "SystemStatus.h"
class AlarmClass
{
private:
	HAL* _HAL;
	t_SystemStatus *_sys_c;

public:
	void Action_OverPressureSecurity();
	void Init(HAL* hal, t_SystemStatus* sys_c);
};

#endif

