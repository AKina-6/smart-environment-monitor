# Smart Environment Monitor

An STM32F103C8T6-based environment monitoring system for embedded systems learning, course projects and portfolio demonstration.

## Features

- DHT11 temperature and humidity acquisition
- BH1750 ambient light acquisition
- SSD1306 OLED display
- LED and buzzer threshold alarms
- UART JSON telemetry
- Optional ESP8266 and MQTT extension
- Host-side simulation and unit tests
- GitHub Actions continuous integration

## Host Build

```bash
cmake -S . -B build
cmake --build build
./build/environment_monitor_sim
ctest --test-dir build --output-on-failure
```

## Architecture

The application logic is hardware-independent. MCU-specific sensor access, display output and timing are connected through platform adapters.

See the Chinese [README](README.md) and documentation under [`docs/`](docs/).
