# KnobSequencerPOC
Single-knob 3 button Arduino CV performance step sequencer
CC BY-NC-SA 4.0
Arduino version of concept by Sam Battle at <a href="https://www.lookmumnocomputer.com">Look Mum No Computer</a>. Plug a Eurorack level clock source (square and saw tested, interrupt is on rise) into the clock, or the Advance button will step through the sequence either for play or record functionality.  Press write/program to record the current knob voltage to the step.  This voltage will "play" and the gate will trigger the next time the step is reached.  Steps where the record button is not pressed should be rests. Gate stays high for 20ms (using delay, so be aware of this.)  Voltage can be recorded at any time.  Press reset to clear sequence and go to first step.  Sketch includes _partial_ comments/cruft for addition of second track (incomplete) and voltage quantization. Output levels are Eurorack friendly, 0-5+ volts.

Note: A semi-tone voltage (~.083v) quantize switch can be added on A2 with a pulldown resistor or a setup pinMode definition with INPUT_PULLUP added and the pertinent lines un-commented.  This is untested though.

Possible modifications (untested):
<ul>
  <li>Conversion to 0-10v with L7810CV or 350T as voltage clamp and 2:1 voltage divider on the input and diode/capacitor voltage doubler on output</li>
  <li>-5/+5 voltage offset option</li>
  <li>Second track (noted)</li>
  <li>Output quantizer option (noted)</li>
  <li>Set-step-to-first button (any non-328 board should have enough interrupt pins)</li>
  <li>"Last Note" button for sequences <16 steps (")</li>
  <li>To record played notes from CV keyboard/controller:</li>
  <ul>
  <li>CV in with knob out-A0 shunted through switching jack (voltage clamp!)</li>
  <li>Gate in with write button-D3 shunted through switching jack (voltage clamp!)</li>
  </ul>
  <li>Internal clock option (with second pot.  BPM readout will be a challenge though-perhaps I2C 3x7-segment display?)</li>
</ul>

Video here:
https://youtu.be/3fGhq8m08SM

Diagram was put together pretty quick so *No guarantees here*, but Please contact if you notice any errors.

BOM:
<ul>
  <li>Arduino Nano Every or compatible</li>
  <li>Adafruit (or compatible) MCP4725 ADC</li>
  <li>8x8 LED matrix with MAX7219 driver(LedControl.h compatible)</li>
  <li>2 low (.2-.3v) forward voltage Schottky Diodes (eg. BAT42)</li>
  <li>1 potentiometer, value rating from 10k-500k (voltage divider-value not critical)</li>
  <li>1k Resistor</li>
  <li>10k Resistor</li>
  <li>3x momentary contact switches</li>
  <li>3 CV jacks, at least one switched (size compatible with your system)</li>
</ul>

