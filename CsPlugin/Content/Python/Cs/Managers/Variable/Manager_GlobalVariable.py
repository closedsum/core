# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# IMPORT

# Variable
import Cs.Managers.Variable.GlobalVariable as Cs_GlobalVariable

# ALIAS

# "alias" - class (py)
FPyGlobalVariable = Cs_GlobalVariable.FPyGlobalVariable

class FPyManager_GlobalVariable:
    _instance = None

    def __init__(self):
        if FPyManager_GlobalVariable._instance is not None:
            raise Exception("FPyManager_GlobalVariable cannot be instantiated more than once.")
        else:
            FPyManager_GlobalVariable._instance = self

        self.IntVariables: dict[str, FPyGlobalVariable[int]] = {}

    @staticmethod
    def Get():
        if FPyManager_GlobalVariable._instance is None:
            FPyManager_GlobalVariable()
        return FPyManager_GlobalVariable._instance
    
    def Shutdown(self):
        context: str = __class__.Shutdown.__qualname__
        print(context)

    def Reset(self):
        for key, variable in self.IntVariables.items():
            variable.Reset()

    def AddInt(self, key: str, default_value: int) -> FPyGlobalVariable[int]:
        """
        Add an integer variable to the manager.
            If the variable already exists, it will be returned.
            If the variable does not exist, it will be created and returned.

        Args:
            key:            (str): The key of the variable to add.
            default_value:  (int): The default value of the variable.

        Returns:
            (FPyGlobalVariable[int]): The variable that was added.
        """
        variable: FPyGlobalVariable[int]  = None

        if key in self.IntVariables:
            variable = self.IntVariables[key]
        else:
            variable = FPyGlobalVariable[int]()
            variable.SetDefaultValue(default_value)

        self.IntVariables[key] = variable
        return variable
    
    def AddAndSetInt(self, key: str, default_value: int, value: int) -> FPyGlobalVariable[int]:
        variable: FPyGlobalVariable[int]  = self.AddInt(key, default_value)
        variable.SetValue(value)
        return variable
    
    def GetInt(self, key: str) -> int:
        return self.IntVariables[key].GetValue()
    
    def SetInt(self, key: str, value: int):
        self.IntVariables[key].SetValue(value)

_PRIVATE_FPyManager_GlobalVariable: FPyManager_GlobalVariable = FPyManager_GlobalVariable.Get()