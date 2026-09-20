# Day 54：RTOS Memory Management、Static Allocation、Heap 与 Memory Pool

今天进入 RTOS 内存管理。

```text
Task / Driver
     ↓
需要内存
     ↓
Static / Heap / Memory Pool
```

Static Allocation：资源生命周期固定、行为可预测。
Heap Allocation：灵活，但需要关注 Fragmentation 与 allocation latency。
Memory Pool：预先划分固定大小 Block，适合固定大小消息、对象和 Buffer。

本日实现固定 Block Memory Pool，验证 Allocation、Pool Exhaustion、Free、Block Reuse 与 Invalid Pointer Protection。
