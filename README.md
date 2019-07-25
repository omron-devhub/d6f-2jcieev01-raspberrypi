# d6f-2jcieev01-raspberrypi
It is a sample projects for OMRON **D6F** MEMS Flow Sensors with
evaluation kit **2JCIE-EV01-AR1**,
**2JCIE-EV01-FT1** and some Arduino boards.

## D6F-PH sensor series
A Compact, High-accuracy Differential
Pressure Sensor with Superior Resistance to Environments.


## D6F sensor series
can Measure Low-flow rate and
Reduce to Piping time by quick joint connection


## Description
this Arduino sample projects for acquiring data from sensors on 2JCIE-EV01.
sample projects output the sensor data to USB-Serial ports.

| example    | description           | baord |
|:----------:|:----------------------|:-----------------------|
| d6f-ph0025 | differential pressure | Raspberry-Pi ZERO-W |
| d6f-ph0505 | differential pressure | Raspberry-Pi ZERO-W |
| d6f-ph0550 | differential pressure | Raspberry-Pi ZERO-W |
| d6f-10     | for Air flow          | Raspberry-Pi ZERO-W |
| d6f-20     | for Air flow          | Raspberry-Pi ZERO-W |
| d6f-50     | for Air flow          | Raspberry-Pi ZERO-W |
| d6f-70     | for Air flow          | Raspberry-Pi ZERO-W |


## DEMO
sample output for D6F-10A7D

```
sensor output:  -0.17[L/min]
sensor output:   0.05[L/min]
sensor output:  -0.10[L/min]
```


## Installation
### Prerequisite
- gcc (pre-installed in standard Raspbian)


### Procedure
this procedure shows the procedure to use the sensors on
**2JCIE-EV01-RP1** .

1. download the archive from github [releases](releases) or
    [master](archive/2jcieev01-raspberrypi-master.zip)

    ```shell
    $ unzip 2jcieev01-raspberrypi-master.zip
    ```

    or, with git:

    ```shell
    $ git clone https://github.com/omron-devhub/d6f-2jcieev01-raspberrypi
    ```

2. make

    ```shell
    $ cd d6f-2jcieev01-raspberrypi-master
    $ make all
    ```

3. run

    ```shell
    $ ./d6f-ph0505
    ```

    ```shell
    $ ./d6f-20
    ```



## Links
- [Arduino samples for 2JCIE-01-AR1/FT1](https://github.com/omron-devhub/2jcieev01-arduino)
- [RaspberryPi samples for 2JCIE-01-RP1](https://github.com/omron-devhub/2jcieev01-raspberrypi)
- [Arduino sample for D6T on 2JCIE-01-AR1/FT1](https://github.com/omron-devhub/d6t-2jcieev01-arduino)
- [RaspberryPi sample for D6T on 2JCIE-01-RP1](https://github.com/omron-devhub/d6t-2jcieev01-raspberrypi)
- [Arduino sample for D6F on 2JCIE-01-AR1/FT1](https://github.com/omron-devhub/d6f-2jcieev01-arduino)
- [Arduino sample for B5W on 2JCIE-01-AR1/FT1](https://github.com/omron-devhub/b5w-2jcieev01-arduino)


## Licence
Copyright (c) OMRON Corporation. All rights reserved.

Licensed under the MIT License.

