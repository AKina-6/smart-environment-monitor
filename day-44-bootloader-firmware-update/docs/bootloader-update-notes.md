# Bootloader 学习笔记

## Image
Version、Size、Integrity Check 是基本元数据；生产系统还应考虑 Signature、Hardware Compatibility 和 Build Information。

## Upgrade
旧版本 A → 下载 B → 校验 B → 启动 B → 自检 → Confirm B。

若 B 启动失败，应能够 Rollback 到 A。

CRC 可检测损坏，但不能证明固件来源可信；Secure Boot 需要数字签名验证。
