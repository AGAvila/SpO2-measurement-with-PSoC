# SpO2 Measurement With PSoC
This program is intended to acquire the SpO2 (blood oxygen saturation) value using a PSoC 5LP. 

## Values obtained:

The program will return the SpO2 value via UART communication. If the character 'a' is received, the system will start taking acquisitions and it will not stop until the character 's' is also received. The program will need to take at least 3 or 4 acquisition before the value obtain can be trust. Each acquisition takes about 8 seconds.

The values are obtained with a resolution of 16 bits. Since the UART communication allows a maximum of 9 bits, I have divided the transmission of the value in two parts of 8 bits each one.

## Physical aspect:

The design has been made assuming that you have at your disposal a broadband photodiode used has a receiver and 2 LEDs, one RED and the other infrared.  Specifically, I have used the model SFH7072 from OSRAM. However, you can use any other. If you want to use two photodiodes, you can modify the design by adding an additional input GPIO and controlling which one is used in each occasion by means of a MUX component.

Consider adapting the assigned pins depending on your specific hardware.

## Additional notes:

In the schematic there are two pins called "EN_1" and "EN_2", being labeled as "Ports power supply control". I used this pins due to my specific hardware, in other cases they could be deleted.
