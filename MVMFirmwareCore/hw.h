// hw.h

#ifndef _HW_h
#define _HW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "generic_definitions.h"


class HW {
public:
   
       
    
        virtual bool Init();
        virtual bool I2CWrite(uint8_t address, uint8_t* wbuffer, int wlength, bool stop);
        virtual bool I2CRead(uint8_t address, uint8_t* wbuffer, int wlength, uint8_t* rbuffer, int rlength, bool stop);
        virtual bool I2CRead(uint8_t address, uint8_t* rbuffer, int rlength, bool stop);
        virtual bool PWMSet(hw_pwm id, float value);
        virtual bool IOSet(hw_gpio id, bool value);
        virtual bool IOGet(hw_gpio id, bool* value);
        virtual void __delay_blocking_ms(uint32_t ms);
        virtual void PrintDebugConsole(String s);
        virtual void PrintLineDebugConsole(String s);
        virtual uint64_t GetMillis();
        virtual int64_t Get_dT_millis(uint64_t ms);

private:
    
};

#endif

