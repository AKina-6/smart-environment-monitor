# SPI Driver 学习笔记

## CPOL / CPHA

| Mode | CPOL | CPHA |
|---|---:|---:|
|0|0|0|
|1|0|1|
|2|1|0|
|3|1|1|

CPOL 决定 Clock idle level；CPHA 决定有效边沿上的采样/改变关系。

## Full Duplex

每个 Clock 都可以同时产生 MOSI 发送和 MISO 接收，因此 TX/RX Buffer 可以同时存在。

## Chip Select

SPI 通常通过 CS 选择从设备：

```text
MCU
 ├── SCLK ─── shared
 ├── MOSI ─── shared
 ├── MISO ─── shared
 ├── CS_A ─── Device A
 └── CS_B ─── Device B
```
