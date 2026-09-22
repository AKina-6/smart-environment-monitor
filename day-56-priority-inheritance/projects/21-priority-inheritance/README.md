# Day 56：Priority Inversion、Priority Inheritance 与 RTOS Synchronization

典型 Priority Inversion：

```text
Low Task  ── owns ──→ Mutex
High Task ──────────→ waits
Medium Task ────────→ runs
```

没有 Priority Inheritance 时，Low 保持低优先级，High 可能因为 Mutex 间接受到 Medium Task 的影响。

启用 Priority Inheritance：

```text
High waits
   ↓
Low inherits High priority
   ↓
Low releases Mutex
   ↓
Low restores base priority
```

本日实现简化 Priority Mutex，并对比 inheritance off/on。

真实 RTOS 还需处理多个 Mutex、nested lock 和多个 waiting task 等复杂情况。
