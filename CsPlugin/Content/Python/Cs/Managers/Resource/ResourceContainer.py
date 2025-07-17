# Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
from typing import TypeVar, Generic

INDEX_NONE = -1

T = TypeVar('T')

class FPyResourceContainer(Generic[T]):
    """
    A container for a resource.
    This is used to store a resource in a pool.
    """
    def __init__(self):
        self.Index: int       = INDEX_NONE
        self.bAllocated: bool = False
        self.Resource: T      = None

    def GetIndex(self) -> int:
        """
        Get the index of the resource in the pool.
        """
        return self.Index
    def SetIndex(self, index: int):
        """
        Set the index of the resource in the pool.
        """
        self.Index = index

    def IsAllocated(self) -> bool: 
        """
        Check if the resource is allocated.
        """
        return self.bAllocated
    def Allocate(self):
        """
        Allocate the resource.
        """
        self.bAllocated = True
    def Deallocate(self):
        """
        Deallocate the resource.
        """
        self.bAllocated = False

    def Get(self) -> T:
        """
        Get the resource.
        """
        return self.Resource
    def Set(self, r: T):
        """
        Set the resource.
        """
        self.Resource = r