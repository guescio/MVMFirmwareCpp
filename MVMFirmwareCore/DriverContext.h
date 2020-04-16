#pragma once
#include "hw.h"
#include "DebugIface.h"
typedef struct
{
	HW* hwi;
	DebugIfaceClass* dbg;
} DriverContext;