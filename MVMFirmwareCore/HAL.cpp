// 
// 
// 


#define SCHEDULER_TIMER_PLOOP			5
#define SCHEDULER_TIMER_PPATIENT		20
#define SCHEDULER_TIMER_FLOWIN			20
#define SCHEDULER_TIMER_PVENTURI		20
#define SCHEDULER_TIMER_ADC				1000
#define SCHEDULER_TIMER_SUPERVISOR		1000



#include "HAL.h"
#include "fw_board_razzeto_v3.h"
#include <functional>

void HAL::Init()
{

	hwi.Init();
	dbg.Init(DBG_INFO, &hwi);
	_dc.hwi = &hwi;
	_dc.dbg = &dbg;
	drv_PLoop.Init(IIC_PS_0, DS_01, OVS_1024, &_dc);
	drv_PPatient.Init(IIC_PS_1, DS_01, OVS_1024, &_dc);
	drv_PVenturi.Init(IIC_PS_2, DS_01, OVS_1024, &_dc);
	drv_FlowVenturi.Init(SpiroquantH_R122P04);

	drv_FlowIn.Init(IIC_FLOW1, &_dc);
	PressureLoop.Init(2, 10, &_dc);

	MEM_PLoop = new CircularBuffer(4);
	MEM_PPatient = new CircularBuffer(4);
	MEM_FlowIn = new CircularBuffer(4);
	MEM_FlowVenturi = new CircularBuffer(4);
	MEM_PVenturi = new CircularBuffer(8);

	cycle_PLoop_LT = hwi.GetMillis();
	cycle_PPatient_LT = hwi.GetMillis();
	cycle_FlowIn_LT = hwi.GetMillis();
	cycle_PVenturi_LT = hwi.GetMillis();
	cycle_ADC_LT = hwi.GetMillis();
	cycle_Supervisor_LT = hwi.GetMillis();

	//hwi->addHandler(std::bind(&HAL::Callback, this, 1));
}
/*
void HAL::Callback(int x)
{
	dbg->DbgPrint(DBG_CODE, DBG_CRITICAL, String((int32_t)hwi->GetMillis()) + " - CALLBACK CALLED " + String(x));
}*/

void HAL::Tick()
{
	hwi.Tick();
	PressureLoop.Tick();
	hwi.PWMSet(PWM_PV1,PressureLoop.GetValveControl());
	
	if (hwi.Get_dT_millis(cycle_PLoop_LT)> SCHEDULER_TIMER_PLOOP)
	{
		cycle_PLoop_LT = hwi.GetMillis();
		drv_PLoop.asyncMeasure();
		dbg.DbgPrint(DBG_CODE, DBG_VALUE, String((int32_t)hwi.GetMillis()) + " - Start Measure");
	}
	else
	if (hwi.Get_dT_millis(cycle_FlowIn_LT) > SCHEDULER_TIMER_FLOWIN)
	{		
		cycle_FlowIn_LT = hwi.GetMillis();
		drv_FlowIn.doMeasure(&FlowIn, &TFlowIn);
		MEM_FlowIn->PushData(FlowIn);
		dbg.DbgPrint(DBG_CODE, DBG_VALUE, String((int32_t)hwi.GetMillis()) + " - Flow: " + String(FlowIn));
		if (callback_flowsens)
			callback_flowsens();
	}
	else
	if (hwi.Get_dT_millis(cycle_PPatient_LT) > SCHEDULER_TIMER_PPATIENT)
	{
		cycle_PPatient_LT = hwi.GetMillis();
		drv_PPatient.asyncMeasure();

	}
	else
	if (hwi.Get_dT_millis(cycle_PVenturi_LT) > SCHEDULER_TIMER_PVENTURI)
	{
		cycle_PVenturi_LT = hwi.GetMillis();
		drv_PVenturi.asyncMeasure();
	}
	else
	if (hwi.Get_dT_millis(cycle_ADC_LT) > SCHEDULER_TIMER_ADC)
	{
		cycle_ADC_LT = hwi.GetMillis();

	}
	else
	if (hwi.Get_dT_millis(cycle_Supervisor_LT) > SCHEDULER_TIMER_SUPERVISOR)
	{
		cycle_Supervisor_LT = hwi.GetMillis();
	}
	else
	if (drv_PLoop.asyncGetResult(&Ploop, &Tloop))
	{
		MEM_PLoop->PushData(Ploop);
		PressureLoop.SetPressure(PRESSURE_VALVE, Ploop);
		dbg.DbgPrint(DBG_CODE, DBG_VALUE, String((int32_t)hwi.GetMillis()) + " - Ploop: " + String(Ploop));
		if (callback_ploop)
			callback_ploop();
	}
	else
	if (drv_PPatient.asyncGetResult(&Ppatient, &Tpatient))
	{
		MEM_PPatient->PushData(Ppatient);
		PressureLoop.SetPressure(PRESSURE_PATIENT, Ppatient);
		dbg.DbgPrint(DBG_CODE, DBG_VALUE, String((int32_t)hwi.GetMillis()) + " - PPatient: " + String(Ppatient));
		if (callback_ppatient)
			callback_ppatient();
	}
	else
	if (drv_PVenturi.asyncGetResult(&Pventuri, &Tventuri))
	{
		FlowVenturi = drv_FlowVenturi.GetFlow(Pventuri, Tventuri);
		MEM_FlowVenturi->PushData(FlowVenturi);
		MEM_PVenturi->PushData(Pventuri);
		dbg.DbgPrint(DBG_CODE, DBG_VALUE, String((int32_t)hwi.GetMillis()) + " - PVenturi: " + String(Pventuri) + " - FlowVenturi: " + String(FlowVenturi));
		if (callback_venturi)
			callback_venturi();
	}
	else
	{
		//ADC GET
	}

}


