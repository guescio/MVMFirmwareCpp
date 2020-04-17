// 
// 
// 

#include "ConfigManager.h"
#include "FwVersion.h"
#include "generic_definitions.h"
#include "UtilsFn.h"

void ConfigManagerClass::Init(t_SystemStatus* _sys_s)
{
    sys_s = _sys_s;
    core_config.run = false;
    core_config.inhale_ms = 750;
    core_config.exhale_ms = 1250;
    core_config.BreathMode = M_BREATH_FORCED; //M_BREATH_ASSISTED;//;
    core_config.flux_close = 5;
    core_config.assist_pressure_delta_trigger = 15;
    core_config.target_pressure = 20;
    core_config.target_pressure_auto = core_config.target_pressure;
    core_config.target_pressure_assist = core_config.target_pressure;

    core_config.respiratory_rate = 15;
    core_config.respiratory_ratio = 0.66;
    core_config.inhale_ms = 60000.0 / core_config.respiratory_rate * (1 - core_config.respiratory_ratio);
    core_config.exhale_ms = 60000.0 / core_config.respiratory_rate * (core_config.respiratory_ratio);

    core_config.P = 70;
    core_config.I = 10;
    core_config.D = 0;

    core_config.P2 = 1.4;
    core_config.I2 = 0.4;
    core_config.D2 = 0;

    core_config.pid_limit = 0.65;

    core_config.pause_lg = false;
    core_config.pause_lg_timer = 0;

}

