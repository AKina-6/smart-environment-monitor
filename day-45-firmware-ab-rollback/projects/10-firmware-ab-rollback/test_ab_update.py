from ab_update import ABManager,State
m=ABManager()
assert m.active==0 and m.slots[0].version==1
m.stage(2,0x22)
assert m.boot(0x22)==1
m.confirm()
assert m.active==1 and m.slots[1].version==2
m.stage(3,0x33)
assert m.boot(0x33)==0
m.boot_failed(); m.boot(0x33); m.boot_failed(); m.boot(0x33); m.boot_failed()
assert m.slots[0].state==State.INVALID
assert m.active==1 and m.slots[1].version==2
print("PASS: upgrade and rollback")
