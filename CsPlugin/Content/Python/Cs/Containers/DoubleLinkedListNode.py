# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check         = CommonLibrary.check
checkf        = CommonLibrary.checkf
IsValidObject = CommonLibrary.IsValidObject

class FPyDoubleLinkedListNode:
    class NCached:
        class NStr:
            LinkBefore = "FPyDoubleLinkedListNode.LinkBefore"
            LinkAfter = "FPyDoubleLinkedListNode.LinkAfter"
    def __init__(self):
        self.Element: any = None
        self.NextLink: FPyDoubleLinkedListNode = None
        self.PrevLink: FPyDoubleLinkedListNode = None

    def Unlink(self):
        if IsValidObject(self.NextLink) == True:
            self.NextLink.PrevLink = self.PrevLink

        if IsValidObject(self.PrevLink) == True:
            self.PrevLink.NextLink = self.NextLink
       
        self.NextLink = None
        self.PrevLink = None

    def LinkBefore(self, before: any):
        context: str = FPyDoubleLinkedListNode.NCached.NStr.LinkBefore

        check(CommonLibrary.IsInstanceOfChecked(context, before, FPyDoubleLinkedListNode))

        if IsValidObject(self.NextLink) == True:
            self.NextLink.PrevLink = self.PrevLink;

        if IsValidObject(self.PrevLink) == True:
            self.PrevLink.NextLink = self.NextLink;

        self.PrevLink = before.PrevLink;

        if IsValidObject(before.PrevLink) == True:
            before.PrevLink.NextLink = self

        before.PrevLink = self
        self.NextLink   = before

    def LinkAfter(self, after: any):
        context: str = FPyDoubleLinkedListNode.NCached.NStr.LinkAfter

        check(CommonLibrary.IsInstanceOfChecked(context, after, FPyDoubleLinkedListNode))
    
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

    def GetElement(self) -> any:
        return self.Element

    def Next(self) -> any:
        return self.NextLink
    def Prev(self) -> any:
        return self.PrevLink
    def GetNextLink(self) -> any:
        return self.NextLink
    def GetPrevLink(self) -> any:
        return self.PrevLink