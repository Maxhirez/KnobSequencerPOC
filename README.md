# KnobSequencerPOC
Single-knob 3 button Arduino CV performance step sequencer
CC BY-NC-SA 4.0
Arduino version of concept by Sam Battle at <a href="https://www.lookmumnocomputer.com">Look Mum No Computer</a>  Plug a Eurorack level clock source (square and saw tested, interrupt is on rise) into the clock in or use the Advance button to move to the next step.  Press write/program to record the current knob voltage to the step.  This voltage will "play" and the gate will trigger the next time the step is reached.  Gate stays high for 20ms (using delay, so be aware of this.)  Voltage can be recorded at any time.  Press reset to clear sequence and go to first step.  Sketch includes _partial_ comments/cruft for addition of second track and voltage quantization.

Video here:
https://youtu.be/3fGhq8m08SM

Diagram was put together pretty quick so *No guarantees here*, but Please contact if you notice any errors.
<img src="https://github.com/Maxhirez/KnobSequencerPOC/blob/master/knobSequencerCV_bb.png" width="100%">
