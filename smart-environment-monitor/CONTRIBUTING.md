# Contributing

1. Create a branch from `main`.
2. Keep hardware-dependent code outside the pure application modules.
3. Use descriptive commit messages such as:
   - `feat: add BH1750 measurement adapter`
   - `fix: handle invalid DHT11 checksum`
   - `docs: add OLED wiring table`
   - `test: cover multiple simultaneous alarms`
4. Run the host build and tests before opening a pull request.
5. Do not commit generated build folders, IDE caches, secrets or large binary files.
