# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Array.py
import Cs.Library.Library_Array as Cs_Library_Array

# "typedefs" - library (py)
CommonLibrary   = Cs_Library_Common.NPyCommon.FLibrary
ArrayLibrary    = Cs_Library_Array.NPyArray.FLibrary

# "typedefs" - functions
checkf           = CommonLibrary.checkf
IsNotNoneChecked = CommonLibrary.IsNotNoneChecked
IsNotEmptyChecked = ArrayLibrary.IsNotEmptyChecked
AllNotNoneChecked = ArrayLibrary.AllNotNoneChecked

class NPyDelegate:
    class FParam:
        def __init__(self):
            self.Types = []
        def IsValidChecked(self, context: str, inType: any) -> bool:
            IsNotEmptyChecked(context, self.Types)
            AllNotNoneChecked(context, self.Types)
            IsNotNoneChecked(context, inType)
            passed: bool = False

            count: int = len(self.Types)
            
            for i in range(0, count):
                passed |= self.Types[i] == inType

            if passed == False:
                types: str = ""
                for i in range(0, count - 1):
                    types += str(self.Types[i]) + " | "
                if (count - 1) > 0 == True:
                    types += str(self.Types[count - 1])                   
                checkf(False, "inType: " + str(inType) + " != any of the supported types: "  + types)
            return True
        
    class NMulticast:
        class FOneParam:
            class NCached:
                class NStr:
                    Broadcast = "NPyDelegate.NMulticast.FOneParam.Broadcast"
            def __init__(self):
                self.Functions: dict[str, object] = dict()
                self.Params: list[NPyDelegate.FParam] = []

                param1 = NPyDelegate.FParam()
                self.Params.append(param1)

            def Add(self, func: any):
                # TODO: checks
                self.Functions[str(id(func))] = func

            def Remove(self, func: any):
                # TODO: checks
                self.Functions.pop(str(id(func)), None)

            def Clear(self):
                self.Functions.clear()

            def Broadcast(self, param1: any):
                context: str = NPyDelegate.NMulticast.FOneParam.NCached.NStr.Broadcast

                # Check Params
                count: int = len(self.Params)

                for i in range(0, count):
                    self.Params[i].IsValidChecked(context, type(param1))

                for k, v in self.Functions.items():
                    v(param1)