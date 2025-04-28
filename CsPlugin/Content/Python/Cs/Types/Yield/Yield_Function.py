# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import copy
import inspect

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check = CommonLibrary.check
checkf = CommonLibrary.checkf

class NPyYield:
    class FFunction:
        class NCached:
            class NStr:
                CopyFromYield = "NPyYield.FFunction.CopyFromYield"
        def __init__(self):
            self.Fn = None
            self.Caller: object = None
            self.Args: list = []

        def CopyFromYield(self, yieldCommand: dict) -> bool:
            context = NPyYield.FFunction.NCached.NStr.CopyFromYield
            check(CommonLibrary.IsValidObjectChecked(context, yieldCommand))

            # Check 'WaitForFunction' key exists for yieldCommand
            if "WaitForFunction" in yieldCommand:
                check(CommonLibrary.IsFunctionChecked(context, yieldCommand["WaitForFunction"]))

                self.Fn = yieldCommand["WaitForFunction"]

                if ("Args" in yieldCommand) and (type(yieldCommand["Args"] is list)):
                    for e in yieldCommand["Args"]:
                        self.Args.append(e)
                    #self.Args = copy.deepcopy(yieldCommand["Args"])
                    sig = inspect.signature(self.Fn)
                    check(sig.return_annotation is bool)
                return True
            return False

        def Execute(self) -> bool:  
            if len(self.Args) > 0:
                return self.Fn(self.Args)
            return self.Fn()

        def Reset(self):
            self.Fn = None
            self.Args = []