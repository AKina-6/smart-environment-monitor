# Day 39 上传说明

目标仓库：

```text
smart-environment-monitor
```

## 自动测试

```bash
cd projects/04-oled-dashboard-ui-state
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/oled_dashboard_sim
```

## STM32 集成

1. 复用 SSD1306 Driver。
2. 将 Day 36-38 的系统数据整理成 `ui_data_t`。
3. 按键短按调用 `dashboard_button_next()` / `dashboard_button_previous()`。
4. 周期调用 `dashboard_render()`。
5. FAULT 状态应自动跳到 Fault Page。
6. 故障解除后检查是否恢复到此前普通页面。

## Git 提交

```bash
git pull
git add .
git commit -m "feat: add OLED dashboard UI state and fault visualization"
git push
```
