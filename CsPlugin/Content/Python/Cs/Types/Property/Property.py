# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

from typing import Tuple

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# Types
import Cs.Types.Delegate.MulticastDelegate as Cs_Types_Delegate_MulticastDelegate

# "alias" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - class
FPyMulticastDelegate = Cs_Types_Delegate_MulticastDelegate.FPyMulticastDelegate

# "alias" - functions
check           = CommonLibrary.check
checkf          = CommonLibrary.checkf

class FPyProperty:
    def __init__(self):
        self.Value: any = None
        self._previous_value: any = None
        self._on_change_event: FPyMulticastDelegate = FPyMulticastDelegate[Tuple[any, any]]()

    def __setattr__(self, name, value):
        self.__dict__[name] = value

        if name == "Value":
            if "_previous_value" in self.__dict__:
                if value != self.__dict__["_previous_value"]:
                    if "_on_change_event" in self.__dict__:
                        self.__dict__["_on_change_event"].Broadcast(self.__dict__["_previous_value"], value)
                self.__dict__["_previous_value"] = value

    def Get(self) -> any:
        return self.Value
    def GetValue(self) -> any:
        return self.Value
    def GetAsBool(self) -> bool:
        return self.Value == True

    def GetOnChangeEvent(self) -> FPyMulticastDelegate:
        return self._on_change_event

    def IsBoolean(self) -> bool:
        return type(self.Value) is bool
    def IsNumber(self) -> bool:
        return (type(self.Value) is int) or (type(self.Value) is float)
    def IsInt(self) -> bool:
        return type(self.Value) is int
    def IsFloat(self) -> bool:
        return type(self.Value) is float
    def IsFloatChecked(self, context: str) -> bool:
        return CommonLibrary.IsFloatChecked(context, self.Value)
    def IsFloatChecked2(self) -> bool:
        return CommonLibrary.IsFloatChecked2(self.Value)
    def IsString(self) -> bool:
        return type(self.Value) is str
    def IsObject(self) -> bool:
        return isinstance(self.Value, object)
    def IsNonNullObject(self) -> bool:
        return self.Value is None