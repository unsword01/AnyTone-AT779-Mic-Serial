# AnyTone-AT779-Mic-Serial
Details of communications protocol between Mic and AnyTone AT779-UV Radio 
(also sold as Radioddity DB20-G and Retevis RA25)

Inspired by the desire to interface a legacy Packet Radio TNC to an AT779-UV Radio I discovered that the PTT on the Mic is not a simple contact closure switch, but instead pressing the PTT results in serial data being sent from the Mic to the Radio. I found this documented by Filip OK1GOD in his blog post: https://melik.cz/posts/sstv-first-steps

Based in the information in the blog post I created [an Arduino sketch](https://github.com/unsword01/AnyTone-AT779-Mic-Serial/blob/main/sketch_AnyTone_PTT_v4.ino) for a simple interface using an Arduino Nano which sends PTT and Keeplive messages to the Radio in response to an input pin on the Adurino module being pulled low (which would be the PTT line from the TNC).

In addition to the PTT the AT779-UV Mic has multiple buttons on its keypad as well as Up/Down buttons on the top. I captured the resulting byte strings sent when each button is pressed and also determined that when certain buttons a held down (i.e. a 'long press') there are additional byte strings sent, as well as additional data when the buttons are released.

Full details of the serial protocol are [in this document](https://github.com/unsword01/AnyTone-AT779-Mic-Serial/blob/main/AnyTone%20AT779-UV%20Mic%20Serial%20Protocol.pdf)

The Radio sends data back to the Mic over the serial link and I was able to determine that this is used to drive the color of the LED on the mic (Off/Red/Green). I created a [simple Arduino sketch to emulate the Radio](https://github.com/unsword01/AnyTone-AT779-Mic-Serial/blob/main/sketch_AnyTone_Serial_to_Mic_v1.ino) and test the control the Mic LED.

The serial data sent by the Radio does not appear to carry any information related to the current frequency or channel in use, nor anything which indicates if the Radio is in VFO or Memory mode.

KZ4TG
