git pull
git add .
git commit -m "feat: add bootloader firmware update state machine"
git push

# verify
cmake -S projects/09-bootloader-firmware-update -B build
cmake --build build
ctest --test-dir build --output-on-failure
