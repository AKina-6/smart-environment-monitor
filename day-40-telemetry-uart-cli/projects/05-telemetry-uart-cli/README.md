# Project 05：Telemetry、UART CLI 与运行时配置

## 目标

把环境监测系统从“只能固件写死参数”推进到“运行时可观察、可配置”。

### CLI

```text
help
status
get hot_on
set hot_on 31.5
get dark_off
set hold_ms 1500
```

### 配置约束

```text
hot_off < hot_on
dark_on < dark_off
0 <= hold_ms <= 60000
```

因此非法配置不会直接覆盖当前有效配置。

### Telemetry

`status` 输出温湿度、光照、执行器、系统健康状态、Uptime 与 Fault Count。

### 与 Day 38 联动

CLI 修改的 `runtime_config_t` 可直接提供给 Actuator Policy，使阈值无需重新编译即可更新。

### STM32 接入

UART RX 层按字节收集一行；遇到 CR/LF 后调用 `cli_execute()`，再将 Reply 经 USART1 发回。ISR/DMA 层只负责接收字节，命令解析建议放在主循环或任务中。
