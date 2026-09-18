# RTOS Queue 与 Producer-Consumer

Queue 是 RTOS 中常用的 Inter-Task Communication 机制：

```text
Producer → Queue → Consumer
```

Producer 不直接修改 Consumer 的内部状态。

FIFO 保证先进入的数据先被取出。

真实 RTOS 中 send/receive 通常还可以带 block timeout，使 Task 在没有数据或没有空间时进入 BLOCKED，而不是忙等。

Mutex 主要保护共享资源；Queue 主要传递消息/数据。二者可以组合，但用途不同。
