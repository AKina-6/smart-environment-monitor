# UART DMA 与 Ring Buffer

UART 数据可能持续到达，因此不能要求主循环及时读取每一个字节。

```text
UART → DMA → Ring Buffer
              ↓
          Application
```

Frame Parser 需要处理半帧、完整帧、多帧粘连和错误帧。

本日使用 XOR 作为教学用完整性校验示例；生产协议应依据协议规范使用 CRC-8/CRC-16 等算法。
