from abc import ABC, abstractmethod

class NPyPooledObject:
    class ICache(ABC):
        @abstractmethod
        def IsAllocated(self) -> bool:
            pass

        @abstractmethod
        def Allocate(self):
            pass
        
        @abstractmethod
        def Deallocate(self):
            pass