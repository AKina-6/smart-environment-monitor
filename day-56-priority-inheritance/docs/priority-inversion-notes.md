# Priority Inversion

设：

```text
L: priority 1，持有 Mutex
H: priority 10，等待 Mutex
M: priority 5，Ready
```

H 被阻塞后，如果 L 仍是 priority 1，M 可能持续运行，导致 L 无法及时释放 Mutex。

Priority Inheritance：

```text
H waits for L's Mutex
        ↓
L effective priority = max(L base, H priority)
```

释放 Mutex 后：

```text
L effective priority → L base priority
```

Base Priority 是原始优先级；Effective Priority 是当前参与调度的有效优先级。
