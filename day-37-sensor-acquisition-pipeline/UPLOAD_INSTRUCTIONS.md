# Day 37 上传说明

```bash
cd projects/02-sensor-acquisition-pipeline
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/sensor_pipeline_sim
```

STM32：复用 DHT11/BH1750 驱动；周期调用 `sensor_pipeline_poll()`；业务层通过 `sensor_pipeline_get_snapshot()` 获取统一数据。

```bash
git pull
git add .
git commit -m "feat: add sensor acquisition pipeline filtering and coherent snapshot"
git push
```
