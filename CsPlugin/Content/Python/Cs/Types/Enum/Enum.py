# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

from enum import Enum

class FPyEnum:
    def __init__(self):
        self.Value: Enum = None
    def GetValue(self):
        return self.Value