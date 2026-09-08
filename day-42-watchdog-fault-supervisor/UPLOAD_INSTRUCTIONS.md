# Day 42 上传说明

目标仓库：`smart-environment-monitor`

```bash
cd projects/07-watchdog-fault-supervisor
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/watchdog_supervisor_sim
```

STM32：配置 IWDG；各关键模块周期调用 heartbeat；主循环统一调用 supervisor poll；只有健康时刷新 IWDG；启动时读取并清 RCC reset flags。

```bash
git pull
git add .
git commit -m "feat: add watchdog fault supervisor reset reason and self recovery"
git push
```
