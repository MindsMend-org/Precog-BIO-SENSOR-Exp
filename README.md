# Precog Bio Sensor Experiment [A starting point]

[All is mind]
Hypothesis: The subconscious mind knows all things, the conscious mind covers it up. Can we train both subconscious & conscious to work as one? I believe we all can.

## Make a prediction. Measure the moment. Share what you find.

Could a person's body react differently before an outcome is revealed? This is an open experiment for curious people to build, question, and improve together. Bring an ESP32 or Arduino-compatible board, a GSR sensor, and an analog pulse sensor; make a prediction before each trial; then compare your results with a fair chance baseline.

This is a way to practice careful experimental design, electronics, and coding, not evidence that precognition is real. A surprising result is a reason to repeat the test with better controls, not a conclusion by itself.

## What the device measures

The Arduino sketch samples two analog inputs:

- **GSR** (galvanic skin response) is a changing electrical signal associated with skin conductance. It can vary with sweat, movement, sensor contact, temperature, and other factors. It does not identify a particular emotion or thought.
- **Heart-contraction channel** is intended to describe contraction phase, not beats per minute: `0` (or any value below `1`) means none, `1` means start, `2` means contracting, and `3` means release. These are phase labels, not a medical measurement or BPM.
- **Current firmware detail:** the sketch reads `hr_raw` directly with `analogRead`, then sets `hr_bit` to `1` when that raw reading exceeds `200` and `0` otherwise. It does not currently translate the analog signal into the four contraction phases above. That translation requires calibrated signal thresholds or a sensor that already provides those encoded states.
- **Timestamp** is elapsed microseconds since `START`, so samples can be aligned in time.

Each data line is:

```text
gsr_raw,hr_raw,hr_bit,t_us
```

The target sampling interval is 4,000 microseconds (250 Hz). Serial output and board timing can make the actual rate less exact, so treat it as a target rather than a guarantee.

## Parts and wiring

- ESP32 development board or another Arduino-compatible board with two analog inputs
- Analog-output GSR sensor/module
- Analog-output pulse sensor/module
- USB cable and a computer with the Arduino IDE
- Jumper wires; follow the sensor maker's instructions for powering and attaching sensors

Connect sensor ground to board ground, and connect the analog outputs to `A0` (GSR) and `A1` (pulse). In [`arduino/precog_bio_sensor.ino`](arduino/precog_bio_sensor.ino), change `gsrPin` and `hrPin` if your board uses different analog pin names or numbers. ESP32 pin aliases vary between boards. Check your exact board's pinout and ADC limits before wiring: **never send a 5 V analog signal into an ESP32 input**, which is generally limited to 3.3 V. Power each sensor only as its documentation specifies.

These are educational sensors, not medical equipment. Do not use the readings to diagnose or make health decisions. Use sensors only as intended, do not attach them to broken or irritated skin, and stop if anything feels uncomfortable. When connected to a computer, use a battery-powered board and avoid any setup that electrically connects a person to mains-powered equipment.

## Upload and collect

1. Install the Arduino IDE and the board support package for your board.
2. Open [`arduino/precog_bio_sensor.ino`](arduino/precog_bio_sensor.ino), select your board and port, then upload.
3. Open Serial Monitor at **115200 baud** and set the line ending to **Newline**.
4. Send `START` to begin streaming, `STOP` to stop, or `RESET` to return to the ready state. The board prints `READY` at startup and `STOPPING` after a stop.
5. Save the comma-separated lines from the serial output as raw data. Keep a separate trial log with participant-chosen anonymous IDs, trial number, prediction, outcome, and event times. Do not include names or other identifying details.

The sketch streams sensor data only. It does not generate random outcomes, record guesses, or save a CSV file on its own. For a useful test, record the guess and trial events separately with timestamps; do not decide after seeing the signals which trials to count.

## A simple, testable protocol

Start small and write down the rules before collecting data:

1. Choose one question, such as whether a pre-outcome sensor measure predicts a randomly selected left/right outcome better than chance.
2. Decide the number of trials, the prediction window, how guesses and outcomes are recorded, and how missing or noisy trials are handled.
3. Generate outcomes randomly and keep each outcome hidden until after the participant has recorded a guess. Avoid changing the rules mid-run.
4. Include a practice period, then collect the planned trials with consistent sensor placement and a quiet, comfortable setup.
5. Compare the pre-defined measure with its chance baseline. Report all planned trials, exclusions, and analysis choices, including results that do not support the idea.
6. Repeat with a fresh session or independent participants before drawing conclusions.

This repository currently provides the Arduino acquisition sketch, not a randomizer or analysis program. Keep trial labels separate from sensor traces during collection, and publish the exact protocol and analysis used so another person can reproduce it.

## Open science and getting involved

You do not need to be an expert. Try the build, check the wiring, ask what could bias the result, and share improvements through issues or pull requests. Helpful contributions include board-specific pin notes, calibration guidance, accessible protocols, data-quality checks, and analysis that compares results with chance without cherry-picking.

Before sharing data, get informed consent from everyone involved. Share only anonymized data and the protocol needed to interpret it. Do not publish identifiable physiological traces or claim that this experiment can establish a medical or paranormal ability.

## Repository contents

- [`arduino/precog_bio_sensor.ino`](arduino/precog_bio_sensor.ino): serial acquisition firmware for raw GSR and pulse-sensor inputs.
