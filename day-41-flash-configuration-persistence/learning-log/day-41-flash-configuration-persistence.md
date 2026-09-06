# Day 41：Flash Configuration Persistence

## 已完成
- [x] Runtime Config Record
- [x] Magic / Version / Payload Size
- [x] Sequence
- [x] CRC32 IEEE
- [x] A/B Slot
- [x] Boot newest-valid selection
- [x] Corrupted newest slot fallback
- [x] Defaults when both invalid
- [x] Read-back verification
- [x] Simulated write failure preserves previous config
- [x] STM32 HAL Flash integration sketch
- [x] 2 unit tests
- [x] Host simulation

## STM32 待实物填写
- MCU / Flash Size：
- Page Size：
- Slot A Address：
- Slot B Address：
- CLI set 后掉电恢复：
- CRC 损坏回退：
- 写入次数：

## 下一步
Day 42：Watchdog、Fault Supervisor、Reset Reason 与系统自恢复。
