from spi_driver import SPIBus,SPIConfig
b=SPIBus(SPIConfig(mode=3))
rx,e=b.transfer(bytes([0x9f,1,2,3]),10)
assert e=="BUS_ERROR"
b.assert_cs()
rx,e=b.transfer(bytes([0x9f,1,2,3]),10)
assert e=="OK" and rx==bytes([0x9f,1,2,3])
rx,e=b.transfer(bytes([1]),0)
assert e=="TIMEOUT"
b.deassert_cs()
print("PASS: mode, CS, full-duplex, timeout")
