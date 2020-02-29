#include "kitdropper.h"

void kitdropperSetTo(uint8_t deg)
{
	Serial1.write(deg);
}
