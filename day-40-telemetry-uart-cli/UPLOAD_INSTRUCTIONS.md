# Day 40 上传说明

目标仓库：`smart-environment-monitor`

```bash
cd projects/05-telemetry-uart-cli
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/telemetry_cli_sim
```

STM32 侧复用已有 USART1 RX interrupt/DMA，将收到的一行交给 `cli_execute()`。运行时配置可直接连接 Day 38 Actuator Policy。

```bash
git pull
git add .
git commit -m "feat: add telemetry UART CLI and runtime configuration interface"
git push
```
