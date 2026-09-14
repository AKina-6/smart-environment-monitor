# Day 48：DMA、Interrupt-driven I/O、Buffer Ownership 与 Zero-Copy

```text
APP owns buffer
    ↓
DMA Start
    ↓
DMA owns buffer
    ↓
Interrupt Completion
    ↓
APP owns buffer
```

DMA 持有 Buffer 时，Application 不应同时修改它。

Zero-Copy 表示尽量让外设 DMA 直接写入后续处理所使用的 Buffer，避免无意义的 memcpy；并不意味着系统任何地方都不能复制。
