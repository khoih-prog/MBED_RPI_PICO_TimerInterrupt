
/****************************************************************************************************************************
  RPi_Pico_TimerInterrupt.h
  For RP2040-based boards such as RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040.
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/RPI_PICO_TimerInterrupt
  Licensed under MIT license

  The RPI_PICO system timer peripheral provides a global microsecond timebase for the system, and generates
  interrupts based on this timebase. It supports the following features:
    • A single 64-bit counter, incrementing once per microsecond
    • This counter can be read from a pair of latching registers, for race-free reads over a 32-bit bus.
    • Four alarms: match on the lower 32 bits of counter, IRQ on match: TIMER_IRQ_0-TIMER_IRQ_3

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one RPI_PICO timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Based on SimpleTimer - A timer library for Arduino.
  Author: mromani@ottotecnica.com
  Copyright (c) 2010 OTTOTECNICA Italy

  Based on BlynkTimer.h
  Author: Volodymyr Shymanskyy

  Version: 1.0.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      11/05/2021 Initial coding to support RP2040-based boards such as RASPBERRY_PI_PICO. etc.
  1.0.1   K Hoang      18/05/2021 Update README and Packages' Patches to match core arduino-pico core v1.4.0
*****************************************************************************************************************************/

#pragma once

#ifndef RPI_PICO_TIMERINTERRUPT_H
#define RPI_PICO_TIMERINTERRUPT_H

#if !( defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
  #error This code is intended to run on the RASPBERRY_PI_PICO platform! Please check your Tools->Board setting.
#else
  #define USING_RPI_PICO_TIMER_INTERRUPT        true  
#endif

#ifndef RPI_PICO_TIMER_INTERRUPT_VERSION
  #define RPI_PICO_TIMER_INTERRUPT_VERSION       "RPi_Pico_TimerInterrupt v1.0.1"
#endif

#ifndef TIMER_INTERRUPT_DEBUG
  #define TIMER_INTERRUPT_DEBUG      0
#endif

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#include "TimerInterrupt_Generic_Debug.h"

/*
  To enable an alarm:
  • Enable the interrupt at the timer with a write to the appropriate alarm bit in INTE: i.e. (1 << 0) for ALARM0
  • Enable the appropriate timer interrupt at the processor (see Section 2.3.2)
  • Write the time you would like the interrupt to fire to ALARM0 (i.e. the current value in TIMERAWL plus your desired
    alarm time in microseconds). Writing the time to the ALARM register sets the ARMED bit as a side effect.
  Once the alarm has fired, the ARMED bit will be set to 0 . To clear the latched interrupt, write a 1 to the appropriate bit in
  INTR.
*/


class RPI_PICO_TimerInterrupt;

typedef RPI_PICO_TimerInterrupt RPI_PICO_Timer;

// We can use many timers here
#define MAX_RPI_PICO_NUM_TIMERS      4

typedef bool (*pico_timer_callback)  (struct repeating_timer *t);


class RPI_PICO_TimerInterrupt
{
  private:
   
    uint8_t                 _timerNo;

    pico_timer_callback     _callback;        // pointer to the callback function
    float                   _frequency;       // Timer frequency
    uint64_t                _timerCount;        // count to activate timer, in us
      
    struct repeating_timer  _timer;

  public:

    RPI_PICO_TimerInterrupt(uint8_t timerNo)
    {     
      _timerNo  = timerNo;
      _callback = NULL;
    };

    // frequency (in hertz) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be added in the future by adding similar functions here
    bool setFrequency(float frequency, pico_timer_callback callback)
    {
      if (_timerNo < MAX_RPI_PICO_NUM_TIMERS)
      {             
        // select timer frequency is 1MHz for better accuracy. We don't use 16-bit prescaler for now.
        // Will use later if very low frequency is needed.
        _frequency  = (float) 1000000;
        _timerCount = (uint64_t) _frequency / frequency;
        
        TISR_LOGWARN3(F("RPI_PICO_TimerInterrupt: _timerNo ="), _timerNo, F(", _fre ="), _frequency);
        TISR_LOGWARN3(F("_count ="), (uint32_t) (_timerCount >> 32) , F("-"), (uint32_t) (_timerCount));
        
        _callback = callback;
  
        // static bool add_repeating_timer_us(int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out);
        // static bool add_repeating_timer_ms(int64_t delay_ms, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out);
        // bool cancel_repeating_timer (repeating_timer_t *timer);
        cancel_repeating_timer(&_timer);
        add_repeating_timer_us(_timerCount, _callback, NULL, &_timer);
               
        TISR_LOGWARN1(F("add_repeating_timer_us ="), _timerCount);

        return true;
      }
      else
      {
        TISR_LOGERROR(F("Error. Timer must be 0-3"));
        
        return false;
      }
    }

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be added in the future by adding similar functions here
    bool setInterval(unsigned long interval, pico_timer_callback callback)
    {
      return setFrequency((float) (1000000.0f / interval), callback);
    }

    bool attachInterrupt(float frequency, pico_timer_callback callback)
    {
      return setFrequency(frequency, callback);
    }

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be added in the future by adding similar functions here
    bool attachInterruptInterval(unsigned long interval, pico_timer_callback callback)
    {
      return setFrequency( (float) ( 1000000.0f / interval), callback);
    }

    void detachInterrupt()
    {
      cancel_repeating_timer(&_timer);
    }

    void disableTimer()
    {
      cancel_repeating_timer(&_timer);
    }

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void reattachInterrupt()
    {
      add_repeating_timer_us(_timerCount, _callback, NULL, &_timer);
    }

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void enableTimer()
    {
      add_repeating_timer_us(_timerCount, _callback, NULL, &_timer);
    }

    // Just stop clock source, clear the count
    void stopTimer()
    {
      cancel_repeating_timer(&_timer);
    }

    // Just reconnect clock source, start current count from 0
    void restartTimer()
    {
      cancel_repeating_timer(&_timer);
      add_repeating_timer_us(_timerCount, _callback, NULL, &_timer);
    }

    int8_t getTimer() __attribute__((always_inline))
    {
      return _timerNo;
    };
}; // class RPI_PICO_TimerInterrupt

#endif    // RPI_PICO_TIMERINTERRUPT_H

