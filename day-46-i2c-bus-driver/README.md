# smart-environment-monitor — Day 46

## I²C Bus Driver

This day adds a transaction-oriented I²C driver layer with explicit NACK, timeout and bus-error handling, plus an SDA stuck-low recovery path.

```text
Application
    ↓
I2C Transaction
    ↓
Driver
    ↓
START → Address → ACK/NACK → Data → STOP
```

Recovery:

```text
SDA stuck-low
→ detect
→ bus recovery
→ retry transaction
```

The real STM32 electrical recovery sequence should be validated on the target board; this repository keeps the Host model deterministic and testable.
