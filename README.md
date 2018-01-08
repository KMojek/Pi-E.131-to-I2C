# Pi-E.131-to-I2C
Use a Raspberry Pi as a simple AC lighting controller

In the holiday lighting community, it is common to use software such as xLights (https://xlights.org/) to control lighting displays. Typically, this is done by a master device (Windows PC, Mac, or Rasperry Pi) relaying info over a local network (wired or wireless) via the E.131 protocol(https://www.doityourselfchristmas.com/wiki/index.php?title=E1.31_(Streaming-ACN)_Protocol) to one or more "controller" devices which then act on that info in order to control lights or other devices via various protocols (WS2811 for pixel lighting, DMX for AC lights or other devices, etc.)

This project is a very simple one; it simply uses a Pi to listen for E.131 data (DMX data packaged into UDP data packets), and relay that on to the Pi's I2C bus. In order for that to be useful, the Pi will need to be configured for I2C output and then you can connect that output to some simple electronics (port expander chips such as this: https://www.adafruit.com/product/732) and use the output of those to control solid-state relays like this one (https://www.gearbest.com/relays/pp_219171.html) in order to control 120VAC lights or other devices. So with a little DIY, you can have a cheap alternative to a Light-O-Rama controller, although it will only allow for on-off control, no dimming. No dimming will be a no-go for some sequences but for many typical singing-faces sequences, on-off works just fine.

Currently, it is assumed that your Pi is running on a static IP address and controlling a maximum of 32 outputs. So to configure this in xLights
* in the Setup tab, add an E.131 output at your Pi's IP address with 32 channels (E.131 universe is irrelevant but don't share that universe number with any other output)
* in the Layout tab, add models as appropriate.
  * For Halloween I use the first eight channels for a HolidayCoro pumpkin (http://www.holidaycoro.com/Singing-Pumpkin-p/17.htm (.xmodel for this available at https://drive.google.com/drive/folders/0B2ozCEidtWh3RWtXUFFmM1djSEk) and then eight for single-string circle elements for the mini-pumpkins (http://www.holidaycoro.com/Singing-Pumpkin-Bunch-p/18.htm) The remaining 16 channels just go unused as models.
  * For Christmas, 8 channels each get used for HolidayCoro singing trees (http://www.holidaycoro.com/Singing-Christmas-Trees-p/100.htm) and all 32 outputs are used.

Videos:
* Pi running Halloween pumpkins: https://vimeo.com/240424336
* Pi running Christmas singing trees: https://vimeo.com/246043246
