# RTOS Task 与同步

Task 常见状态：

```text
READY → RUNNING → BLOCKED
  ↑                 ↓
  └─────────────────┘
```

当多个 Task Ready 时，Scheduler 根据 Priority 选择运行对象。

多个 Task/ISR 访问共享资源且执行顺序影响结果时，会产生 Race Condition。

Mutex 用于保护共享资源：

```text
Task A → lock → resource → unlock
Task B → blocked while A owns mutex
```

Mutex 必须由 owner 释放。

Priority Inversion 的典型形式：

```text
Low Task 持有 Mutex
High Task 等待 Mutex
Medium Task 持续运行
```

生产 RTOS 通常使用 Priority Inheritance 降低这一问题。
