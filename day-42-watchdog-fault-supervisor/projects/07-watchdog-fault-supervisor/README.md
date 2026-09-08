# Project 07: Watchdog, Fault Supervisor and Reset Reason

核心策略：只有所有 required 模块都在各自 deadline 内上报 heartbeat，Supervisor 才允许刷新 IWDG。

```text
Sensor ----heartbeat----\
Control ---heartbeat-----+--> Fault Supervisor --> Refresh IWDG
UI --------heartbeat----/
Telemetry (optional)
```

如果关键模块卡死：

```text
heartbeat missing
→ Supervisor blocks watchdog refresh
→ IWDG timeout
→ MCU reset
→ next boot reads reset reason
```

默认 deadline 示例：Sensor/Control 600 ms，UI 1500 ms，Telemetry 可选。

Host 验证：
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/watchdog_supervisor_sim
```
