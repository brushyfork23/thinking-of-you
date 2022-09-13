# What is this thing you gave me?

A nifty reprogrammable microcontroller, and some accessories to demo its capabilities.

# What does it do?

This object connects to others like it, thus connecting you to folks who like you.
By pressing the button, you let everyone else know you're thinking of them.

# How do I use it?

You connect it to your WiFi by first connecting to its WiFi. Then you either press the button, or wait for someone else to press theirs.

1. Give the module 5v DC through the USB-C connector. You can just plug it into pretty much anything.
2. Wait a bit, then connect to its WIFI network:
    - ssid: WLED-AP
    - password: wled1234
3. Connect it to your WiFi
    1. If it does not open the captive portal automatically, go to IP `4.3.2.1` or accress `http://wled.me` in a web browser.
    2. Click the "WIFI SETTINGS" button.
    3. Enter your home's WiFi Network name and Network password.
    4. Click "Save & Connect"
    5. Wait a minute for it to connect to your WiFi network.
4. Press the button to send a warm hello. Your lights will twinkle. Everyone else's lights will twinkle. You are connected.

# But, like, what is it really?

At the core is a development board made by Wemos called the [Lolin D1 mini](https://www.wemos.cc/en/latest/d1/d1_mini.html), which is based around the super rad WiFi-enabled reprogrammable microcontroller from Espressif called the [ESP8266](https://www.espressif.com/en/products/socs/esp8266). Plugged into that is a [prototyping board](https://www.wemos.cc/en/latest/d1_mini_shield/dual_base.html) with a button on one half and Wemos's [RGB LED shield](https://www.wemos.cc/en/latest/d1_mini_shield/rgb_led.html) on the other. Flashed to the D1 mini is the program [WLED](https://kno.wled.ge/) with a [custom modification](https://github.com/brushyfork23/thinking-of-you/WLED-usermod) which lets the button do what I want. A piece of diffusion material has been hot-glued over the LEDs to make them easier on the eyes, and the D1 mini has been plugged into a solderless breadboard to give the whole thing some weight and make it more managable to handle.

# What does it _actually_ do?

When the module powers up, WLED attempts to connect to a WiFi network using credentials stored in its memory. After a minute or so with no connection, it will launch its own WiFi access point you can connect to. It serves a web portal which allows easy configuration and control of the LEDs. You can select different colors, palettes, and animations, and assign actions to the button.

WLED supports various protocols for syncing multiple modules, and one of those is the asynchronous pub/sub web service MQTT. I configured the module to connect to a free MQTT broker, so once a WiFi connection is established the module subscribes to notifications and begins broadcasting all changes to a device-specific MQTT topic.

The custom modification I wrote listens for the button to be pressed and broadcasts a hardcoded message to the group topic all of these modules are subscribed to. That message tells the modules to play a specific animation with a speicifc color palette at a specific brightness. It also takes advantage of WLED's nightlight feature to shut off the animation after one minute. The end result is that the press of any module's button causes all modules to briefly play the same animation.

# Why did you give it to me?

I wanted to share one of my favorite hobbies with you, so I put together a demo project out of resusable and expandable components. The Lolin D1 mini is a versitile Arduino-compatible microcontroller and WLED shows off many of its fascinating capabilities. The button, lights, and internet-connectivity were a relatively low cost and low effort way to turn the board into something useful, and you are welcome to unplug them from the microcontroller and find another use for it. We all now have the same hardware, so we can share any interesting ideas you come up with!

# Digging in

To play with WLED, connect to it from a browser or the mobile apps.

-   Check your router device list for the IP of the WLED device inside your local network, then navigate to that IP in a web browser.
-   or, much easier, install the [WLED app](https://github.com/Aircoookie/WLED-App) on a mobile device and use the "Discover lights" feature to automatically detect the module.

Most of the effects were designed for a long, straight strip of LEDs, but you can still find interesting/soothing/exciting combinations that look good on this little ring.

# Digging deeper

You can modify WLED and install it to the module yourself. Start with the documentation here: https://kno.wled.ge/advanced/compiling-wled. I found it delightfully simple to write an extension and flash the module using PlatformIO. I bet you could make some great improvements to my usermod.

Should you repurpose these boards, here are some technical notes about the modules' construction:

-   The normally-open momentary pushbutton is soldered between Ground and GPIO pin 16 (which the Lolin board has labeled D0 for some reason). A 10k ohm pull-up resistor is soldered onto the prototyping board between GPIO 16 and 3.3V (labeled 3V) to keep the input pin's voltage high until a button press brings it low. Software monitors for the drop in voltage to register the button press. I think this could have actually been accomplished in software, as I'm pretty sure the ESP8266 has configurable internal pull-up resistors, but this hardware solution reduced the modifications needed to out-of-the-box WLED.
-   The LED shield defaults to getting its data over GPIO pin 2 (labeled D4), but WLED sends some other data over that pin at boot which caused the LEDs to flash obnoxiously. I cut the D4 jumper on the back of the LED shield and soldered the jumper to use GPIO pin 15 instead (labeld D8).
-   The diffusion material has been secured over the LEDs with hot glue (my favorite permanent-until-you-change-your-mind adhesion tool). This should prevent the LEDs from being searingly bright, but if you think up a better method you can just pry off the diffusor and scrape away the glue blobs without leaving any residue.
-   The LEDs on the shield have the WS2812B chipset, which would like to receive their data at 5V, but I believe the D1 mini outputs data from its GPIO pins at 3.3V. Luckily, for such a small numer of LEDs and at such a small wire distance, everything works fine. If you use the D1 mini to connect to a longer run of LEDs, you will probably want to use a logic level shifter to step up the data line from 3.3V to 5V. Though, there are a number of things you'll want to do for a longer run, like use an external power supply, add a 1000uF capacitor, and maybe include an anti-ringing resistor. Please feel free to reach out for advice on whatever you're trying to accomplish!

# Troubleshooting

Not working?  Boo!  I'm sorry!

The most common issue I've seen is a failure to establish a connection to the MQTT broker. That means you can press the button and it will cycle through colors, but you won't get the fun animation and connection to the other devices.  It's honestly pretty opaque to debug, and I don't have any good recommendation for how to diagnose and repair.  I'm happy to chat with you one-on-one to work through it, but your best bet would be to dive deep and flash a new version of the firmware with debug flags enabled.

Again, if you're having issues, I'm very sorry to have gotten your hopes up and given you a disappointing device. I hope you can still find inspiration to turn this object into something useful.
