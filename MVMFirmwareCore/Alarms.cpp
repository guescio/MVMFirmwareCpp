// 
// 
// 

#include "Alarms.h"


void AlarmClass::Action_OverPressureSecurity()
{
	_sys_c->in_over_pressure_emergency = true;
	_HAL->SetOutputValve(true);
}
void AlarmClass::Init(HAL* hal, t_SystemStatus* sys_c)
{
	_sys_c = sys_c;
	_HAL = hal;
}