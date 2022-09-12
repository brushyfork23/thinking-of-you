# WLED Usermod - Thinking of You

WLED allows custom functionality to be easily added through extensions called usermods. See https://github.com/Aircoookie/WLED/wiki/Add-own-functionality for more info.

The usermod this demo project requires is named Thinking of You.

When installed, it monitors for a configured button to be pressed. When pressed, an MQTT message is published to the topic `{Group Topic}/api`. That meesage instructs all modules to activate a rainbow twinkle effect for 1 minute, then turn off. The contents of the payload is:

```
{
  "on": true,
  "bri": 100,
  "nl": {
    "on": true,
    "dur": 1,
    "mode": 0,
    "tbri": 0
  },
  "seg": [{
    "fx": 74,
    "sx": 125,
    "ix": 125,
    "pal": 11
  }]
}
```

# How to install

To include the Thinking of You usermod when compiling WLED:

1. Copy the `usermod_thinking_of_you.h` into the sketch folder (same folder as wled00.ino)
2. Add `#include "usermod_thinking_of_you.h` in the top of `usermods_list.cpp`
3. Add `registerUsermod(new ThinkingOfYou())` toward the bottom of `usermods_list.cpp`
