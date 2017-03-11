# PowerMeter
PIC32MX based , ethernet enabled power meter for measuring mains power flows

The repository includes:

PIC32MX250 board design files in FreePCB format, this is called Multi485Driver as it is a legacy board.
PowerMeter adapter board.
Source code for power meter.

For further discussion see [Wiki](http://oakhousehomeautomation.wikidot.com/power-import-export-measurement)

# Setting up a project
To edit the hardware .fpc files, produce gerbers and so on a copy of FreePCB is needed, this can be obtained from [FreePCB](http://www.freepcb.com)

Software was build using Microchip MPLABX IDE version 3.35, xc32-gcc v1.42

After getting the source files a subfolder TCPIP should be created, and TCPIP related files should be copied there.
The command file CopyToTCPIP.cmd is provided to do this.
