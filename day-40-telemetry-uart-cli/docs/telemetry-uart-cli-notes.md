# Telemetry / UART CLI 学习笔记

## 1. Telemetry
Telemetry 是设备主动暴露运行状态的数据接口，可用于串口调试、日志、上位机或后续网络上传。

## 2. CLI
CLI 负责把文本命令转换为配置读取/修改动作。Parser 与 UART Driver 分开，便于 Host 自动测试。

## 3. Runtime Configuration
在线修改参数时先写入临时副本并做完整约束验证，通过后再原子式替换当前配置，避免半更新状态。

## 4. 安全边界
CLI 改阈值不等于允许任意值。嵌入式配置接口必须保留范围、关系和类型校验。
