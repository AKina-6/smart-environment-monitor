from dataclasses import dataclass

@dataclass
class Task:
    name:str
    priority:int
    state:str="READY"

class Scheduler:
    def __init__(self): self.tasks=[]
    def add(self,name,priority): self.tasks.append(Task(name,priority))
    def pick(self):
        ready=[t for t in self.tasks if t.state=="READY"]
        if not ready:return None
        t=max(ready,key=lambda x:x.priority);t.state="RUNNING";return t

class Mutex:
    def __init__(self): self.owner=None
    def lock(self,task):
        if self.owner is None:self.owner=task;return True
        return False
    def unlock(self,task):
        if self.owner!=task:return False
        self.owner=None;return True
