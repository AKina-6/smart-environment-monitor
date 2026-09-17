# Day 51：RTOS Task Architecture、Priority、Mutex 与 Race Condition

建立最小 RTOS-like 调度与同步模型。

```text
Sensor Task ─┐
Control Task ├→ Scheduler → CPU
Logger Task ─┘

Shared Resource → Mutex → Owner
```

Scheduler 按 Priority 选择 Ready Task。Mutex 记录 owner，并阻止其他 Task 释放资源。

本日重点是 RTOS 核心概念与状态模型；真实 FreeRTOS API、抢占式 tick 和 priority inheritance 留作后续目标板集成。
