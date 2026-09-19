# RTOS Event Group 与 Software Timer

多个事件可压缩到一个 bit mask：

BIT0 = SENSOR_READY
BIT1 = NETWORK_READY
BIT2 = STORAGE_READY

ANY：`(BITS & MASK) != 0`
ALL：`(BITS & MASK) == MASK`

Software Timer 通常由 RTOS Timer Service Task 管理。

Periodic：
```text
|----1000ms----|----1000ms----|----1000ms----|
```

One-shot：
```text
|----500ms----| STOP
```

Timer 回调应保持短小；复杂工作应通过 Queue/Event 通知工作 Task。
