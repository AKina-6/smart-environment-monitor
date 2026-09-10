# Day 44：Bootloader、Firmware Version 与 Update State Machine

建立最小固件升级模型：

```text
Reset → Bootloader → Application / Update / Recovery
```

候选固件：

```text
DOWNLOADING → READY → VALID → CONFIRMED
```

CRC 校验失败：

```text
READY → INVALID → RECOVERY
```

Bootloader 负责启动模式选择、候选固件管理、完整性校验和升级确认；Application 负责正常业务。

本日先实现状态机，不伪造真实 Flash 擦写、签名验证和 A/B 固件分区。
