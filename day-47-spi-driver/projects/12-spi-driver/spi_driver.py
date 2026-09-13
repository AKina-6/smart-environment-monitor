from dataclasses import dataclass

@dataclass
class SPIConfig:
    mode:int=0
    clock_hz:int=8_000_000
    lsb_first:bool=False

class SPIBus:
    def __init__(self,cfg):
        self.cfg=cfg; self.cs=False; self.transfers=0

    def assert_cs(self): self.cs=True
    def deassert_cs(self): self.cs=False

    def transfer(self,tx,timeout_ms):
        if not self.cs: return None,"BUS_ERROR"
        if timeout_ms<=0: return None,"TIMEOUT"
        self.transfers+=1
        return bytes(tx),"OK"
