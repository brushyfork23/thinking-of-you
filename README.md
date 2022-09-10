# What is this?

A nifty reprogrammable microcontroller, and some accessories to demo its capabilities.

# What does it do?

This object connects to others like it, thus connecting you to folks who like you.
By pressing the button, you let every else know you are thinking of them.

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

At the core is a development board made by Wemos called the [Lolin D1 mini](https://www.wemos.cc/en/latest/d1/d1_mini.html), which is based around the super rad WiFi-enabled reprogrammable microcontroller from Espressif called the [ESP8266](https://www.espressif.com/en/products/socs/esp8266). Plugged into that is a [prototyping board](https://www.wemos.cc/en/latest/d1_mini_shield/dual_base.html) with a button soldered onto one side and Wemos's [RGB LED shield](https://www.wemos.cc/en/latest/d1_mini_shield/rgb_led.html) plugged into the other side. Flashed to the D1 mini is the program [WLED](https://kno.wled.ge/) with a [custom modification](https://github.com/brushyfork23/WLED-usermod-thinking-of-you) which makes the button do what I want.  A piece of diffusion material has been hot-glued over the LEDs to make them easier on the eyes, and the D1 mini has been plugged into a solderless breadboard to give the whole thing some weight and make it more managable to handle.

# Why did you give it to me?

I wanted to share one of my favorite hobbies with you so I put together a demo project out of resusable and expandable components.  The Lolin D1 mini is a versitile microcontroller and WLED shows off many of its fascinating capabilities.  The button, LED, and internet-connectivity were a relatively low cost and low effort way to turn the board into something useful, but you are welcome to unplug them from the microcontroller and find another use for it.  Whatever you end up doing, I hope you share your experience!

# Digging in

To play with WLED, connect to it from a browser or the mobile apps.

-   Check your router device list for the IP of the WLED device inside your local network, then navigate to that IP in a web browser.
-   or, much easier, install the [WLED app](https://github.com/Aircoookie/WLED-App) on a mobile device and use the "Discover lights" feature to automatically detect the module.

# Digging deeper

You can modify WLED and install it to the module yourself.  Start with the documentation here: https://kno.wled.ge/advanced/compiling-wled.  I found it delightfully simple to write an extension and flash the module using PlatformIO.  What great ideas will you come up with?
