// fw_board_razzeto_v3.h

#ifndef _FW_BOARD_RAZZETO_V3_h
#define _FW_BOARD_RAZZETO_V3_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"    
   
#else
	#include "WProgram.h"
#endif





    #include "hw.h"
class HW_V3 : public HW {
public:
    

    bool Init();
    bool I2CWrite(uint8_t address, uint8_t* wbuffer, int wlength, bool stop);
    bool I2CRead(uint8_t address, uint8_t* wbuffer, int wlength, uint8_t* rbuffer, int rlength, bool stop);
    bool I2CRead(uint8_t address, uint8_t* rbuffer, int rlength, bool stop);
    bool PWMSet(hw_pwm id, float value);
    bool IOSet(hw_gpio id, bool value);
    bool IOGet(hw_gpio id, bool* value);
    void PrintDebugConsole(String s);
    void PrintLineDebugConsole(String s);
    void __delay_blocking_ms(uint32_t ms);
    uint64_t GetMillis();
    int64_t Get_dT_millis(uint64_t ms);

private:
    void __service_i2c_detect();
    void i2c_MuxSelect(uint8_t i);
};


#endif

