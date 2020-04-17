// ConfigManager.h

#ifndef _CONFIGMANAGER_h
#define _CONFIGMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Configuration.h"
#include "SystemStatus.h"


class ConfigManagerClass
{
 protected:


 public:
	 bool SetParameter(String p, String v);
	 String GetParameter(String p);
	 void Init(t_SystemStatus* _sys_s);
	 t_config core_config;

private:


	t_SystemStatus *sys_s;
};

#endif

