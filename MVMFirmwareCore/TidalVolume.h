// TidalVolume.h

#ifndef _TIDALVOLUME_h
#define _TIDALVOLUME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "HAL.h"

class TidalVolumeClass
{
private:
	HAL* _HAL;
	float TotalVolume;
	float InspVolumeSensirion;
	float InspVolumeVenturi;
	float ExpVolumeVenturi;
	float TidalCorrection=1;
	float FLUX;
	int Status=0;
	uint64_t last_meas_t;
	uint64_t last_meas_t_b;
	float FluxMax;

public:
	float liveFlux;
	float liveVolume;
	float currentTvEsp;
	float currentTvIsnp;
	float currentFluxPeak;
	void Init(HAL* hal);
	void PushDataSens(float flux_sens);
	void PushDataVenturi(float flux_venturi);
	void DoNewCycle();
	void DoExhale();
	void DoEndCycle();
};

#endif

//                  #     # ### 
//                  ##    #  #  
//                  # #   #  #  
//                  #  #  #  #  
//                  #   # #  #  
//                  #    ##  #  
//                  #     # ### 
//
// Nuclear Instruments 2020 - All rights reserved
// Any commercial use of this code is forbidden
// Contact info@nuclearinstruments.eu
