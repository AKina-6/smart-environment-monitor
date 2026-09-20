# RTOS Memory Management

Static Allocation 在编译期或静态存储区确定对象和 Buffer 的空间。

Heap：

```text
malloc → use → free
```

长期运行的嵌入式系统需要关注 Fragmentation 和 allocation latency。

Memory Pool：

```text
Pool
├── Block 0
├── Block 1
├── Block 2
└── ...
```

固定 Block 能从设计上避免外部碎片，但只能高效服务于适合固定尺寸的对象。

实时系统通常重视：

```text
Determinism > maximum allocation flexibility
```
