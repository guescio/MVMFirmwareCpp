// MVMCore.h

#ifndef _MVMCORE_h
#define _MVMCORE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ConfigManager.h"
#include "HAL.h"
#include "MVM_StateMachine.h"

class MVMCore
{
public:
	void Init();
	void Tick();
	bool DataAvailableOnUART0();
	String ReadUART0UntilEOL();
	bool WriteUART0(String s);
	bool SetParameter(String p, String v);
	String GetParameter(String p);

private:
	void InitConfiguration();
	HAL MVM_HAL;
	ConfigManagerClass CMC;
	t_SystemStatus sys_s;

	CircularBuffer  *MEM_Ppatient_LP;
	MVM_StateMachine MVM_SM;
	float old_delta_ppatient;

	void PPatient_Event();
	void FlowIn_Event();
};
#endif

