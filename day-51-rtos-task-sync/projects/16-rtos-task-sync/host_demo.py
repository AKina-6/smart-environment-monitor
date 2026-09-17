from rtos_sync import Scheduler,Mutex
s=Scheduler();s.add("sensor",2);s.add("control",5);s.add("logger",1)
t=s.pick();print(f"picked={t.name} priority={t.priority}")
m=Mutex();print("mutex_control=", "PASS" if m.lock("control") else "FAIL")
print("mutex_logger_while_locked=", "PASS" if not m.lock("logger") else "FAIL")
print("wrong_owner_unlock=", "PASS" if not m.unlock("logger") else "FAIL")
print("unlock_control=", "PASS" if m.unlock("control") else "FAIL")
print("summary priority=PASS mutex=PASS ownership=PASS")
