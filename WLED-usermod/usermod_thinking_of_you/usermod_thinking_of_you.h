#pragma once

#include "wled.h"

#define TOY_EFFECT_ID 74 // Colortwinkles
#define TOY_PALLET_ID 11 // Rainbow
#define TOY_DEFAULT_BUTTON_ID -1

#define WLED_DEBOUNCE_THRESHOLD      50 // only consider button input of at least 50ms as valid (debouncing)
#define WLED_DOUBLE_PRESS           350 // double press if another press within 350ms after a short press

/*
 * This usermod published an MQTT message to the group topic whenever a button is pressed.
 *
 * The message it sends is:
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
 */

class ThinkingOfYou : public Usermod {
  private:
    // This config variable has a default set inside readFromConfig()
    int8_t buttonId;

  public:
    void setup() {}

    void loop() {}

    /*
     * When the button configured in settings is pressed, publish an MQTT message to the Group Topic
    */
    bool handleButton(uint8_t b) {
      yield();

      // Ensure usermod is enabled
      if (buttonId < 0) {
        return false;
      }
      
      // Ensure this is the trigger button, and that it is a pushbutton
      if (b != buttonId || btnPin[b]<0 || (buttonType[b] != BTN_TYPE_PUSH && buttonType[b] != BTN_TYPE_PUSH_ACT_HIGH)) {
        return false;
      }

      if (isShortButtonPress(b)) {
        publishMessage();
      }
      
      return false;
    }

    // This logic is duplicated from button.cpp's handleButton()
    bool isShortButtonPress(uint8_t b) {
      if (!isButtonPressed(b) && buttonPressedBefore[b]) { //released

        long dur = millis() - buttonPressedTime[b];
        if (dur < WLED_DEBOUNCE_THRESHOLD) {buttonPressedBefore[b] = false; return false;} //too short "press", debounce
        bool doublePress = buttonWaitTime[b]; //did we have a short press before?
        buttonWaitTime[b] = 0;

        if (!buttonLongPressed[b]) { //short press
          if (b != 1 && !macroDoublePress[b]) { //don't wait for double press on buttons without a default action if no double press macro set
            return true;
          } else { //double press if less than 350 ms between current press and previous short press release (buttonWaitTime!=0)
            if (!doublePress) {
              buttonWaitTime[b] = millis();
            }
          }
        }
        buttonPressedBefore[b] = false;
        buttonLongPressed[b] = false;
      }

      //if 350ms elapsed since last short press release it is a short press
      if (buttonWaitTime[b] && millis() - buttonWaitTime[b] > WLED_DOUBLE_PRESS && !buttonPressedBefore[b]) {
        buttonWaitTime[b] = 0;
        return true;
      }

      return false;
    }

    void publishMessage() {
      if (WLED_MQTT_CONNECTED){
        char topicBuf[38], jsonBuf[122];
        sprintf_P(topicBuf, "%s/api", mqttGroupTopic);
        sprintf_P(jsonBuf,  "{\"on\":true,\"bri\":100,\"nl\":{\"on\":true,\"dur\":1,\"mode\":0,\"tbri\":0},\"seg\":[{\"fx\":%d,\"sx\":125,\"ix\":125,\"pal\":%d}]}", TOY_EFFECT_ID, TOY_PALLET_ID);
        mqtt->publish(topicBuf, 0, false, jsonBuf);
      }
    }

    /*
     * addToConfig() will add custom persistent settings to the cfg.json file in the "um" (usermod) object.
     * The value added to settings for this module is:
     *  - the button ID which will trigger the MQTT publish on a short press (note that this is not the button _pin_)
     */
    void addToConfig(JsonObject& root)
    {
      JsonObject top = root.createNestedObject("Thinking of You");
      top["Button ID"] = buttonId;
    }


    /*
     * readFromConfig() is used to read back the custom values set in config.
     */
    bool readFromConfig(JsonObject& root)
    {
      JsonObject top = root["Thinking of You"];

      bool configComplete = !top.isNull();

      configComplete &= getJsonValue(top["Button ID"], buttonId, TOY_DEFAULT_BUTTON_ID);

      return configComplete;
    }
};