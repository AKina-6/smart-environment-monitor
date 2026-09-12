# Day 46：I²C Bus Driver、Transaction、ACK/NACK、Timeout 与 Bus Recovery

建立 I²C 事务抽象和错误恢复模型。事务包含 Address、Buffer、Length、Timeout。NACK、Timeout、Bus Error 分离处理；检测 SDA stuck-low 后执行 recovery，再重试事务。
