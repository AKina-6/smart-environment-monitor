# Day 50：Device Driver Layer、HAL 抽象与统一接口

```text
Application
    ↓
Device Interface
    ↓
Device Driver
    ↓
HAL
    ↓
MCU Peripheral
```

统一设备接口包含 init/read/write，并通过 ready 状态阻止未初始化设备被访问。

今天使用 Virtual Sensor 验证 Driver 生命周期；真实 STM32 项目中可把 HAL 实现替换为 GPIO/I2C/SPI/UART 外设。
