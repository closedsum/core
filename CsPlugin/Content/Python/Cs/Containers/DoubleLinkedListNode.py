# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
from typing import TypeVar, Generic, get_args

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check         = CommonLibrary.check
checkf        = CommonLibrary.checkf
IsValidObject = CommonLibrary.IsValidObject

T = TypeVar('T')

class FPyDoubleLinkedListNode(Generic[T]):
    def __init__(self):
        self.Element: T = None
        self.NextLink: 'FPyDoubleLinkedListNode[T]' = None
        self.PrevLink: 'FPyDoubleLinkedListNode[T]' = None

    def Unlink(self):
        if IsValidObject(self.NextLink) == True:
            self.NextLink.PrevLink = self.PrevLink

        if IsValidObject(self.PrevLink) == True:
            self.PrevLink.NextLink = self.NextLink
       
        self.NextLink = None
        self.PrevLink = None

    def LinkBefore(self, before: 'FPyDoubleLinkedListNode[T]'):
        context: str = __class__.LinkBefore.__qualname__

        check(CommonLibrary.IsInstanceOfChecked(context, before, FPyDoubleLinkedListNode))

        # Get the type parameters of both nodes
        self_type = type(self)
        before_type = type(before)
        
        # Check if both nodes have the same generic type parameter
        self_args = get_args(self_type)
        before_args = get_args(before_type)
        
        if self_args and before_args and self_args[0] != before_args[0]:
            checkf(False, f"{context}: Type parameter mismatch for before. Expected {self_args[0]}, got {before_args[0]}")

        if IsValidObject(self.NextLink) == True:
            self.NextLink.PrevLink = self.PrevLink;

        if IsValidObject(self.PrevLink) == True:
            self.PrevLink.NextLink = self.NextLink;

        self.PrevLink = before.PrevLink;

        if IsValidObject(before.PrevLink) == True:
            before.PrevLink.NextLink = self

        before.PrevLink = self
        self.NextLink   = before

    def LinkAfter(self, after: 'FPyDoubleLinkedListNode[T]'):
        context: str = __class__.LinkAfter.__qualname__

        check(CommonLibrary.IsInstanceOfChecked(context, after, FPyDoubleLinkedListNode))
    
                # Get the type parameters of both nodes
        self_type = type(self)
        after_type = type(after)
        
        # Check if both nodes have the same generic type parameter
        self_args = get_args(self_type)
        after_args = get_args(after_type)
        
        if self_args and after_args and self_args[0] != after_args[0]:
            checkf(False, f"{context}: Type parameter mismatch for after. Expected {self_args[0]}, got {after_args[0]}")

        if IsValidObject(self.NextLink) == True:
            self.NextLink.PrevLink = self.PrevLink

        if IsValidObject(self.PrevLink) == True:
            self.PrevLink.NextLink = self.NextLink

        self.PrevLink = after

        if IsValidObject(after.NextLink) == True:
            after.NextLink.PrevLink = self

        self.NextLink  = after.NextLink
        after.NextLink = self

    def IsLinked(self) -> bool:
        return (IsValidObject(self.NextLink) == True) or (IsValidObject(self.PrevLink) == True)

    def GetElement(self) -> T:
        return self.Element

    def Next(self) -> 'FPyDoubleLinkedListNode[T]':
        return self.NextLink
    def Prev(self) -> 'FPyDoubleLinkedListNode[T]':
        return self.PrevLink
    def GetNextLink(self) -> 'FPyDoubleLinkedListNode[T]':
        return self.NextLink
    def GetPrevLink(self) -> 'FPyDoubleLinkedListNode[T]':
        return self.PrevLink