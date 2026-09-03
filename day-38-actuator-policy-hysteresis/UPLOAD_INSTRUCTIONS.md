# Day 38 上传说明

```bash
cd projects/03-actuator-policy-hysteresis
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/actuator_policy_sim
```

提交：

```bash
git pull
git add .
git commit -m "feat: add actuator hysteresis anti chatter and safe state policy"
git push
```
