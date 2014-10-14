#ifndef LightController_h
#define LightController_h

#include "Arduino.h"

class LightController
{
  public:
    static void Setup(const int pins[], int number_of_lights);
    static void Clear(const int pins[], int number_of_lights);

    static void Flashlight(const int pins[], int number_of_lights);

    static void Snake
    (
      const int pins[], 
      int number_of_lights, 

      int tail_size,
      int tail_appear_delay_min,
      int tail_appear_delay_max,

      int tail_disappear_delay_min,
      int tail_disappear_delay_max,

      int light_total_snakes
    );

    static void Checkboard
    (
      const int pins[], 
      int number_of_lights, 

      int checkboard_total_flashes,
      int checkboard_delay_min,
      int checkboard_delay_max
    );

    static void Pong
    (
      const int pins[], 
      int number_of_lights, 

      int pong_delay,
      int pong_passes,
      int pong_flashes,
      int pong_flash_delay
    );

    static void Flash
    (
      const int pins[], 
      int pin_to_flash, 
      int pong_flash_delay,
      int pong_flashes
    );

  private:
    LightController() {};

};

#endif
