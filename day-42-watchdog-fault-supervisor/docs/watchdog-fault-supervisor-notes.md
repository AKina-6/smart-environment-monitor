# Watchdog / Fault Supervisor 笔记

## 为什么不能在 Timer ISR 里无条件喂狗
如果固定中断永远执行 `IWDG_Refresh()`，即使主循环或控制模块已经死锁，Watchdog 仍会一直被刷新，失去检测软件失效的意义。

## Heartbeat Ticket
每个关键模块周期上报 `last_heartbeat_ms`。Supervisor 统一判断所有 required 模块是否健康，然后才决定是否喂狗。

## Reset Reason
启动时读取 RCC reset flags，可区分 Power-On、Software Reset、IWDG Reset 等。读取后应清 reset flags，避免影响下一次判断。

## 自恢复边界
Watchdog 只能把系统从“卡死”恢复到重新启动。重复复位仍需要持久化计数、故障日志、降级策略等机制进一步处理。
