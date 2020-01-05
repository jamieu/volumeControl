# AV1 to Lumagen Volume Display

An Arduino sketch to read the current volume and mode settings from an AV1 preprocessor via the RS232 port and send them to a Lumagen XE over RS232 to be displayed as an OSD.

### Prerequisites

* Arduino mega 2560
* Each RS232 serial port requires a MAX2232 chip to adjust levels


### Pinouts for serial connections

* AV1 | serial port 1 | 19(RX), 18(TX)
* Lumagen XE | serial port 2 | 17(RX), 16(TX)

