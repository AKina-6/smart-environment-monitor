# DMA 与 Buffer Ownership

Blocking I/O 会让 CPU 等待传输结束。DMA + Interrupt 允许 CPU 在传输期间执行其他工作。

Buffer Ownership 必须明确：

```text
APP → DMA → APP
```

DMA 持有期间，Application 不应修改 Buffer。

Zero-Copy：

```text
Peripheral → DMA Buffer → Application
```

而不是：

```text
Peripheral → DMA Buffer → memcpy → Application Buffer
```
