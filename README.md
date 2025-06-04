# AnyTone-AT779-Mic-Serial
Details of communications protocol between AnyTone AT779-UV Mic and Radio

Inspired by the desire to interface a legacy Packet Radio TNC to AT779-Radio, when I discovered that the PTT is not a simple switch, but instead pressing the PTT switch results in serial data being sent from the mic to the radio. I found this documented by Filip OK1GOD in this blog post: https://melik.cz/posts/sstv-first-steps

Based in the information in the blog post I created an Arduino sketch which sends PTT and Keeplive messages to the Radio

In addition to the PTT switch the AT779-UV Mic has multiple buttons on its keypad as well as Up/Down buttons on the top. I captured the resulting byte strings sent when each button is pressed and also determined that when certain buttons a held down (i.e. a long press' there are additional byte strings sent, as well as when the buttons are released.

The Radio sends data back to the Mic and I was able to determine that this is used to drive the color of the LED on the mic (Off/Red/Green). I created a simple Arduino sketch to emulate the Radio and control the Mic LED
