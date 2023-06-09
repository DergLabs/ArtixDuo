# ArtixDuo
A Dual Artix-7 FPGA board intended for developing Chip-Chip interface busses and advanced FPGA projects

**Overview**

This board is currently on Rev 2. As testing and bringup continue, more changes may be made. Original Altium Files have been provided along with a PDF schematic file. Vivado XDC files will be added. 

Two XDC files are needed, one for FPGA1 and one for FPGA0. They cannot be interchanged!

**SMC Fimrware**
The SMC (System Management Controller) is an RP2040 responsible for monitoring power, voltage rails and currents. It uses an i2C bus communicating with INA260 power monitor IC's present on all major FPGA voltage rails. Whene connected to a serial terminal the SMC will display the realtime voltage, curent and power of each rail. Tera Term works best on windows and Serial on MacOS. Make sure that the serial window is large enough to fit the entire message otherwise it will not print correctly. The SMC is also capable of the following: 
- Generate CLK signals for both FPGA's from (Tested and verified upto 200MHZ)
- Communicate to both FPGA's via SPI. !!! IF YOU DO USE THIS THEN YOU CANNOT USE THE SMC TO GENERATE FPGA CLOCKS !!!
- Display Board Status and othe information on i2C OLED (Coming in Rev 2)
- Enable/Disable each power rail

When the Board is plugged in, you must wait for the SMC to boot and flash its onboard LED 3 times. Once that is complete you can enable the main power supply by pressing the SMC user button. The onboard LED by the SMC will light up when the DC-DC is active.
The SMC firmware is in beta and more updates are to come.

**Onboard MCU**
The onboard MCU is also an RP2040. The MCU is connected to each FPGA with a 9-bit bus (1-bit for clk, 8-bits for data), and can be programmed to perform any functions the user would like. No firmware is provided for this chip as it's function is user specific.

**FT4232**
The FT4232 is a combination USB-JTAG and UART bridge. Two independent JTAG and UART busses go to each FPGA. Onboard MUX's are used to select between the FT4232 and the JTAG headders. Currently Vivado does not support using two independent JTAG busses on a single FT4232 :(, Only one FPGA can be used at a time and the other must be connected via the JTAG header. There are two onboard headers for selecting between the JTAG header and FT4232. When in the "1" position, the FT4232 is selected. When in the "0" position, the JTAG header is selected. 

**FPGA0 IO**
FPGA0 has acess to the following IO:
- 48 User IO pins available on the 0.1" headers. These IO pins pass through bi-directional 100Mb/s Buffers and should be able to reliably operate upto 50Mhz and potentialy beyond.
- 4x PMOD headers (32 IO total). These IO's also pass through bi-directional buffers.
- 4x 6.6Gb/s GTP Transceivers. These have been routed with 100 Ohm differential pairs  
- 1 XADC Input
- 100-bit Bus to FPGA1
- 9-bit Bus to MCU
- SPI Bus to SMC
- 4 User buttons
- 8 user LED's
- 512Mb Octal SPI PSRAM operating at upto 200Mhz. This is a DDR memory capable of upto 400MB/s (3.2Gb/s)

**FPGA1 IO**
FPGA1 has acess to the following IO:
- 48 User IO pins available on the 0.1" headers. These IO pins pass through bi-directional 100Mb/s Buffers and should be able to reliably operate upto 50Mhz and potentialy beyond.
- 4x PMOD headers (32 IO total). These IO's also pass through bi-directional buffers.
- Displayport RX and TX via 6.6Gb/s GTP Transceivers. These have been routed with 100 ohm differential pairs   
- 1 XADC Input
- 100-bit Bus to FPGA1
- 9-bit Bus to MCU
- SPI Bus to SMC
- 4 User buttons
- 8 user LED's

**Power**
A LTCC3370 is used to provide the 4 power rails for each FPGA (3.3V, 1.8V, 1.2V and 1.0V). Each rail is capable of supplying up to 2A. In the event that more power is needed, an addon board will be required to provide suplemental power. With the current Artix-7 35T chips, this should not be needed, however these chips are pin compatible with specific 50T and 75T parts. If these parts were to be used, suplemental power may be needed. 
The DC-DC converter is configured to operate at 2Mhz Burst Mode.

![ArtixDuo Top (Rev2)](https://imgur.com/InKgrNF.png)

![ArtixDuo Bottom (Rev2)](https://imgur.com/wn1rjKm.png)

![Assembled Board (Rev1)](https://imgur.com/jNDjfVh.jpg)
