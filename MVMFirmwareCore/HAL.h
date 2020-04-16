// HAL.h

#ifndef _HAL_h
#define _HAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "hw.h"
#include "DebugIface.h"
#include "driver_5525DSO.h"
#include "driver_SFM3019.h"

class HAL
{
	private:
		HW *hwi;
		DebugIfaceClass *dbg;
		Sensor5525DSO *drv_PLoop;
		Sensor5525DSO *drv_PPatient;
		SensorSFM3019* drv_FlowIn;
		DriverContext _dc;
		uint64_t cycle_PLoop_LT;
		uint64_t cycle_PPatient_LT;
		uint64_t cycle_FlowIn_LT;
		float Tloop, Ploop;
		float Tpatient, Ppatient;

	public:
		HAL();
		void Tick();
};

#endif

