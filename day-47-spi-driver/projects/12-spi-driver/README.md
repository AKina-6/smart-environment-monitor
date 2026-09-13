# Day 47：SPI Driver、Full-Duplex、Chip Select 与 SPI Mode

建立 SPI Transaction 抽象：

```text
CS ↓
Clock
MOSI → TX
MISO ← RX
CS ↑
```

支持 SPI Mode 0~3、Clock、Bit Order、CS 控制、Full-Duplex Buffer 和 Timeout。

SPI 与 I²C 的核心差异：
- SPI 通常没有地址字段，设备由独立 CS 选择
- SPI 可以同时发送和接收
- SPI 没有 I²C 的 ACK/NACK
- 多从设备共享 SCLK/MOSI/MISO，各自使用 CS

Host 模型中的 RX 返回 TX 仅用于验证数据流，不代表真实从设备行为。
