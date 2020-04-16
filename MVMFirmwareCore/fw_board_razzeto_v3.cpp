// 
// 
// 

#include "fw_board_razzeto_v3.h"
#include <Wire.h>

#define VALVE_IN_PIN		A0 
#define VALVE_OUT_PIN		32 

#define BUZZER				12
#define ALARM_LED			13

#define TCAADDR 0x70


bool HW_V3::Init()
{
	Serial.begin(115200);
	

	ledcSetup(0, 10000, 12);
	ledcAttachPin(VALVE_IN_PIN, 0);
	ledcWrite(0, 0);

	digitalWrite(VALVE_OUT_PIN, LOW);
	digitalWrite(ALARM_LED, LOW);
	digitalWrite(BUZZER, LOW);

	pinMode(VALVE_OUT_PIN, OUTPUT);
	pinMode(ALARM_LED, OUTPUT);
	pinMode(BUZZER, OUTPUT);

	Wire.begin();

	for (int i = 0; i < 8; i++) {
		i2c_MuxSelect(i);
		Serial.println("SCAN I2C BUS: " + String(i));
		__service_i2c_detect();
	}

}

bool HW_V3::I2CWrite(uint8_t address, uint8_t* wbuffer, int wlength, bool stop)
{
	uint8_t result;
	Wire.beginTransmission(address);
	for (int i=0;i< wlength; i++)
		Wire.write(wbuffer[i]); 
	result = Wire.endTransmission();

	if (result != 0)
		return false;
	else
		return true;
}
bool HW_V3::I2CRead(uint8_t address, uint8_t* wbuffer, int wlength, uint8_t* rbuffer, int rlength, bool stop)
{
	uint8_t count;
	uint8_t result;
	Wire.beginTransmission(address);
	for (int i = 0;i < wlength; i++)
		Wire.write(wbuffer[i]);
	result = Wire.endTransmission();
	if (result != 0)
		return false;
	count = Wire.requestFrom((uint16_t)address, (uint8_t) rlength, stop);
	if (count < rlength)
		return false;

	for (int i = 0;i < rlength; i++)
	{
		rbuffer[i] = Wire.read();
	}

	return true;
}

bool HW_V3::I2CRead(uint8_t address, uint8_t* rbuffer, int rlength, bool stop)
{
	uint8_t count;

	count = Wire.requestFrom((uint16_t)address, (uint8_t)rlength, stop);

	if (count < rlength)
		return false;


	for (int i = 0;i < rlength; i++)
	{
		rbuffer[i] = Wire.read();
	}

	return true;
}
bool HW_V3::PWMSet(hw_pwm id, float value)
{

	if ((value < 0) || (value > 100.0)) return false;

	switch (id)
	{
		case PWM_PV1:
			uint32_t v = (uint32_t)value * 4095.0 / 100.0;
			ledcWrite(0, v);
			break;

	}


	return true;
}
bool HW_V3::IOSet(hw_gpio id, bool value)
{
	switch (id)
	{
		case GPIO_PV2:
			digitalWrite(VALVE_OUT_PIN, LOW);
			break;
		case GPIO_BUZZER:
			digitalWrite(BUZZER, LOW);
			break;
		case GPIO_LED:
			digitalWrite(ALARM_LED, LOW);
			break;

		default:
			return false;
			break;
	}
	return true;
}
bool HW_V3::IOGet(hw_gpio id, bool* value)
{
	switch (id)
	{
		case GPIO_PV2:
			*value = digitalRead(VALVE_OUT_PIN);
			break;
		case GPIO_BUZZER:
			*value = digitalRead(BUZZER);
			break;
		case GPIO_LED:
			*value = digitalRead(ALARM_LED);
			break;

		default:
			return false;
			break;
	}
	return true;
}

void HW_V3::__delay_blocking_ms(uint32_t ms)
{
	delay(ms);
}

void HW_V3::PrintDebugConsole(String s)
{
	Serial.print(s);
}

void HW_V3::PrintLineDebugConsole(String s)
{
	Serial.println(s);
}

uint64_t HW_V3::GetMillis()
{
	return (uint64_t) millis();
}
int64_t HW_V3::Get_dT_millis(uint64_t ms)
{
	return (int64_t)(millis() - ms);
}


void HW_V3::__service_i2c_detect()
{
	byte error, address;
	int nDevices;
	Serial.println("Scanning... I2C");
	nDevices = 0;
	for (address = 1; address < 127; address++) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if (error == 0) {
			Serial.print("I2C device found at address 0x");
			if (address < 16) {
				Serial.print("0");
			}
			Serial.println(address, HEX);
			nDevices++;
		}
		else if (error == 4) {
			Serial.print("Unknow error at address 0x");
			if (address < 16) {
				Serial.print("0");
			}
			Serial.println(address, HEX);
		}
	}
	if (nDevices == 0) {
		Serial.println("No I2C devices found\n");
	}
	else {
		Serial.println("done\n");
	}
}


void HW_V3::i2c_MuxSelect(uint8_t i)
{
	if (i > 7)
		return;

	Wire.beginTransmission(TCAADDR);
	Wire.write(1 << i);
	Wire.endTransmission();
}
