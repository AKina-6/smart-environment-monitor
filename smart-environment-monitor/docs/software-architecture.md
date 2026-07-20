# 软件架构

## 分层设计

```text
Application
├── environment_monitor
├── alarm_manager
└── telemetry
        ↓
Device Drivers
├── dht11
├── bh1750
└── ssd1306
        ↓
Platform Adapter
├── stm32_hal
└── host_simulation
        ↓
Hardware / Operating System
```

## 核心原则

- 应用逻辑不直接依赖 STM32 HAL。
- 报警规则使用纯 C 实现，可在电脑上单元测试。
- 传感器读取失败通过 `valid` 字段统一上报。
- 遥测层输出统一 JSON，便于串口助手和上位机解析。
- 阈值集中放置在 `config.h`，便于维护。
- MCU 端后续可将主循环拆分为 FreeRTOS 任务。

## 推荐 FreeRTOS 任务划分

| 任务 | 周期 | 优先级建议 |
|---|---:|---:|
| SensorTask | 1000 ms | 中 |
| DisplayTask | 500 ms | 低 |
| AlarmTask | 100 ms | 高 |
| TelemetryTask | 1000 ms | 中 |
| StorageTask | 按需 | 低 |

任务间可通过队列传递 `environment_data_t`，使用互斥锁保护 I²C 总线。
