// 
// 
// 

#include "HAL.h"
#include "fw_board_razzeto_v3.h"

HAL::HAL()
{
	hwi = (HW*) new HW_V3();
	hwi->Init();
	dbg = new DebugIfaceClass(DBG_ALL, hwi);
	_dc.hwi = hwi;
	_dc.dbg = dbg;
	drv_PLoop = new Sensor5525DSO(0x76, DS_01, OVS_1024, &_dc);
	drv_PLoop->Init();
	drv_PPatient = new Sensor5525DSO(0x77, DS_01, OVS_1024, &_dc);
	drv_PPatient->Init();
	drv_FlowIn = new SensorSFM3019(0x2E, &_dc);
	drv_FlowIn->Init();

	cycle_PLoop_LT = hwi->GetMillis();
	cycle_PPatient_LT = hwi->GetMillis();
	cycle_FlowIn_LT = hwi->GetMillis();
}

void HAL::Tick()
{
	/*
	if (hwi->Get_dT_millis(cycle_PLoop_LT)>1000)
	{
		cycle_PLoop_LT = hwi->GetMillis();
		drv_PLoop->asyncMeasure();
		dbg->DbgPrint(DBG_CODE, DBG_CRITICAL, String((int32_t)hwi->GetMillis()) + " - Start Measure");
		
	}*/
	if (hwi->Get_dT_millis(cycle_FlowIn_LT) > 1000)
	{
		float T, Flow;
		cycle_FlowIn_LT = hwi->GetMillis();
		drv_FlowIn->doMeasure(&Flow, &T);
		dbg->DbgPrint(DBG_CODE, DBG_CRITICAL, String((int32_t)hwi->GetMillis()) + " - Flow: " + String(Flow));

	}
	/*
	if (hwi->Get_dT_millis(cycle_PPatient_LT) > 20)
	{
		cycle_PPatient_LT = hwi->GetMillis();
		drv_PPatient->doMeasure(&Ppatient, &Tpatient);
		dbg->DbgPrint(DBG_CODE, DBG_CRITICAL, "Ploop: " + String(Ppatient));
	}*/
	
	if (drv_PLoop->asyncGetResult(&Ploop, &Tloop))
	{
		dbg->DbgPrint(DBG_CODE, DBG_CRITICAL, String((int32_t)hwi->GetMillis()) + " - Ploop: " + String(Ploop));
	}
}