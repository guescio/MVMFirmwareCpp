#pragma once

typedef struct
{
    float FLUX;
    float TidalVolume;
    float InspVolumeSensirion;
    float InspVolumeVenturi;
    float TidalCorrection;
    int TidalStatus;
    float ExpVolumeVenturi;
    float AutoZero;
} t_tidal_volume_c;


typedef struct
{
    float overshoot_avg;
    float overshoot_length_avg;
    float time_to_peak_avg;
    float final_error_avg;
    float t1050_avg;
    float t1090_avg;
    float tpeak_avg;
    float t9010_avg;
    float t9050_avg;
    float peep_avg;
    float t10_avg;
    float flux_peak_avg;
    float flux_t1090_avg;
    float flux_t9010_avg;

    float time_to_peak;
    float overshoot;
    float final_error;
    float t10a;
    float t50a;
    float t90a;
    float t10b;
    float t50b;
    float t90b;
    float overshoot_length;
    float flux_peak;
    float flux_t10a;
    float flux_t90a;
    float flux_t10b;
    float flux_t90b;

    int mean_cnt;
    uint32_t start_time;
    int phase;

} t_stat_param;

typedef struct
{
	float pLoop;
	float pPatient;
    float pPatient_low_passed;
	float FlowIn;
	float FlowVenturi;
    t_tidal_volume_c tVolume;

    float last_O2 = 21.7;
    float last_peep = 0;
    float last_bpm = 0;
    float averaged_bpm = 0;
    float GasTemperature = 0;

    bool batteryPowered = false;
    float currentBatteryCharge = 100;

    float currentP_Peak = 0;
    float currentTvIsnp = 0;
    float currentTvEsp = 0;
    float currentVM = 0;


    float PPatient_delta;
    float PPatient_delta2;
    float PPatient_lowpass;

    int dbg_trigger;
    float dgb_peaktime;
    float fluxpeak = 0;
    float pres_peak = 0;
    unsigned long peaktime = 0;

    float dt_veturi_100ms = 0;

    float pid_valvein_slow;
    float pid_valvein_fast;

    t_stat_param __stat_param;

    uint32_t ALARM_FLAG;
    uint32_t WARNING_FLAG;
} t_SystemStatus;