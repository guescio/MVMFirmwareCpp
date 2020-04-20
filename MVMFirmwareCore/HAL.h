// HAL.h

#ifndef _HAL_h
#define _HAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "fw_board_razzeto_v3.h"
#include "fw_board_ni_v4.h"
#include "DebugIface.h"
#include "driver_5525DSO.h"
#include "driver_SFM3019.h"
#include "driver_VenturiFlowMeter.h"
#include "PressureLoop.h"
#include "CircularBuffer.h"

class HAL
{
	private:
		HW_V4 hwi;
		Sensor5525DSO drv_PLoop;
		Sensor5525DSO drv_PPatient;
		Sensor5525DSO drv_PVenturi;
		SensorSFM3019 drv_FlowIn;
		VenturiFlowMeter drv_FlowVenturi;
		PressureLoopClass PressureLoop;
		DriverContext _dc;
		CircularBuffer *MEM_PLoop;
		CircularBuffer *MEM_PPatient;
		CircularBuffer *MEM_FlowIn;
		CircularBuffer *MEM_FlowVenturi;


		uint64_t cycle_PLoop_LT;
		uint64_t cycle_PPatient_LT;
		uint64_t cycle_PVenturi_LT;
		uint64_t cycle_FlowIn_LT;
		float Tloop, Ploop;
		float Tpatient, Ppatient;
		float FlowIn, TFlowIn;
		float Tventuri, Pventuri;
		float FlowVenturi;
		
	public:
		DebugIfaceClass dbg;
		void Init();
		float GetPressureValve(int32_t Delay);
		float GetPressurePatient(int32_t Delay);
		float GetFlowInspire(int32_t Delay);
		float GetFlowVenturi(int32_t Delay);
		void SetInputValve(float value);
		void SetOutputValve(bool value);
		void GetInputValvePID(float *pid_slow, float *pid_fast);
		void SetBuzzer(bool value);
		void SetAlarmLed(bool value);
		void SetAlarmRele(bool value);
		float GetVolumeVenturi();
		float GetVolumeInput();
		void ResetVolumeVenturi();
		void ResetVolumeInput();
		bool DataAvailableOnUART0();
		String ReadUART0UntilEOL();
		bool WriteUART0(String s);
		uint64_t GetMillis();
		int64_t Get_dT_millis(uint64_t ms);

		std::function<void()> callback_ploop = NULL;
		std::function<void()> callback_ppatient = NULL;
		std::function<void()> callback_flowsens = NULL;
		std::function<void()> callback_venturi = NULL;

		void addHandler_PLoop(std::function<void()> callback)
		{
			callback_ploop = callback;
		}

		void addHandler_PPatient(std::function<void()> callback)
		{
			callback_ppatient = callback;
		}

		void addHandler_FlowSens(std::function<void()> callback)
		{
			callback_flowsens = callback;
		}

		void addHandler_FlowVenturi(std::function<void()> callback)
		{
			callback_venturi = callback;
		}


		void Tick();
};

#endif