bool ConfigManagerClass::SetParameter(String p, String v)
{
    String strPatam = p;

    //Serial.println("CMD: " +  param.getValue() + " " +  value.getValue());

    if (strPatam == "run") {
        int numberValue = v.toInt();

        if (numberValue < 1)
            core_config.run = false;
        else
            core_config.run = true;

        return true;
    }

    if (strPatam == "mode") {
        int numberValue = v.toInt();
        if (numberValue == 0) {
            //Forced Mode
            core_config.BreathMode = M_BREATH_FORCED;
        }
        else {
            //Assisted Mode
            core_config.BreathMode = M_BREATH_ASSISTED;
        }
        return true;
    }

    if (strPatam == "rate") {
        float numberValue = v.toFloat();
        core_config.respiratory_rate = numberValue;
        core_config.inhale_ms = 60000.0 / core_config.respiratory_rate * (1 - core_config.respiratory_ratio);
        core_config.exhale_ms = 60000.0 / core_config.respiratory_rate * (core_config.respiratory_ratio);
        return true;
    }

    if (strPatam == "ratio") {
        float numberValue = v.toFloat();
        core_config.respiratory_ratio = numberValue;
        core_config.inhale_ms = 60000.0 / core_config.respiratory_rate * (1 - core_config.respiratory_ratio);
        core_config.exhale_ms = 60000.0 / core_config.respiratory_rate * (core_config.respiratory_ratio);
        return true;
    }

    if (strPatam == "assist_ptrigger") {
        float numberValue = v.toFloat();
        core_config.assist_pressure_delta_trigger = numberValue;
        return true;
    }

    if (strPatam == "assist_flow_min") {
        float numberValue = v.toFloat();
        core_config.flux_close = numberValue;
        return true;
    }

    if (strPatam == "ptarget") {
        float numberValue = v.toFloat();
        core_config.target_pressure_auto = numberValue;
        return true;
    }

    if (strPatam == "pressure_support") {
        float numberValue = v.toFloat();
        core_config.target_pressure_assist = numberValue;
        return true;
    }

    if (strPatam == "pid_p") {
        float numberValue = v.toFloat();
        core_config.P = numberValue;
        return true;
    }

    if (strPatam == "pid_i") {
        float numberValue = v.toFloat();
        core_config.I = numberValue;
        return true;
    }

    if (strPatam == "pid_d") {
        float numberValue = v.toFloat();
        core_config.D = numberValue;
        return true;
    }

    if (strPatam == "pid_p2") {
        float numberValue = v.toFloat();
        core_config.P2 = numberValue;
        return true;
    }

    if (strPatam == "pid_i2") {
        float numberValue = v.toFloat();
        core_config.I2 = numberValue;
        return true;
    }

    if (strPatam == "pid_d2") {
        float numberValue = v.toFloat();
        core_config.D2 = numberValue;
        return true;
    }

    if (strPatam == "pause_inhale") {
        int numberValue = v.toInt();
        core_config.pause_inhale = numberValue;
        return true;
    }

    if (strPatam == "pause_lg") {
        int numberValue = v.toInt();
        core_config.pause_lg = numberValue ? true : false;
        return true;
    }

    if (strPatam == "pause_lg_time") {
        int numberValue = v.toFloat();
        core_config.pause_lg_timer = numberValue * 1000.0;
        return true;
    }

    if (strPatam == "pause_lg_p") {
        int numberValue = v.toFloat();
        core_config.pause_lg_p = numberValue;
        return true;
    }

    if (strPatam == "pause_exhale") {
        int numberValue = v.toInt();
        core_config.pause_exhale = numberValue;
        return true;
    }

    if (strPatam == "pid_limit") {
        float numberValue = v.toFloat();
        core_config.pid_limit = numberValue;
        return true;
    }

    if (strPatam == "alarm_snooze") {
        int numberValue = v.toInt();
        //ResetAlarm(numberValue);
        return true;
    }

    if (strPatam == "alarm") {
        int numberValue = v.toInt();
        //TriggerAlarm(ALARM_GUI_ALARM);
        return true;
    }

    if (strPatam == "watchdog_reset") {
        int numberValue = v.toInt();
        //watchdog_time = millis();
        sys_s->ALARM_FLAG = sys_s->ALARM_FLAG & (~GenerateFlag(__ERROR_WDOG_PI));
        return true;
    }

    if (strPatam == "console") {
        int numberValue = v.toInt();
        core_config.__CONSOLE_MODE = numberValue != 0 ? true : false;
        return true;
    }

    if (strPatam == "timestamp") {
        int numberValue = v.toInt();
        core_config.__ADDTimeStamp = numberValue != 0 ? true : false;
        return true;
    }

    if (strPatam == "wdenable") {
        int numberValue = v.toInt();
        core_config.__WDENABLE = numberValue != 0 ? true : false;
        sys_s->ALARM_FLAG = sys_s->ALARM_FLAG & (~GenerateFlag(__ERROR_ALARM_PI));
        return true;
    }

    if (strPatam == "backup_enable") {
        int numberValue = v.toInt();
        core_config.backup_enable = numberValue ? true : false;
        return true;
    }

    if (strPatam == "backup_min_rate") {
        float numberValue = v.toFloat();
        numberValue = numberValue < 1 ? 1 : numberValue;
        core_config.backup_min_rate = numberValue;
        return true;
    }

    if (strPatam == "stats_clear") {
        //ResetStatsBegin();
        return true;
    }

    return false;
}
String ConfigManagerClass::GetParameter(String p)
{

    String strPatam = p;

    //Serial.println("CMD: " +  param.getValue() + " " +  value.getValue());

    if (strPatam == "pressure") {
        return "valore=" + String(sys_s->pLoop);
   
    }

    if (strPatam == "flow") {
        return "valore=" + String(sys_s->FlowIn);

    }

    if (strPatam == "o2") {
        return "valore=" + String(sys_s->last_O2);
        
    }

    if (strPatam == "bpm") {
        return "valore=" + String(sys_s->last_bpm);
    }

    if (strPatam == "backup") {
        return "valore=" + String(0);

    }

    if (strPatam == "tidal") {
        return "valore=" + String(sys_s->tVolume.TidalVolume);
    }

    if (strPatam == "peep") {
        return "valore=" + String(sys_s->last_peep);
    }

    if (strPatam == "temperature") {
        return "valore=" + String(sys_s->GasTemperature);
    }

    if (strPatam == "power_mode") {
        return "valore=" + String(sys_s->batteryPowered ? 1 : 0);
    }

    if (strPatam == "battery") {
        return "valore=" + String(sys_s->currentBatteryCharge);
    }

    if (strPatam == "version") {
        return "valore=" + String(_FIRMWARE_VERSION_);
    }

    if (strPatam == "alarm") {
        return "valore=" + String(sys_s->ALARM_FLAG);
    }

    if (strPatam == "warning") {
        return "valore=" + String(sys_s->WARNING_FLAG);
    }

    if (strPatam == "run") {
        return "valore=" + String(core_config.run ? 1 : 0);
    }

    if (strPatam == "mode") {
        return "valore=" + String(core_config.BreathMode == M_BREATH_ASSISTED ? 1 : 0);
    }
    if (strPatam == "rate") {
        return "valore=" + String(core_config.respiratory_rate);
    }
    if (strPatam == "ratio") {
        return "valore=" + String(core_config.respiratory_ratio);
    }
    if (strPatam == "assist_ptrigger") {
        return "valore=" + String(core_config.assist_pressure_delta_trigger);
    }
    if (strPatam == "assist_flow_min") {
        return "valore=" + String(core_config.flux_close);
    }
    if (strPatam == "ptarget") {
        return  "valore=" + String(core_config.target_pressure_auto);
    }
    if (strPatam == "pressure_support") {
        return  "valore=" + String(core_config.target_pressure_assist);
    }
    if (strPatam == "backup_enable") {
        return  "valore=" + String(core_config.backup_enable ? 1 : 0);

    }
    if (strPatam == "backup_min_rate") {
        return  "valore=" + String(core_config.backup_min_rate);
    }

    if (strPatam == "pause_lg") {
        return  "valore=" + String(core_config.pause_lg);
    }

    if (strPatam == "pause_lg_time") {
        return  "valore=" + String(core_config.pause_lg_timer / 1000.0);
    }

    if (strPatam == "pause_lg_p") {
        return  "valore=" + String(core_config.pause_lg_p);
    }
    if (strPatam == "all") {
        return "valore=" + String(sys_s->pPatient) 
            + "," + String(sys_s->tVolume.FLUX)
            + "," + String(sys_s->last_O2)
            + "," + String(sys_s->last_bpm)
            + "," + String(sys_s->tVolume.TidalVolume) 
            + "," + String(sys_s->last_peep)
            + "," + String(sys_s->GasTemperature) 
            + "," + String(sys_s->batteryPowered ? 1 : 0) 
            + "," + String(sys_s->currentBatteryCharge)
            + "," + String(sys_s->currentP_Peak)
            + "," + String(sys_s->currentTvIsnp)
            + "," + String(sys_s->currentTvEsp)
            + "," + String(sys_s->currentVM);
    }

    if (strPatam == "calib") {
       /* Serial.print("Valore=");
        for (int j = 0; j < N_PRESSURE_SENSORS; j++) {
            i2c_MuxSelect(pressure_sensor_i2c_mux[j]);
            float mean = 0;
            PRES_SENS_CT[j].ZERO = 0;
            for (int q = 0; q < 100; q++) {
                read_pressure_sensor(j);
                mean += pressure[j].last_pressure;
            }
            PRES_SENS_CT[j].ZERO = mean / 100;

            Serial.print(String(PRES_SENS_CT[j].ZERO) + ",");
        }
        Serial.println(" ");*/
    }

    if (strPatam == "calibv") {
        /*if (fabs(tidal_volume_c.ExpVolumeVenturi) > 0)
            tidal_volume_c.AutoZero = fabs(tidal_volume_c.InspVolumeVenturi) / fabs(tidal_volume_c.ExpVolumeVenturi);

        Serial.println("valore=" + String(tidal_volume_c.InspVolumeVenturi) + "," + String(tidal_volume_c.ExpVolumeVenturi) + "," + String(tidal_volume_c.AutoZero));
    
*/    }

    if (strPatam == "stats") {
        /*if (__stat_param.mean_cnt > 0) {
            float overshoot_avg = __stat_param.overshoot_avg / __stat_param.mean_cnt;
            float overshoot_length_avg = __stat_param.overshoot_length_avg / __stat_param.mean_cnt;
            float final_error_avg = __stat_param.final_error_avg / __stat_param.mean_cnt;
            float t1050_avg = __stat_param.t1050_avg / __stat_param.mean_cnt;
            float t1090_avg = __stat_param.t1090_avg / __stat_param.mean_cnt;
            float tpeak_avg = __stat_param.tpeak_avg / __stat_param.mean_cnt;
            float t9010_avg = __stat_param.t9010_avg / __stat_param.mean_cnt;
            float t9050_avg = __stat_param.t9050_avg / __stat_param.mean_cnt;
            float peep_avg = __stat_param.peep_avg / __stat_param.mean_cnt;
            float t10_avg = __stat_param.t10_avg / __stat_param.mean_cnt;
            float time_to_peak_avg = __stat_param.time_to_peak_avg / __stat_param.mean_cnt;
            float flux_peak_avg = __stat_param.flux_peak_avg / __stat_param.mean_cnt;
            float flux_t1090_avg = __stat_param.flux_t1090_avg / __stat_param.mean_cnt;
            float flux_t9010_avg = __stat_param.flux_t9010_avg / __stat_param.mean_cnt;

            Serial.println("valore=overshoot_avg:" + String(overshoot_avg)
                + ",overshoot_length_avg:" + String(overshoot_length_avg)
                + ",final_error:" + String(final_error_avg)
                + ",t1050_avg:" + String(t1050_avg)
                + ",t1090_avg:" + String(t1090_avg)
                + ",tpeak_avg:" + String(tpeak_avg)
                + ",t9010_avg:" + String(t9010_avg)
                + ",t9050_avg:" + String(t9050_avg)
                + ",peep_avg:" + String(peep_avg)
                + ",t10_avg:" + String(t10_avg)
                + ",time_to_peak_avg:" + String(time_to_peak_avg)
                + ",flux_peak_avg:" + String(flux_peak_avg)
                + ",flux_t1090_avg:" + String(flux_t1090_avg)
                + ",flux_t9010_avg:" + String(flux_t9010_avg));
        }
        else {
            Serial.println("valore=no_data");
        }*/
    }


    return "valore=ERROR:Invalid Command Argument";
}


