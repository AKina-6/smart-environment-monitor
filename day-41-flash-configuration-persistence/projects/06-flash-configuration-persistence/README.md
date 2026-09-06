# Project 06：Flash Configuration Persistence

把 Day 40 UART CLI 修改的运行时参数保存到非易失 Flash。

## Record

```text
MAGIC | VERSION | SIZE | SEQUENCE | CONFIG | CRC32
```

CRC32 使用 IEEE CRC-32：poly reflected `0xEDB88320`，init `0xFFFFFFFF`，xorout `0xFFFFFFFF`。标准测试向量 `123456789 -> 0xCBF43926`。

## A/B Slot

```text
Slot A          Slot B
 seq=10          seq=11
 valid           valid
                  ↑ newest
```

每次保存写入非当前槽位：

```text
active A
→ erase B
→ write B seq+1
→ read-back verify
→ switch active to B
```

因此旧槽位在新槽位写入并校验成功前始终保留。

## Boot Recovery

启动时分别验证两个槽位的 Magic / Version / Size / Config / CRC，然后选择 Sequence 更新的有效记录。如果最新槽损坏，则回退到另一个有效槽；两个槽都无效则使用默认参数。

## Host verification

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/flash_config_sim
```
