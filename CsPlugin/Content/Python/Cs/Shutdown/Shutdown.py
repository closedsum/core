from abc import ABC, abstractmethod

class IPyCsShutdown(ABC):
    @abstractmethod
    def HasShutdown(self) -> bool:
        pass
    @abstractmethod
    def Shutdown(self):
        pass