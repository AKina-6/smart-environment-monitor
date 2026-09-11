from dataclasses import dataclass
from enum import Enum

class State(Enum):
    EMPTY=0; PENDING=1; CONFIRMED=2; INVALID=3

@dataclass
class Slot:
    version:int=0
    crc:int=0
    attempts:int=0
    state:State=State.EMPTY

class ABManager:
    def __init__(self):
        self.slots=[Slot(1,state=State.CONFIRMED),Slot()]
        self.active=0
        self.pending=1
        self.max_attempts=3

    def stage(self,version,crc):
        assert version>self.slots[self.active].version
        self.slots[self.pending]=Slot(version,crc,0,State.PENDING)

    def boot(self,calculated_crc):
        p=self.slots[self.pending]
        if p.state!=State.PENDING or p.crc!=calculated_crc:
            p.state=State.INVALID
            return self.active
        p.attempts+=1
        return self.pending

    def confirm(self):
        p=self.slots[self.pending]
        assert p.state==State.PENDING and p.attempts>0
        p.state=State.CONFIRMED
        old=self.active
        self.active=self.pending
        self.pending=old
        self.slots[self.pending]=Slot()

    def boot_failed(self):
        p=self.slots[self.pending]
        if p.state==State.PENDING and p.attempts>=self.max_attempts:
            p.state=State.INVALID
            self.pending=self.active
