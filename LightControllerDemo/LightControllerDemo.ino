// Experimenting with 8 LEDs; exploring how to store and invoke light sequences

#include <Servo.h>
#include "LightController.h"

///////////////////////////////////////////////////////////////////////////////
// Modes
///////////////////////////////////////////////////////////////////////////////
  const int mode_light_snake_enabled      = true;
  const int mode_light_checkboard_enabled = false;
  const int mode_light_pong_enabled       = true;



///////////////////////////////////////////////////////////////////////////////
// Arduino Pin Mappings
///////////////////////////////////////////////////////////////////////////////
  const int pin_num_speaker = 2;

  const int pin_num_leds[]   = { 13, 12, 11, 10, 9, 8, 7, 6 };
  const int output_pins[]    = { pin_num_speaker };
  const int input_pins[]     = { };



///////////////////////////////////////////////////////////////////////////////
// Setup
///////////////////////////////////////////////////////////////////////////////
  const int number_of_lights = sizeof(pin_num_leds) / sizeof(int);

  void setup()
  {
    Serial.begin(9600);

    LightController::Setup( pin_num_leds, number_of_lights );
    LightController::Clear( pin_num_leds, number_of_lights );

    for ( int i = 0; i < sizeof(output_pins) / sizeof(int); i++ ) 
      pinMode(output_pins[i], OUTPUT); 
    for ( int i = 0; i < sizeof(input_pins)  / sizeof(int); i++ ) 
      pinMode(input_pins[i],  INPUT); 
  }



///////////////////////////////////////////////////////////////////////////////
// Loop
///////////////////////////////////////////////////////////////////////////////
  void loop()
  {
    if ( mode_light_snake_enabled ) {
      LightController::Clear( pin_num_leds, number_of_lights );
      delay(250);

      LightController::Snake( pin_num_leds, number_of_lights,
         4,  // Tail Size
        15,  // Tail Appear Delay Min
        50,  // Tail Appear Delay Max
     
        15,  // Tail Disappear Delay Min
        35,  // Tail Disappear Delay Max

        20   // Light Total Snakes
      );
    }

    if ( mode_light_checkboard_enabled ) {
      LightController::Flashlight( pin_num_leds, number_of_lights );
      delay(250);

      LightController::Checkboard( pin_num_leds, number_of_lights,
        10,  // Total Flashes
        175, // Delay Min
        175  // Delay Max
      );

    }

    if ( mode_light_pong_enabled ) {
      LightController::Clear( pin_num_leds, number_of_lights );
      delay(250);

      LightController::Pong( pin_num_leds, number_of_lights,
        25, // Delay
        20, // Number of Passes
        10, // Number of Endpoint Flashes
        40  // Endpoint Flash Delay
      );
    }
  }
