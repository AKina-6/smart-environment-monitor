# Day 52：RTOS Queue、Producer-Consumer 与 Inter-task Communication

```text
Sensor Task
    ↓ Producer
┌─────────────┐
│ RTOS Queue  │
└─────────────┘
    ↓ Consumer
Control / Logger Task
```

Queue 提供固定容量、FIFO、Producer 写入、Consumer 读取以及 Full/Empty 状态。

相比共享变量 + Mutex，Queue 更适合 Task-to-Task Message Passing，因为数据传递与同步边界天然结合。

本日使用固定长度 Message Buffer 验证 FIFO、Full Protection 与 Producer-Consumer 流程。
