# Internet of Borg v2 (WIP)
---
## Project Info
Internet of Borg is an idea to repurpose a standard water cooler to dispense Borg and have the ability to rate limit drinkers based on how much they have drank. There are lots of ideas for future major releases, but this version seeks to be able to:
- [] Detect when a user is trying to dispense Borg
- [] Limit how much can be dispensed at a time using a servo controller valve
- [] Keep track of how much has been dispensed in total (for low liquid level alerts)

Future versions of the project hope to be able to:
- Keep track of how much each user has drank (through on-cup RFID)
- Determine how much to rate limit by roughly calculating a user's BAC
- OTA updates (possibly reincorporating some BlynkIO functionality for use with an app)
- Multiple drink availability by utilizing both the hot and cold side of the water cooler seperately (hot water side might dispense room temperature water while the cold side dispenses alcoholic beverages)

Possible applications might include:
- Automatic bar payment (link cup ID to payment method to easily and automatically charge a user for amount dispensed)
- Stop users from getting too drunk (limit to a certain BAC)

Internet of Borg v1 (never finished) used a solenoid to perform dispense limiting which never worked because of the minimum working pressure required by the solenoid valve. Additionally, IoB v1 used BlynkIO and had a ton of unnecesary code. 
Internet of Borg v2 is almost a complete rewrite:
- No BlynkIO
- (Less) unnecesary code
- Easier UX for dispensing

Most importantly, IoB v2 will use a servo controlled ball valve instead of a solenoid valve in order to provide minimal flow restriction. More info on this in the hardware section.

## Software Components:
The general software layout is as follows:
| File | Description |
| --------- | ------------------- |
| Main.cpp | Contains the main setup and loop functions |
| fun.h | Contains the project functions |
| include.h | Contains include paramters |
| io.h | Contains pin defintions and pinMode setup |
| settings.h | Contains variables that the user may want to change |

On IoB v1, serial messages were sent over BlynkIO. For this project I will be using standard Serial over the ESP microUSB port. 

On IoB v1, drink dispensing was triggered by the user pressing the button which would open the valve and shut the valve by a timeout or after the dispense limit was reached, whichever came first. On IoB v2, drink dispensing is simply triggered by the flow sensor, indicating that a user has begun to dispense a drink. This means the valve will be left normally open and will only interrupt the flow if a rate limit condition is met, in which case it will close the valve and wait for a delay before resetting the state. The state will also be able to be reset by pressing the button, which will reopen the valve. In the future with cup ID technology, the valve will be normally closed and will automatically open when a cup is presented and its embedded RFID is read and validated. The valve will close when the cup is removed from the spigot area or when the limit is reached, whichever comes first.

## Hardware Components:
Another major change from IoB v1 is the new custom PCB. The schematic files will be included in the hw folder along with a hardware readme if I ever get around to making that.
For now, the hardware consists of:
| Module | Description |
| ------ | ----------- |
| 2x LM7805 5v regulators | Used to low voltage circuitry components. One regulator is for the microcontroller and the other is for the accessories (dropping from 12v to 5v generates a fair bit of heat so two regulators to spread the heat production) |
| Node MCU V3 ESP8266 | Microcontroller. Picked because it was on hand and will work fine for this |
| MP6500 Stepper Driver | Great little stepper driver which is used to control the servo controlled valve |
| RGB LED Pushbutton | An overpriced pushbutton with discreet RGB LEDs. Only electronic user input |
| LED Tape | Used to illuminate the dispenser valves. This is an individually addressable 3 wire LED tape |
| Flow sensor | A flow sensor that I found on AliExpress that outputs pulses from an encoder turned by the flow of liquid |

The servo controller valve is a WIP and I will include more details when I flush them out but it will be a standard stepper motor coupled to a (food safe) ball valve and a 3D printed coupler and mount.