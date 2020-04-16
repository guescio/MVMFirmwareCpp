/*
 Name:		MVMFirmwareCore.ino
 Created:	12/04/2020 12:23:43
 Author:	Andre
*/

// the setup function runs once when you press reset or power the board

#include "PressureLoop.h"
#include "driver_SFM3019.h"
#include "DebugIface.h"
#include "hw.h"
#include "driver_5525DSO.h"
#include "fw_board_razzeto_v3.h"
#include "hw_ard_esp32.h"
#include "HAL.h"

HAL *MVM;
void setup() {
    MVM = new HAL();
}

// the loop function runs over and over again until power down or reset
void loop() {
    MVM->Tick();
}
