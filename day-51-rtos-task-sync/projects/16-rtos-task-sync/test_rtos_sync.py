from rtos_sync import Scheduler,Mutex
s=Scheduler();s.add("sensor",2);s.add("control",5);s.add("logger",1)
t=s.pick();assert t.name=="control" and t.priority==5
m=Mutex();assert m.lock("control");assert not m.lock("logger");assert not m.unlock("logger");assert m.unlock("control");assert m.lock("logger")
print("PASS: priority, mutex contention, ownership")
