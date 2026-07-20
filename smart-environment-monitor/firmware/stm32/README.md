# STM32 HAL 移植指南

本目录不包含 ST 官方 HAL 源码。请使用 STM32CubeMX 生成工程，再接入本仓库的业务层代码。

## 推荐平台

- MCU：STM32F103C8T6
- IDE：STM32CubeIDE 或 Keil MDK
- HAL：STM32CubeF1
- 系统时钟：72 MHz

## CubeMX 配置建议

| 外设 | 配置 |
|---|---|
| RCC | HSE Crystal/Ceramic Resonator |
| SYS | Serial Wire |
| USART1 | 115200, 8-N-1 |
| I2C1 | 100 kHz 或 400 kHz |
| DHT11 GPIO | Output Open Drain / Input 动态切换 |
| LED GPIO | Push-Pull Output |
| Buzzer GPIO | Push-Pull Output |
| Timer | 1 us 基准延时，可用于 DHT11 |

## 推荐引脚

| 模块 | STM32 引脚 |
|---|---|
| DHT11 DATA | PA0 |
| OLED/BH1750 SCL | PB6 |
| OLED/BH1750 SDA | PB7 |
| USART1 TX | PA9 |
| USART1 RX | PA10 |
| Alarm LED | PB0 |
| Buzzer | PB1 |

## 接入步骤

1. 将根目录 `include/` 与 `src/app/` 添加到工程。
2. 在 CubeMX 生成的 `main.c` 中创建 `environment_monitor_t`。
3. 实现下列平台函数：
   - 读取 DHT11
   - 读取 BH1750
   - 更新 SSD1306
   - 控制 LED 和蜂鸣器
   - 通过 USART1 发送字符串
4. 每隔 `MONITOR_SAMPLE_PERIOD_MS` 调用一次 `environment_monitor_process()`。

## 主循环示例

```c
environment_monitor_t monitor;
environment_data_t data;
char telemetry[MONITOR_JSON_BUFFER_SIZE];

environment_monitor_init(&monitor);

while (1)
{
    data.temperature_c = dht11_temperature();
    data.humidity_pct = dht11_humidity();
    data.light_lux = bh1750_read_lux();
    data.timestamp_ms = HAL_GetTick();
    data.valid = sensors_are_valid();

    uint32_t alarm = environment_monitor_process(
        &monitor,
        &data,
        telemetry,
        sizeof(telemetry)
    );

    oled_show_environment(&data, alarm);
    alarm_output_set(alarm != 0U);
    HAL_UART_Transmit(
        &huart1,
        (uint8_t *)telemetry,
        strlen(telemetry),
        100U
    );

    HAL_Delay(MONITOR_SAMPLE_PERIOD_MS);
}
```

实际工程中建议使用非阻塞驱动或 FreeRTOS 任务替代长时间阻塞延时。
