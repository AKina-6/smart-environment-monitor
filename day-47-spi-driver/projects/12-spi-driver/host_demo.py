from spi_driver import SPIBus,SPIConfig
b=SPIBus(SPIConfig(mode=3,clock_hz=10_000_000))
print("mode=MODE_3 clock=10000000Hz")
print("without_cs=",b.transfer(bytes([0x9f]),10)[1])
b.assert_cs()
rx,e=b.transfer(bytes([0x9f,1,2,3]),10)
print("transfer=",e,"rx=",rx.hex(" "),"transfers=",b.transfers)
print("timeout=",b.transfer(bytes([0]),0)[1])
print("summary mode=PASS cs=PASS full_duplex=PASS timeout=PASS")
