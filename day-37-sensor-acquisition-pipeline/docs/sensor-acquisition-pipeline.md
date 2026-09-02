# Sensor Acquisition Pipeline Notes

## 1. Acquisition 和 Application 解耦
采集层负责什么时候读取、如何滤波、数据是否有效；Application 只消费 Snapshot。

## 2. Moving Average
窗口内样本等权平均，适合降低随机抖动，但会增加延迟。

## 3. EMA
`y[k] = alpha*x[k] + (1-alpha)*y[k-1]`。不需要保存整个窗口，适合 MCU。

## 4. Snapshot consistency
多传感器采样时刻不同，Snapshot 必须携带每个通道 timestamp。只有时间跨度满足要求时才视为 coherent。
