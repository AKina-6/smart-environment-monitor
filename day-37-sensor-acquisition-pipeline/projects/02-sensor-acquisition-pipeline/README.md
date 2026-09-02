# Project 02：Sensor Acquisition Pipeline

## 数据流

```text
Physical Sensor
   ↓
Driver Read
   ↓
Raw Sample
   ↓
Filter
   ↓
Timestamped Channel State
   ↓
Coherent Snapshot
   ↓
Service / Application
```

## 采样周期

- Temperature: 1000 ms
- Humidity: 1000 ms
- Light: 250 ms

不同传感器不必使用相同采样频率。

## Filter

Temperature/Humidity：8-sample Moving Average。

Light：EMA，`alpha = 0.25`。

## Coherent Snapshot

Snapshot 不只检查三个值是否存在，还比较每个通道的最后采样时间。最大时间差在 `coherence_window_ms` 内才标记为 coherent。

这避免把“很老的温度”和“刚采到的光照”直接当成同一时刻状态。
