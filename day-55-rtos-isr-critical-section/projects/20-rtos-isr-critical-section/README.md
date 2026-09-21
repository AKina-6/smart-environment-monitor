# Day 55：ISR、Critical Section、ISR-safe API 与 Deferred Work

核心模型：

```text
ISR
 ├── 快速处理硬件事件
 └── post event
        ↓
   Deferred Work
        ↓
       Task
```

Critical Section 用于保护短临界区，并支持嵌套进入/退出。

Deferred Queue 模拟 ISR-safe 的事件投递机制。

真实 RTOS 中只能在 ISR 中调用明确支持 ISR context 的 API；复杂业务逻辑应延后到 Task context。
