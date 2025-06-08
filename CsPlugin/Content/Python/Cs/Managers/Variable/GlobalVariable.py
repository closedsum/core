# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
from typing import TypeVar, Generic

# IMPORT

# Types
# - Cs/Types/Delegate/MulticastDelegate.py
import Cs.Types.Delegate.MulticastDelegate as Cs_Types_MulticastDelegate

# ALIAS

# "alias" - class (py)
FPyMulticastDelegate = Cs_Types_MulticastDelegate.FPyMulticastDelegate

T = TypeVar('T')

class FPyGlobalVariable(Generic[T]):
    _instance = None

    def __init__(self):
        self.DefaultValue: T = None
        self.Value: T = None

        self.OnChange_Event: FPyMulticastDelegate[T] = FPyMulticastDelegate[T]()

    def Shutdown(self):
        self.DefaultValue = None
        self.Value = None

    def SetDefaultValue(self, default_value: T):
        self.DefaultValue = default_value
        self.Value = default_value

    def GetValue(self) -> T:
        return self.Value
    
    def SetValue(self, value: T):
        previous_value: T = self.Value
        self.Value        = value

        if previous_value != value:
            self.OnChange_Event.Broadcast(value)
        

