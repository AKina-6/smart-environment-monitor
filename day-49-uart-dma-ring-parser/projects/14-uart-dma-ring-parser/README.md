# Day 49：UART DMA Ring Buffer、Frame Parser 与非阻塞通信

```text
UART RX → DMA → Ring Buffer → Frame Parser → Command/Telemetry
```

协议帧：

```text
0xAA | TYPE | LEN | PAYLOAD | CRC
```

Parser 区分 FORMAT、LENGTH、CRC 错误。Ring Buffer 使用 head/tail 实现固定容量、非阻塞接收。

本日 Host 模型验证协议解析与 Ring Buffer；真实 STM32 UART DMA circular mode / IDLE line 中断留作目标板集成。
