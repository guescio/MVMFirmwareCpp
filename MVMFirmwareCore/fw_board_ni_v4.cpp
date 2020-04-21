// 
// 
// 

#include "fw_board_ni_v4.h"


#include <Wire.h>


#define VALVE_IN_PIN		A1 
#define VALVE_OUT_PIN		32 

#define BUZZER				21
#define ALARM_LED			17
#define ALARM_RELE			A12
#define BREETHE				4

#define TCAADDR 0x70


bool HW_V4::Init()
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

	iic_devs[0].t_device = IIC_PS_0;
	iic_devs[0].muxport = 0;
	iic_devs[0].address = 0x76;

	iic_devs[1].t_device = IIC_PS_1;
	iic_devs[1].muxport = 0;
	iic_devs[1].address = 0x77;

	iic_devs[2].t_device = IIC_PS_2;
	iic_devs[2].muxport = 1;
	iic_devs[2].address = 0x76;

	iic_devs[3].t_device = IIC_FLOW1;
	iic_devs[3].muxport = 1;
	iic_devs[3].address = 0x2E;

	iic_devs[4].t_device = IIC_ADC_0;
	iic_devs[4].muxport = 4;
	iic_devs[4].address = 0x48;

	iic_devs[5].t_device = IIC_SUPERVISOR;
	iic_devs[5].muxport = 3;
	iic_devs[5].address = 0x22;


	iic_devs[6].t_device = IIC_MUX;
	iic_devs[6].muxport = -1;
	iic_devs[6].address = 0x70;

	iic_devs[7].t_device = IIC_GENERAL_CALL_SENSIRION;
	iic_devs[7].muxport = 2;
	iic_devs[7].address = 0x00;


}

bool HW_V4::I2CWrite(t_i2cdevices device, uint8_t* wbuffer, int wlength, bool stop)
{
	uint8_t address;
	uint8_t result;
	t_i2cdev dev = GetIICDevice(device);
	address = dev.address;
	i2c_MuxSelect(dev.muxport);

	Wire.beginTransmission(address);
	for (int i = 0;i < wlength; i++)
		Wire.write(wbuffer[i]);
	result = Wire.endTransmission();

	if (result != 0)
		return false;
	else
		return true;
}
bool HW_V4::I2CRead(t_i2cdevices device, uint8_t* wbuffer, int wlength, uint8_t* rbuffer, int rlength, bool stop)
{
	uint8_t address;
	uint8_t count;
	uint8_t result;

	t_i2cdev dev = GetIICDevice(device);
	address = dev.address;
	i2c_MuxSelect(dev.muxport);

	Wire.beginTransmission(address);
	for (int i = 0;i < wlength; i++)
		Wire.write(wbuffer[i]);
	result = Wire.endTransmission();
	if (result != 0)
		return false;
	count = Wire.requestFrom((uint16_t)address, (uint8_t)rlength, stop);
	if (count < rlength)
		return false;

	for (int i = 0;i < rlength; i++)
	{
		rbuffer[i] = Wire.read();
	}

	return true;
}

bool HW_V4::I2CRead(t_i2cdevices device, uint8_t* rbuffer, int rlength, bool stop)
{
	uint8_t count;
	uint8_t address;
	t_i2cdev dev = GetIICDevice(device);
	address = dev.address;
	i2c_MuxSelect(dev.muxport);

	count = Wire.requestFrom((uint16_t)address, (uint8_t)rlength, stop);

	if (count < rlength)
		return false;


	for (int i = 0;i < rlength; i++)
	{
		rbuffer[i] = Wire.read();
	}

	return true;
}
bool HW_V4::PWMSet(hw_pwm id, float value)
{

	if ((value < 0) || (value > 100.0)) return false;

	switch (id)
	{
	case PWM_PV1:
		uint32_t v = (uint32_t)value * 4095.0 / 100.0;
		ledcWrite(0, v);
		if (v > 0)
			digitalWrite(BREETHE, HIGH);
		break;

	}


	return true;
}
bool HW_V4::IOSet(hw_gpio id, bool value)
{
	switch (id)
	{
	case GPIO_PV2:
		digitalWrite(VALVE_OUT_PIN, value ? HIGH : LOW);
		if (value==LOW)
			digitalWrite(BREETHE, LOW);
		break;
	case GPIO_BUZZER:
		digitalWrite(BUZZER, value ? HIGH : LOW);
		break;
	case GPIO_LED:
		digitalWrite(ALARM_LED, value ? HIGH : LOW);
		break;
	case GPIO_RELEALLARM:
		digitalWrite(ALARM_RELE, value ? HIGH : LOW);
		break;
	default:
		return false;
		break;
	}
	return true;
}
bool HW_V4::IOGet(hw_gpio id, bool* value)
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
	case GPIO_RELEALLARM:
		*value = digitalRead(ALARM_RELE);
		break;
	default:
		return false;
		break;
	}
	return true;
}

void HW_V4::__delay_blocking_ms(uint32_t ms)
{
	delay(ms);
}

void HW_V4::PrintDebugConsole(String s)
{
	Serial.print(s);
}

void HW_V4::PrintLineDebugConsole(String s)
{
	Serial.println(s);
}

void HW_V4::Tick()
{

	return;
}


bool HW_V4::DataAvailableOnUART0()
{
	return Serial.available();
}

bool HW_V4::WriteUART0(String s)
{
	Serial.println(s);
	return true;
}
String HW_V4::ReadUART0UntilEOL()
{
	//PERICOLO. SE IL \n NON VIENE INVIATO TUTTO STALLA!!!!
	return Serial.readStringUntil('\n');
}

uint64_t HW_V4::GetMillis()
{
	return (uint64_t)millis();
}
int64_t HW_V4::Get_dT_millis(uint64_t ms)
{
	return (int64_t)(millis() - ms);
}


void HW_V4::__service_i2c_detect()
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


void HW_V4::i2c_MuxSelect(uint8_t i)
{
	if (i > 7)
		return;

	if (i < 0)
		return;

	if (current_muxpos == i) return;

	current_muxpos = i;

	Wire.beginTransmission(TCAADDR);
	Wire.write(1 << i);
	Wire.endTransmission();

}

t_i2cdev HW_V4::GetIICDevice(t_i2cdevices device)
{
	for (int i = 0; i < IIC_COUNT; i++)
	{
		if (iic_devs[i].t_device == device)
		{
			return iic_devs[i];
		}
	}
}