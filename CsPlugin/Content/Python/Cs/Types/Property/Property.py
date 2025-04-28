# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check           = CommonLibrary.check
checkf          = CommonLibrary.checkf

class FPyProperty:
    def __init__(self):
        self.Value: any = None

    def Get(self) -> any:
        return self.Value
    def GetValue(self) -> any:
        return self.Value

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