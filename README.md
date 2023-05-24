# SpO2-measurement-with-PSoC
This program is intended to acquire the SpO2 (blood oxygen saturation) value using a PSoC 5LP. 

The design has been made assuming that you have at your disposal a broadband photodiode used has a receiver and 2 LEDs, one RED and the other infrared.  Specifically, I have used the model SFH7072 from OSRAM. However, you can use any other.

If you want to use two photodiodes, you can modify the design by adding an additional input GPIO and controlling which one is used in each occasion by means of a MUX component.
