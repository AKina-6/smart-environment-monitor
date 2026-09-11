# Day 45：Firmware A/B Slot、Rollback 与升级事务

Active Firmware 与 Pending Firmware 分离。新镜像必须经过验证、首次启动和 Confirm，才成为 Active。连续启动失败达到阈值后，Pending 镜像标记 INVALID，继续使用旧 Active 镜像。

```text
Active A → Stage B → Validate → Boot B → Confirm → Active B
                                      └→ repeated failure → Rollback
```
