# MBED_RPI_PICO_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/MBED_RPI_PICO_TimerInterrupt.svg?)](https://www.ardu-badge.com/MBED_RPI_PICO_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MBED_RPI_PICO_TimerInterrupt.svg)](https://github.com/khoih-prog/MBED_RPI_PICO_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MBED_RPI_PICO_TimerInterrupt/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MBED_RPI_PICO_TimerInterrupt.svg)](http://github.com/khoih-prog/MBED_RPI_PICO_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-MBED_RPI_PICO_TimerInterrupt/count.svg" title="MBED_RPI_PICO_TimerInterrupt Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-MBED_RPI_PICO_TimerInterrupt/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.2](#releases-v112)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.1](#releases-v101)
  * [Initial Releases v1.0.0](#initial-releases-v100)

---
---

## Changelog

### Releases v1.2.0

1. Fix `poor-timer-accuracy` bug. Check [Poor accuracy on timer interrupt frequency or interval. #4](https://github.com/khoih-prog/MBED_RPI_PICO_TimerInterrupt/issues/4)

### Releases v1.1.2

1. Using `float` instead of `ulong` for interval for better accuracy

### Releases v1.1.1

1. Remove redundant function call

### Releases v1.1.0

1. Fix `multiple-definitions` linker error. Drop `src_cpp` and `src_h` directories
2. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.
3. Optimize library code by using `reference-passing` instead of `value-passing`
4. Update all examples


### Releases v1.0.1

1. Fix platform in `library.json`

### Initial Releases v1.0.0

1. Initial coding to support RP2040-based boards such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO**, etc. using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)



