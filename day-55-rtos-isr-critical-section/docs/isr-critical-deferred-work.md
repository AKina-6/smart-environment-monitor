# ISR、Critical Section 与 Deferred Work

ISR 应尽量短，避免阻塞、长时间计算和调用可能阻塞的普通 API。

Critical Section：

```text
enter → interrupts OFF → shared state update → exit → interrupts ON
```

嵌套临界区需要 nesting counter，只有最外层 exit 才恢复中断状态。

ISR-safe API 是专门允许在 interrupt context 使用的接口，很多 RTOS 会提供 `FromISR` 风格 API。

Deferred Work：

```text
ISR → post event → Task handles event
```

这样可以缩短 interrupt latency，并把复杂逻辑放回正常 Task context。
