# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal
import sys
from enum import Enum

# Types
# - Cs/Types/Enum/Enum.py
import Cs.Types.Enum.Enum as Cs_Enum
# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "ALIAS"

# "alias" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - class (py)
FPyEnum = Cs_Enum.FPyEnum

# "alias" - functions (py)
check               = CommonLibrary.check
IsValidDictChecked  = CommonLibrary.IsValidDictChecked
IsInstanceOfChecked = CommonLibrary.IsInstanceOfChecked

class NPyYield:
    class FEnum:
        class NCached:
            class NStr:
                CopyFromYield = "NPyYield.FEnum.CopyFromYield"
        def __init__(self):
            self.EnumContainer: Cs_Enum.FPyEnum = None
            self.Value: Enum = None

        def CopyFromYield(self, yieldCommand: dict) -> bool:
            context: str = "NJsYield.FEnum.CopyFromYield"

            check(IsValidDictChecked(context, yieldCommand))

            # Check 'WaitForEnum' key exists for yieldCommand
            if ("WaitForEnum" in yieldCommand) and ("Value" in yieldCommand):
                # Check yieldCommand.WaitForEnum is of type: FJsEnum.FValue
                check(IsInstanceOfChecked(context, yieldCommand["WaitForEnum"], FPyEnum))
                check(IsInstanceOfChecked(context, yieldCommand["Value"], Enum))
 
                self.EnumContainer = yieldCommand["WaitForEnum"]
                self.Value         = yieldCommand["Value"]
                return True
            return False
        
        def Execute(self) -> bool:
            return self.EnumContainer.GetValue() == self.Value

        def Reset(self):
            self.EnumContainer = None
            self.Value = None