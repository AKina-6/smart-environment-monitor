# Day 41 上传说明

目标仓库：`smart-environment-monitor`

```bash
cd projects/06-flash-configuration-persistence
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/flash_config_sim
```

STM32 实物集成时必须先依据芯片容量和 linker script 重新确定两个保留 Flash Page 地址。

```bash
git pull
git add .
git commit -m "feat: add flash configuration persistence with CRC and dual slot recovery"
git push
```
