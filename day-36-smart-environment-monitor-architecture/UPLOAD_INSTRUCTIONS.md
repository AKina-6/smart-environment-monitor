# Day 36 上传说明

目标仓库：`smart-environment-monitor`

```bash
cd projects/01-system-architecture-fault-handling
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/environment_monitor_sim
```

Git：

```bash
git pull
git add .
git commit -m "feat: add layered environment monitor architecture and fault handling"
git push
```
