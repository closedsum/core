# Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

INDEX_NONE = -1

class FPyResourceContainer:
    def __init__(self):
        self.Index: int       = INDEX_NONE
        self.bAllocated: bool = False
        self.Resource: any    = None

    def GetIndex(self) -> int:
        return self.Index
    def SetIndex(self, index: int):
        self.Index = index

    def IsAllocated(self) -> bool: 
        return self.bAllocated
    def Allocate(self):
        self.bAllocated = True
    def Deallocate(self):
        self.bAllocated = False

    def Get(self) -> any:
        return self.Resource
    def Set(self, r: any):
        self.Resource = r