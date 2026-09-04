# Project 04：OLED Dashboard、UI State 与 Fault Visualization

## 目标

把环境监测系统的数据和状态稳定地映射到 OLED 页面，而不是在业务代码中直接散落大量 `ssd1306_draw_text()` 调用。

## 页面状态

```text
OVERVIEW
SENSOR
SYSTEM
FAULT
```

正常情况下，用户可以在前三页循环：

```text
OVERVIEW → SENSOR → SYSTEM → OVERVIEW
```

FAULT 页具有更高优先级：

```text
任何普通页面
   ↓ health == FAULT
FAULT
```

故障解除后恢复到进入 Fault 前的页面。

## Overview

显示：

- 温度
- 湿度
- 光照
- Fan
- Light
- Alarm
- 系统 Health

## Sensor

重点显示每个输入数据是否有效：

```text
TEMP 24.5 OK
HUM  46.0 ERR
LUX  520  OK
```

## System

显示：

- Uptime
- Health
- Fault Count
- Page Change Count

## Fault

Fault 页面优先显示：

- Alarm
- 哪个 Sensor 无效
- Fault Count

Fault 时禁止普通按键切页，避免告警信息被用户无意切走。

## 分层

```text
Environment State
      ↓
   ui_data_t
      ↓
   UI State
      ↓
   Renderer
      ↓
SSD1306 Adapter
```

UI Core 不直接依赖 STM32 HAL 或 SSD1306 驱动，因此可以在 Host 上进行自动测试。
