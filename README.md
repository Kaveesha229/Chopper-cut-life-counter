<h1 align="center">Cutter Cycle Counter</h1>
<p align="center"><strong>INDUSTRIAL AUTOMATION | EMBEDDED CONTROL</strong></p>
<p align="center"><a href="https://github.com/Kaveesha229">Kaveesha Gunawardena | Engineering portfolio</a></p>

## Overview

An embedded prototype for sequencing a stepper driven feed and a relay output while displaying a cycle count on an OLED. It provides a foundation for documenting cutter usage.

## Repository guide

<table>
<tr><th>File or folder</th><th>Purpose</th></tr>
<tr><td><a href="Chopper_Testing.ino">Chopper_Testing.ino</a></td><td>Main control and display sketch</td></tr>
</table>

## Hardware and libraries

The sketch uses a step and direction motor driver, a relay output, a switch and a 128 by 64 SSD1306 OLED at I2C address `0x3C`. Dependencies are `Wire`, `Adafruit_GFX` and `Adafruit_SSD1306`.

## Connections

<table>
<tr><th>Signal</th><th>Pin or address</th></tr>
<tr><td>Stepper STEP</td><td>2</td></tr>
<tr><td>Stepper DIR</td><td>3</td></tr>
<tr><td>Switch with internal pullup</td><td>4</td></tr>
<tr><td>Relay</td><td>7</td></tr>
<tr><td>OLED</td><td>Board I2C pins, address 0x3C</td></tr>
</table>

## Operating sequence

While the switch input is low, the program generates step pulses for approximately 50 milliseconds, pauses, activates the relay and increments `onCount`. The relay stays high for 1 second before the sequence resets. Holding the input low repeats the sequence. The OLED shows the count, with an idle screen when the input is inactive.

## Getting started

1. Open `Chopper_Testing.ino` in Arduino IDE.
2. Install the two Adafruit display libraries and select the controller board.
3. Verify pin assignments and the OLED address.
4. Test the display and logic outputs before connecting the cutting mechanism.
5. Use Serial Monitor at 9600 baud to inspect the count messages.

## Current scope

The counter records commanded relay cycles. It does not independently verify a completed cut or measure blade wear. The count is stored in RAM and resets after a restart. Persistent storage, a replacement threshold and maintenance alerts are future extensions.

## Suggested verification

Compare commanded cycles with observed physical cuts, test sustained switch input and record restart behaviour. A quantified reliability result is not included in the current repository.

## Project media

Photos and demonstration videos will be added here as the project presentation is updated.

<p align="center"><sub>Practical engineering through building, testing and refinement.</sub></p>
