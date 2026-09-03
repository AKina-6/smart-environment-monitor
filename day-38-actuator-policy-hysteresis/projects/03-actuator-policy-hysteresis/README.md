# Project 03：Actuator Policy、Hysteresis 与 Anti-Chatter

## 目标

把 Day 36/37 的环境状态和传感器 Snapshot 转换为稳定、安全的执行器控制。

### 风扇滞回

```text
T >= 30°C -> ON
T <= 28°C -> OFF
28°C < T < 30°C -> 保持当前状态
```

### 灯光滞回

```text
L <= 100 lux -> ON
L >= 150 lux -> OFF
100 < L < 150 -> 保持当前状态
```

### 最小保持时间

即使条件跨过阈值，距离上次切换不足 `min_hold_ms` 时也暂不切换，避免继电器/风扇频繁启停。

### Fault Safe State

进入 `SYSTEM_FAULT`：

```text
fan = OFF
light = OFF
alarm = ON
```

真实产品的安全输出要根据设备风险重新定义，本项目只是演示“故障态必须有明确策略”。
