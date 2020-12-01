# menorah
A PCB menorah!
This is a work in progress, though I've ordered boards so I hope the hardware is correct. The majority of the circuit is copied from [the snowflake ornament I worked on last year](https://github.com/azzeloof/snowflake), but some parts of this circuit (the pinout of the programming header) are untested.

PCB aside, the total component cost comes to less than $10. You'll need an AVR programmer too (though I think you can use an Arduino).

Firmware will be added soon. I wanted to post this as soon as I finished the hardware in case anybody wants to make one in time for Hanukkah!

# hardware
*BOM Change* I made a mistake in the board layout. For the ATTiny85, I used the same footprint I used on the snowflake, which is a SMD footprint for a DIP-8 socket. I should have used a SOIC-8 footprint to accommodate the SMD ATTiny85 I chose. The BOM has been updated to include a socket and THT ATTiny85. The other (and probably better) approach would be to update the board layout to use the correct footprint.
The board is a sample two-layer PCB. I ordered from PCBWay, because they'll make boards with a blue solder mask and white siklscreen. I used lead-free HASL as a copper finish. Immersion silver might look good too, though it's expensive, it can tarnish, and takes longer to produce. Honestly I woulda probably gone with it if lead time wasn't an issue.
ENIG or hard gold would look good too if you'd rather go for that look.

If you want to make your own, you can take the gerbers from the hardware directory.
It can be [directly ordered from PCBWay](https://www.pcbway.com/project/shareproject/LED_Menorah.html) also.

Controller is an ATtiny85, and power comes from a AAA battery pack that gets adhered to the back (it also acts as a support). LEDs are reverse-mounted to shine through the board. Resistor values in the schematic are set for blue LEDs, but I'll probably change them to red or yellow. Use whichever colors you'd like, just make sure to set the resistors appropriatley. 

# firmware
coming soon
