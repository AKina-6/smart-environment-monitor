# OLED Dashboard 与 UI State 学习笔记

## UI State 与 Display Driver 分离

Display Driver 只负责：

```text
画点 / 写字符 / 刷新屏幕
```

UI State 负责：

```text
当前是什么页面
下一页是什么
Fault 是否强制覆盖
```

Renderer 负责：

```text
业务数据 → 页面内容
```

这样 SSD1306 更换为 LCD 时，核心 UI 状态仍可以复用。

## Fault 页面优先级

正常页面属于用户导航状态；Fault 页面属于系统安全状态。

因此 Fault 出现时主动抢占当前页面，在恢复后再回到此前页面。

## Data Binding

UI 不直接读取 DHT11/BH1750，而是使用统一 `ui_data_t`。

数据链：

```text
Sensor Pipeline
→ Validation
→ Actuator Policy
→ ui_data_t
→ Renderer
```
