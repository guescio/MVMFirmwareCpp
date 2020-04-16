// PressureLoop.h

#ifndef _PRESSURELOOP_h
#define _PRESSURELOOP_h
#include "generic_definitions.h"

class PressureLoopClass
{
 protected:


 public:
	void init(int32_t LoopRatio);
    void Tick();
    void SetPressure(t_pressure_selector ps, float pressure);
    void SetTargetPressure(float pressure);
    void ConfigurePidSlow(float P, float I, float D);
    void ConfigurePidFast(float P, float I, float D);
    void GetPidSlow(float *P, float *I, float *D);
    void GetPidFast(float *P, float *I, float *D);
    void SetPidFilter(float fast, float slow);
    void GetPidFilter(float *fast, float *slow);

private:
    float _PID_P2;
    float _PID_I2;
    float _PID_D2;

    float _PID_P;
    float _PID_I;
    float _PID_D;

    float _pid_limit;

    float _Pset;
    float _pressure_valve;
    float _pressure_patient;

    int32_t _LoopRatio;
    
    int32_t LoopCounter;

    float fast_pid_set = 0;

    float _filter_fast;
    float _filter_slow;

    float _ValvePWM;

    void PID_SLOW_LOOP();
    void PID_FAST_LOOP();
};


#endif

