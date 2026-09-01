# 系统架构与 Fault Handling

## 数据流

```text
DHT11 ─┐
       ├→ Sensor Snapshot → Validation → Environment Service → Application Policy
BH1750 ┘                                                        ↓
                                                      Fan / Light / Alarm / UI
```

## 为什么把健康状态和测量值分开

`temperature_c = 0` 本身无法表达“真的 0°C”还是“读取失败”。因此测量值和 `sensor_health_t` 必须分离。

## Degraded Mode

单个传感器失败时继续使用剩余可信数据，同时提示系统能力下降。这样比任意单点失败都让整机停止更适合实际嵌入式系统。

## Fault Mode

多个核心输入同时无效时，不再执行依赖这些数据的自动控制，转入告警/安全策略。
