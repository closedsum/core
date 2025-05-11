# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import sys
import traceback

# IMPORT

# Types
# - Cs/Types/Delegate/MulticastDelegate.py
import Cs.Types.Delegate.MulticastDelegate as Cs_Types_MulticastDelegate

# ALIAS

# "alias" - class (py)
FPyMulticastDelegate = Cs_Types_MulticastDelegate.FPyMulticastDelegate

class FPySysExceptHookHandler:
    _instance = None

    def __init__(self):
        self.OnHandle_ExceptHook_Event: FPyMulticastDelegate = FPyMulticastDelegate()

        if FPySysExceptHookHandler._instance is not None:
            raise Exception("FPySysExceptHookHandler cannot be instantiated more than once.")
        else:
            FPySysExceptHookHandler._instance = self

    @staticmethod
    def Get():
        if FPySysExceptHookHandler._instance is None:
            FPySysExceptHookHandler()

            # Store the default exception hook, if it's not already stored
            if not hasattr(sys, '__original_excepthook__'):
                sys.__original_excepthook__ = sys.excepthook

            sys.excepthook = FPySysExceptHookHandler.OnHandle_ExceptHook
        return FPySysExceptHookHandler._instance
    
    def Shutdown(self):
        #context: str = __class__.Shutdown.__qualname__

        self.OnHandle_ExceptHook_Event.Broadcast()
        self.OnHandle_ExceptHook_Event.Clear()

        # Reset sys.excepthook to its original behavior
        sys.excepthook = sys.__original_excepthook__  

    @staticmethod
    def OnHandle_ExceptHook(exc_type, exc_value, exc_traceback):
        FPySysExceptHookHandler.Get().Shutdown()

        traceback_details = "\n".join(traceback.extract_tb(exc_traceback).format())

        msg = f"caller: {' '.join(sys.argv)}\n{exc_type}: {exc_value}\n{traceback_details}"
        print(msg)

PRIVATE_FPySysExceptHookHandler: FPySysExceptHookHandler = FPySysExceptHookHandler.Get()