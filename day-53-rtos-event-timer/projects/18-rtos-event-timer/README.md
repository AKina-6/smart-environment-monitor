# Day 53：RTOS Event Group、Software Timer 与周期任务

Event Group 用 Bit Mask 表示多个系统事件，可等待 ANY 或 ALL。

Software Timer 支持 Periodic Auto-reload 与 One-shot 模式。

```text
Event:
Task A ──set bits──→ [EVENT FLAGS] ←wait── Task B

Timer:
Start → elapsed time → expiration → event/callback
```

本日 Host 模型验证事件组合、清除和定时器行为；真实 FreeRTOS 中可映射到 EventGroup、xTimer 与 Tick 系统。
