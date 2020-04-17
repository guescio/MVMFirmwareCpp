// CircularBuffer.h
#include <stdint.h>

#ifndef _CIRCULARBUFFER_h
#define _CIRCULARBUFFER_h

class CircularBuffer {

private:
	float* buffer;
	int _size;
public:
	CircularBuffer(int32_t size);
	~CircularBuffer();
	void PushData(float data);
	float GetData(int32_t delay);
};


#endif

