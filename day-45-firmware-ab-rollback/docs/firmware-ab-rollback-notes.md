# Firmware A/B 与 Rollback

A/B Slot 的核心是始终保留一个已确认可启动的 Firmware。

升级：
Download → Verify → Boot → Self-test → Confirm

失败：
Pending → INVALID → Rollback → Active

CRC 用于完整性检测；生产系统还需要数字签名、硬件兼容性检查以及更严格的 Boot Flag / Flash Transaction 设计。
