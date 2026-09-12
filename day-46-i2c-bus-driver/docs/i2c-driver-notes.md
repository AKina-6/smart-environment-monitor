# I²C Driver

典型事务：START → Address → ACK/NACK → Data → STOP。

裸机驱动不能无限等待状态位，应使用 Timeout。

SDA stuck-low 时可临时切换 GPIO、产生最多 9 个 SCL 脉冲、尝试释放从设备并生成 STOP，然后恢复 I²C 外设。今天只建立软件状态模型。
