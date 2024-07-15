#include <string>
#include "MeasurementTable.h"

#define ENTRY(ID, var, rightshift, resolution, unit, name, minvalue, maxvalue) \
{(ID), (rightshift), (resolution), (unit), (name), (minvalue), (maxvalue)},

measurement_t measurementTable[] =
{
    #include "../balance32_firmware/mtable.h"
};

measurement_t parameterTable[] =
{
	#include "../balance32_firmware/ptable.h"
};
