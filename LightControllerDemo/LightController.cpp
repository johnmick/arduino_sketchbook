#include "LightController.h"

void LightController::Setup(const int pins[], int number_of_lights) {
  for ( int i = 0; i < number_of_lights; i++ ) 
    pinMode(pins[i], OUTPUT);
};

void LightController::Clear(const int pins[], int number_of_lights) {
  for ( int i = 0; i < number_of_lights; i++ ) 
    digitalWrite(pins[i], LOW);
};

void LightController::Flashlight(const int pins[], int number_of_lights) {
  for ( int i = 0; i < number_of_lights; i++ ) 
    digitalWrite(pins[i], HIGH);
};

void LightController::Snake
(
  const int pins[], 
  int  number_of_lights, 

  int  tail_size,
  int  tail_appear_delay_min,
  int  tail_appear_delay_max,

  int  tail_disappear_delay_min,
  int  tail_disappear_delay_max,

  int  light_total_snakes,
  bool sound_enabled,
  int  pin_num_speaker
)
{
  for ( int iterations = 0; iterations < light_total_snakes; iterations++ )
  {
    int appear_delay    = random(tail_appear_delay_min, tail_appear_delay_max);
    int disappear_delay = random(tail_disappear_delay_min, tail_disappear_delay_max);

    // Snake Forward
    for ( int i = 0; i < number_of_lights; i++ ) {
      digitalWrite(pins[i], HIGH);
      if ( i -  tail_size > -1 ) { digitalWrite(pins[i-tail_size], LOW); } // Trim Tail

      if ( sound_enabled ) {
        tone( pin_num_speaker, 100 + i * 50, appear_delay / 4);
      }
      delay( appear_delay );
    }

    // Complete Slide Out
    for ( int i = number_of_lights - tail_size; i < number_of_lights; i++ ) {
      digitalWrite(pins[i], LOW);
      if ( sound_enabled ) {
        tone( pin_num_speaker, (100 + number_of_lights * 50) - i * 50, appear_delay / 4);
      }
      delay( disappear_delay );
    }
  }
}

void LightController::Checkboard
(
  const int pins[], 
  int  number_of_lights, 

  int  checkboard_total_flashes,
  int  checkboard_delay_min,
  int  checkboard_delay_max,
  bool sound_enabled,
  int  pin_num_speaker
)
{
  for ( int iterations = 0; iterations < checkboard_total_flashes; iterations++ ) 
  {
    int delayTime = random(checkboard_delay_min, checkboard_delay_max );
    for ( int i = 0; i < number_of_lights; i++ ) {
      digitalWrite(pins[i], i % 2 ? HIGH : LOW );
    }

    if ( sound_enabled ) {
      tone(pin_num_speaker, map(iterations, 0, checkboard_total_flashes, 50, 200), delayTime / 3);
    }

    delay(delayTime);
    for ( int i = 0; i < number_of_lights; i++ ) {
      digitalWrite(pins[i], i % 2 ? LOW : HIGH );
    }

    if ( sound_enabled ) {
      tone(pin_num_speaker, map(iterations, 0, checkboard_total_flashes, 200, 50), delayTime / 3);
    }
    delay(delayTime);
  }
}

void LightController::Pong
(
  const int pins[], 
  int  number_of_lights, 

  int  pong_delay,
  int  pong_passes,
  int  pong_flashes,
  int  pong_flash_delay,
  bool sound_enabled,
  int  pin_num_speaker
)
{
  for ( int iterations = 0; iterations < pong_passes; iterations++ )
  {
    if ( iterations % 2 == 0 ) {

      for ( int i = 0; i < number_of_lights; i++ ) {
        digitalWrite(pins[i], HIGH); 
        if ( i - 1 > -1 ) { 
          digitalWrite(pins[i-1], LOW); 
        }

        if ( sound_enabled ) {
          tone( pin_num_speaker, map(i, 0, number_of_lights, 100, 500), pong_delay/2 );
        }
        delay(pong_delay);
      }

      LightController::Flash(
        pins[number_of_lights-1], // Pin to Flash
        pong_flash_delay,
        pong_flashes,
        sound_enabled,
        pin_num_speaker,
        500
      );

    } else {

      for ( int i = number_of_lights-1; i > -1; i-- ) {
        digitalWrite(pins[i], HIGH);
        if ( i + 1 < number_of_lights ) { 
          digitalWrite(pins[i+1], LOW);
        }
        if ( sound_enabled ) {
          tone( pin_num_speaker, map(i, 0, number_of_lights, 100, 500), pong_delay/2 );
        }
        delay(pong_delay);
      }

      LightController::Flash(
        pins[0],              // Pin to Flash
        pong_flash_delay,
        pong_flashes,
        sound_enabled,
        pin_num_speaker,
        100
      );

    }
  }
}

void LightController::Flash
(
  int  pin_to_flash, 
  int  pong_flash_delay,
  int  pong_flashes,
  bool sound_enabled,
  int  pin_num_speaker,
  int  frequency
)
{
  for ( int i = 0; i < pong_flashes; i++ ) {
    digitalWrite(pin_to_flash, HIGH);
    if ( sound_enabled ) { tone( pin_num_speaker, frequency, pong_flash_delay ); }
    delay(pong_flash_delay);
    digitalWrite(pin_to_flash, LOW);
    delay(pong_flash_delay);
  }
}
