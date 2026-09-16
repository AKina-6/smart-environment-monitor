# Device Driver 与 HAL

HAL 把 MCU 具体硬件操作封装起来；Driver 理解具体设备协议；Application 使用统一接口。

```text
Application → Device Interface → Driver → HAL → Hardware
```

并非所有设备都天然适合 read/write 三接口，生产系统可以继续扩展 control、ioctl、async callback 等能力。
