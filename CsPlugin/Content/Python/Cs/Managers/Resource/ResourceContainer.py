# Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
from typing import TypeVar, Generic

INDEX_NONE = -1

T = TypeVar('T')

class FPyResourceContainer(Generic[T]):
    def __init__(self):
        self.Index: int       = INDEX_NONE
        self.bAllocated: bool = False
        self.Resource: T      = None

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

    def Get(self) -> T:
        return self.Resource
    def Set(self, r: T):
        self.Resource = r