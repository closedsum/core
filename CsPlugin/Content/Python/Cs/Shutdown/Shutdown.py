from abc import ABC, abstractmethod

class IPyShutdown(ABC):
    """
    Interface for an object that can be shutdown.
    """
    @abstractmethod
    def HasShutdown(self) -> bool:
        """
        Check if the object has been shutdown.
        """
        pass
    
    @abstractmethod
    def Shutdown(self):
        """
        Shutdown the object.
        """
        pass