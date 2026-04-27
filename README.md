# Automated Bottle Washer System


An Arduino-based bottle washer control system that counts bottles using an IR sensor and automatically runs a relay-controlled washing/locking/actuator sequence after the target number of bottles is detected.

This project is designed for small-scale automated bottle handling systems where bottles need to be detected, locked, positioned, and processed in a repeatable sequence.

---

## Features

- IR sensor-based bottle detection
- Automatic bottle counting
- Default 4-bottle operation cycle
- Buzzer alert at startup and before cycle execution
- Relay-controlled locking and catching mechanism
- Actuator control for mechanical movement
- Automatic reset after each cycle
- Expandable mode-selection logic for different bottle targets

---

## How It Works

1. The Arduino starts and gives two buzzer beeps to indicate power ON.
2. The IR sensor monitors bottle movement.
3. Every rising edge from the IR sensor increments the bottle count.
4. When the bottle count reaches the configured target, the system starts the washer sequence.
5. The lock, catch, secondary lock, and actuator relays are triggered in order.
6. After the sequence is complete, the system resets the count and waits for the next batch.

---

## Hardware Requirements

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno/Nano or compatible board | 1 | Main controller |
| IR sensor module | 1 | Bottle detection |
| 4-channel relay module | 1 | Controls lock, catch, actuator, and secondary lock |
| Buzzer | 1 | Startup and cycle alert |
| Push button | 1 | Optional mode selection |
| LED | 1 | Optional mode indicator |
| Actuator/mechanical drive | 1 | Bottle movement or washing mechanism |
| External power supply | As needed | Powers relay loads safely |

---

## Pin Configuration

| Arduino Pin | Name | Function |
|---|---|---|
| `8` | `IR` | IR bottle detection sensor |
| `A0` | `BUZZER` | Buzzer output |
| `12` | `CATCH` | Catch relay |
| `10` | `LOCK` | Main lock relay |
| `5` | `ACTUATOR` | Actuator relay |
| `3` | `LOCK2` | Secondary lock relay |
| `6` | `BUTTON_PIN` | Optional push button input |
| `A4` | `MODE_LED` | Optional mode indicator LED |

> Relay logic depends on your relay module. In this sketch, some relays appear to use active-low behavior, meaning `LOW` may turn the relay ON and `HIGH` may turn it OFF.

---

## Default Cycle Timing

| Step | Action | Duration |
|---:|---|---:|
| 1 | Buzzer ON | 500 ms |
| 2 | Main lock activates | 2000 ms |
| 3 | Secondary lock and catch activate | 1000 ms |
| 4 | Actuator activates | 3200 ms |
| 5 | Washing/process wait time | 6000 ms |
| 6 | Actuator deactivates | 2000 ms |
| 7 | Catch deactivates | 4000 ms |
| 8 | Locks reset | Immediate |

---

## Project Structure

```text
bottle-washer/
├── bottle_washer.ino
├── README.md
└── LICENSE
```

---

## Uploading the Code

1. Install the Arduino IDE.
2. Create a new Arduino sketch named `bottle_washer.ino`.
3. Copy only the bottle washer code into the sketch.
4. Connect the Arduino board to your computer.
5. Select the correct board from **Tools > Board**.
6. Select the correct port from **Tools > Port**.
7. Click **Upload**.

---

## Important Notes

- Keep the bottle washer and bottle filler sketches in separate `.ino` files.
- Do not paste two Arduino programs with separate `setup()` and `loop()` functions into one sketch.
- The current washer code uses a default bottle target of `4`.
- The startup mode-selection logic is present but commented out.
- The pump section is commented out in the current washer sketch. Add a pump relay definition if your washer requires pump control.

---

## Calibration

You may need to adjust these values depending on your hardware:

```cpp
int bottleTarget = 4;
delay(3200);  // actuator movement time
delay(6000);  // washing/process time
delay(4000);  // catch release delay
```

Recommended calibration steps:

1. Test the IR sensor separately.
2. Confirm relay ON/OFF logic before connecting loads.
3. Test each relay output manually.
4. Run the full sequence without bottles.
5. Run the full sequence with empty bottles.
6. Adjust delay values according to machine movement.

---

## Safety Warning

This project may control motors, actuators, pumps, or other high-current devices through relays. Always use proper isolation, fuses, emergency stop switches, and suitable power supplies. Do not touch live AC wiring. If using mains voltage, consult a qualified electrician.

---

## Troubleshooting

| Problem | Possible Cause | Solution |
|---|---|---|
| Bottle count increases too fast | IR sensor noise or bounce | Increase debounce delay or adjust sensor position |
| Relay works opposite way | Active-low relay module | Swap `HIGH` and `LOW` logic for that relay |
| Cycle starts unexpectedly | False IR trigger | Shield sensor from ambient light and vibration |
| Actuator does not move | Relay wiring or external power issue | Check relay output and actuator supply |
| Button mode does not work | Mode code is commented out | Uncomment and test the startup mode-selection block |

---

## Future Improvements

- Add LCD/OLED display for bottle count and mode
- Add emergency stop input
- Add non-blocking timing using `millis()` instead of `delay()`
- Add EEPROM memory for saved bottle target
- Add pump relay control
- Add manual test mode for each relay
- Add serial monitor debugging

---
