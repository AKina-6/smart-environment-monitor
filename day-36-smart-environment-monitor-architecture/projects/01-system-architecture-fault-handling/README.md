# Project 01：Smart Environment Monitor Architecture & Fault Handling

## 目标

把此前的单点驱动和 RTOS/通信练习组织成一个可扩展的嵌入式系统结构：

```text
BSP / Drivers
    ↓
Sensor Layer
    ↓
Service Layer
    ↓
Application Layer
    ↓
Actuators / UI / Telemetry
```

## 分层

### Sensor Layer
负责把 DHT11、BH1750 等原始驱动结果统一成 `sensor_snapshot_t`，并标记健康状态。

### Service Layer
负责数值范围检查、数据陈旧判断、环境状态分类和故障统计。

### Application Layer
根据 `NORMAL / DARK / HOT / DEGRADED / FAULT` 决定风扇、灯、告警和 UI Warning。

### BSP
只负责具体硬件访问，例如 OLED、UART、GPIO、PWM、传感器总线。

## Fault Handling

- 1 个 Sensor 异常：`DEGRADED`，保留可用功能并显示 Warning。
- 2 个及以上 Sensor 异常：`FAULT`，进入告警状态。
- 数据超过 stale timeout 未更新：标记 `STALE`。
- 数值超出物理范围：标记 `RANGE_ERROR`。
- 驱动读取失败：标记 `IO_ERROR`。

## Host 验证

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/environment_monitor_sim
```