float HAL::GetPressureValve(int32_t Delay)
{
	return MEM_PLoop->GetData(Delay);
}
float HAL::GetPressurePatient(int32_t Delay)
{
	return MEM_PPatient->GetData(Delay);
}
float HAL::GetFlowInspire(int32_t Delay)
{
	return MEM_FlowIn->GetData(Delay);
}
float HAL::GetFlowVenturi(int32_t Delay)
{
	return MEM_FlowVenturi->GetData(Delay);
}
float HAL::GetPVenturi(int32_t Delay)
{
	return MEM_PVenturi->GetData(Delay);
}
void HAL::SetInputValve(float value)
{
	PressureLoop.SetTargetPressure(value);
}
void HAL::SetOutputValve(bool value)
{
	hwi.IOSet(GPIO_PV2, value);
}
void HAL::SetBuzzer(bool value)
{
	hwi.IOSet(GPIO_BUZZER, value);
}
void HAL::SetAlarmLed(bool value)
{
	hwi.IOSet(GPIO_LED, value);
}
void HAL::SetAlarmRele(bool value)
{
	hwi.IOSet(GPIO_RELEALLARM, value);
}

float HAL::GetVolumeVenturi()
{
	return drv_FlowVenturi.GetIntegral();
}
float HAL::GetVolumeInput()
{
	return drv_FlowIn.GetIntegral();
}
void HAL::ResetVolumeVenturi()
{
	drv_FlowVenturi.ResetIntegral();
}
void HAL::ResetVolumeInput()
{
	drv_FlowIn.ResetIntegral();
}

bool HAL::DataAvailableOnUART0()
{
	return hwi.DataAvailableOnUART0();
}

String HAL::ReadUART0UntilEOL()
{
	return hwi.ReadUART0UntilEOL();
}

bool HAL::WriteUART0(String s)
{
	return hwi.WriteUART0(s);
}

void HAL::GetInputValvePID(float* pid_slow, float* pid_fast)
{
	PressureLoop.GetPidMonitor(pid_slow, pid_fast);
}

uint64_t HAL::GetMillis()
{
	return hwi.GetMillis();
}

int64_t HAL::Get_dT_millis(uint64_t ms)
{
	return hwi.Get_dT_millis(ms);
}

float HAL::ZeroPressureSensor(t_pressure_sensor ps)
{
	
	switch (ps)
	{
	case PS_LOOP:
		return drv_PLoop.doZero();
		break;
	case PS_PATIENT:
		return drv_PPatient.doZero();
		break;
	case PS_VENTURI:
		return drv_PVenturi.doZero();
		break;
	default:
		return 0;
		break;
	}
}

void HAL::ConfigureInputValvePID(float P, float I, float D, float P2, float I2, float D2, float pid_limit)
{
	PressureLoop.ConfigurePidSlow(P2, I2, D2, pid_limit);
	PressureLoop.ConfigurePidFast(P, I, D);
}

void HAL::delay_ms(float ms)
{
	hwi.__delay_blocking_ms((uint32_t) ms);
}