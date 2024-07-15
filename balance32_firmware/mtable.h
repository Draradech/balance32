//ENTRY(ID,  var,              rightshift,       resolution, unit,  name,                        minvalue,    maxvalue  )

ENTRY('1', sensorData.voltage,          0,       0.0008,       "V", "solar voltage",                  0.0,         2.0  )
ENTRY('2', actuator.clockDiv,           0,       3.906e-3,      "", "clock div",                      0.0,      1000.0  )

ENTRY('a', sensorData.cpu[0],           0,       0.1,          "%", "cpu load 0",                     0.0,       100.0  )
ENTRY('s', sensorData.cpu[1],           0,       0.1,          "%", "cpu load 1",                     0.0,       100.0  )
ENTRY('d', sensorData.cpu[2],           0,       0.1,          "%", "cpu load 2",                     0.0,       100.0  )
ENTRY('f', sensorData.cpu[3],           0,       0.1,          "%", "cpu load 3",                     0.0,       100.0  )
ENTRY('g', sensorData.cpu[4],           0,       0.1,          "%", "cpu load 4",                     0.0,       100.0  )

ENTRY(0,   sensorData.voltage,          0,       0.0,          "-", "end of table",                   0.0,         0.0  )
