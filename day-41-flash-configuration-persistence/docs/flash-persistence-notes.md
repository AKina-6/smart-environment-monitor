# Flash Configuration Persistence Notes

## 为什么不能直接原地覆盖

Flash 通常需要先擦除整个 Page，再重新编程。擦除或写入过程中掉电会让该 Page 中的数据不可用，因此双槽设计保留一个上一次已验证的版本。

## Sequence

Sequence 表示逻辑版本号。启动时两个槽都有效时选择更新的 Sequence。

## CRC

CRC 用于检测记录损坏，不提供身份认证或抗恶意篡改能力。

## 写入顺序

1. 验证新配置；
2. 选择非活动槽；
3. 擦除；
4. 写入完整记录；
5. 回读；
6. 校验 Magic / Version / CRC；
7. 成功后切换 Active Slot。

## 实物注意

必须依据实际 STM32F103 型号 Flash 容量和 Page Size 重新规划 Slot 地址，并在 linker script 中保留对应区域，避免与程序代码重叠。
