# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Utility/Log.py
import Cs.Utility.Log as Cs_Utility_Log
# Variable
import Cs.Managers.Variable.GlobalVariable as Cs_GlobalVariable

# ALIAS

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - class (py)
FPyLog = Cs_Utility_Log.FPyLog
FPyGlobalVariable = Cs_GlobalVariable.FPyGlobalVariable

# "alias" - enum (py)
LogType = FPyLog.EType

# "alias" - function (py)
checkf = FPyCommonLibrary.checkf

# Constants

SHOW_LOG = 1

class FPyManager_GlobalVariable:
    _instance = None

    def __init__(self):
        if FPyManager_GlobalVariable._instance is not None:
            raise Exception("FPyManager_GlobalVariable cannot be instantiated more than once.")
        else:
            FPyManager_GlobalVariable._instance = self

        self.LogType = LogType.PRINT
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

    def SetLogType(self, log_type: LogType):
        self.LogType = log_type

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
        """
        Add an integer variable to the manager and set the value.
            If the variable already exists, it will be returned.
            If the variable does not exist, it will be created and returned.

        Args:
            key:            (str): The key of the variable to add.
            default_value:  (int): The default value of the variable.
            value:          (int): The value to set the variable to.

        Returns:
            (FPyGlobalVariable[int]): The variable that was added.
        """
        variable: FPyGlobalVariable[int]  = self.AddInt(key, default_value)
        variable.SetValue(value)
        return variable
    
    def GetInt(self, key: str) -> int:
        """
        Get the value of an Integer Global Variable.

        Args:
            key: (str): The key of the Global Variable to get.

        Returns:
            (int): The value of the Global Variable.
        """
        context: str = __class__.GetInt.__qualname__
        checkf(key in self.IntVariables, f"{context}: Global Variable: {key} has NOT been added.")
        return self.IntVariables[key].GetValue()
    
    def SetInt(self, key: str, value: int):
        context: str = __class__.SetInt.__qualname__
        checkf(key in self.IntVariables, f"{context}: Global Variable: {key} has NOT been added.")
        self.IntVariables[key].SetValue(value)

    def CanShowLog(self, key: str) -> bool:
        """
        Check if the log should be shown for the given key.
            ASSUME: The Global Variable associated with key is meant for logging.
            ASSUME: The Global Variable is an integer.
            ASSUME: Showing a log means the Global Variable == 1 (SHOW_LOG)

        Args:
            key: (str): The key of the Global Variable to check.

        Returns:
            (bool): True if the log should be shown, False otherwise.
        """
        context: str = __class__.CanShowLog.__qualname__

        checkf(key in self.IntVariables, f"{context}: Global Variable: {key} has NOT been added.")
        return self.IntVariables[key].GetValue() == SHOW_LOG
    
    def ConditionalShowLog(self, key: str, message: str):
        """
        Show a log if the Global Variable associated with key is meant for logging.
            ASSUME: The Global Variable associated with key is meant for logging.
            ASSUME: The Global Variable is an integer.
            ASSUME: Showing a log means the Global Variable == 1 (SHOW_LOG)

        Args:
            key:       (str): The key of the Global Variable to check.
            message:   (str): The message to show if the log should be shown.
        """
        if self.CanShowLog(key):
            FPyLog.Log(self.LogType, message)

_PRIVATE_FPyManager_GlobalVariable: FPyManager_GlobalVariable = FPyManager_GlobalVariable.Get()