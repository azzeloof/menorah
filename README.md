# menorah
A PCB menorah!
This is a work in progress, though I've ordered boards so I hope the hardware is correct. The majority of the circuit is copied from [the snowflake ornament I worked on last year](https://github.com/azzeloof/snowflake), but some parts of this circuit (the pinout of the programming header) are untested.

BOM will be added soon, though the parts cost should be sub-$20 (excluding PCB). You'll need an AVR programmer too (though I think you can use an Arduino).

Firmware will be added soon also. I wanted to post this as soon as I finished the hardware in case anybody wants to make one in time for Hanukkah!

# hardware
The board is a somple two-layer PCB. I ordered from PCBWay, because they'll make boards with a blue solder mask and white siklscreen. I used lead-free HASL as a copper finish. Immersion silver might look good too, though it's expensive, it can tarnish, and takes longer to produce. Honestly I woulda probably gone with it if lead time wasn't an issue.
ENIG or hard gold would look good too if you'd rather go for that look.

If you want to make your own, you can take the gerbers from the hardware directory.

Controller is an ATtiny85, and power comes from a AAA battery pack that gets adhered to the back (it also acts as a support). LEDs are reverse-mounted to shine through the board. Resistor values in the schematic are set for blue LEDs, but I'll probably change them to red or yellow. Use whichever colors you'd like, just make sure to set the resistors appropriatley. 

# firmware
coming soon
