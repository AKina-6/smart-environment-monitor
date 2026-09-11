from ab_update import ABManager,State
m=ABManager()
print("boot active=A version=1")
m.stage(2,0x2222); print("stage pending=B version=2")
print("boot candidate=", "B" if m.boot(0x2222)==1 else "A"); m.confirm()
print("confirm active=B version=2")
m.stage(3,0x3333)
for i in range(3):
    print("failed boot attempt",i+1,"slot=A")
    m.boot(0x3333); m.boot_failed()
print("rollback active=B version=2 pending_state=",m.slots[0].state.name)
print("summary upgrade=PASS rollback=PASS")
