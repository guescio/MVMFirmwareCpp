/*
 Name:		MVMFirmwareCore.ino
 Created:	12/04/2020 12:23:43
 Author:	Andre
*/

// the setup function runs once when you press reset or power the board

#include "driver_OxygenSensor.h"
#include "driver_ADS1115.h"
#include "TidalVolume.h"
#include "Alarms.h"
#include "MVM_StateMachine.h"
#include "ConfigManager.h"
#include "MVMCore.h"
#include <SimpleCLI.h>
#include "CircularBuffer.h"
#include "PressureLoop.h"
#include "driver_SFM3019.h"
#include "DebugIface.h"
#include "hw.h"
#include "driver_5525DSO.h"
#include "fw_board_razzeto_v3.h"
#include "hw_ard_esp32.h"
#include "HAL.h"
#include <SimpleCLI.h>

MVMCore MVM;

// Create CLI Object
SimpleCLI cli;
// Commands
Command param_set;
Command param_get;

void SetCommandCallback(cmd* c);
void GetCommandCallback(cmd* c);
void CliErrorCallback(cmd_error* e);
void InitConsoleInterface();

void setup() {

    InitConsoleInterface();
    MVM.Init();
}

// the loop function runs over and over again until power down or reset
void loop() {
    MVM.Tick();

    if (MVM.DataAvailableOnUART0()) {
        
        String input = MVM.ReadUART0UntilEOL();
        cli.parse(input);
    }
}


void InitConsoleInterface()
{
    cli.setOnError(CliErrorCallback); // Set error Callback
    param_set = cli.addCommand("set", SetCommandCallback);
    param_set.addPositionalArgument("param", "null");
    param_set.addPositionalArgument("value", "0");

    param_get = cli.addCommand("get", GetCommandCallback);
    param_get.addPositionalArgument("param", "null");
}


 void SetCommandCallback(cmd* c)
{
    Command cmd(c); 

    Argument param = cmd.getArgument("param");
    Argument value = cmd.getArgument("value");

    String strPatam = param.getValue();
    String strValue = value.getValue();

    if (MVM.SetParameter(strPatam, strValue))
        MVM.WriteUART0("valore=OK");
    else
        MVM.WriteUART0("valore=ERROR:Invalid Command Argument");

}
 void GetCommandCallback(cmd* c)
 {
     Command cmd(c);
     Argument param = cmd.getArgument("param");
     String strPatam = param.getValue();
     String r;
     MVM.WriteUART0(MVM.GetParameter(strPatam));
 
 }

void CliErrorCallback(cmd_error* e)
{
    CommandError cmdError(e);
    Serial.print("valore=ERROR: ");
    Serial.println(cmdError.toString());
}
