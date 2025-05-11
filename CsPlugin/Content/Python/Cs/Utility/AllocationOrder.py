# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# Containers
# - Cs/Containers/DoubleLinkedListNode.js
import Cs.Containers.DoubleLinkedListNode as Cs_DoubleLinkedListNode

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - type
FPyDoubleLinkedListNode = Cs_DoubleLinkedListNode.FPyDoubleLinkedListNode

# "typedefs" - function
checkf  = CommonLibrary.checkf

class FPyAllocationOrder:
    def __init__(self):
        self.Links: list[FPyDoubleLinkedListNode] = []
        self.Head: FPyDoubleLinkedListNode = None
        self.Tail: FPyDoubleLinkedListNode = None
        self.Size: int = 0

    def Shutdown(self):
        self.Links = []
        self.Head = None
        self.Tail = None
        self.Size = 0

    def Reset(self):
        for i in range(0, self.Size):
            link: FPyDoubleLinkedListNode = self.Links[i]
            link.Unlink()

        self.Head = None
        self.Tail = None

        for i in range(0, self.Size):
            link: FPyDoubleLinkedListNode = self.Links[i]
            self.AddToTail(link)

    def Create(self, size: int):
        context: str = __class__.Create.__qualname__

        checkf(type(size) is int, context + ": s is NOT an Integer.")
        checkf(size > 0, context + ": size: " + str(size) + " is NOT > 0.")
        checkf(size != self.Size, context + ": Size is already size: " + str(size))

        self.Shutdown();

        self.Size = size;

        self.Links = []

        for i in range(0, self.Size):
            self.AddNewToTail()

    def GetLinks(self) -> list[FPyDoubleLinkedListNode]:
        return self.Links
    def GetHead(self) -> FPyDoubleLinkedListNode:
        return self.Head
    def GetTail(self) -> FPyDoubleLinkedListNode:
        return self.Tail
    def GetSize(self) -> int:
        return self.Size

    def Add(self):
        self.AddNewToTail()

        self.Size += 1

    def AddToTail(self, link: FPyDoubleLinkedListNode):
        if self.Tail != None:
            link.LinkAfter(self.Tail)

            self.Tail = link
        else:
            self.Head = link
            self.Tail = self.Head

    def AddNewToTail(self):
        link: FPyDoubleLinkedListNode = FPyDoubleLinkedListNode()
    
        self.Links.append(link)

        link.Element = len(self.Links) - 1

        self.AddToTail(link)

    def AddBefore(self, link: FPyDoubleLinkedListNode, linkBefore: FPyDoubleLinkedListNode):
        link.LinkBefore(linkBefore)

        if linkBefore == self.Head:
            self.Head = link

    def AddBeforeHead(self, link: FPyDoubleLinkedListNode):
        self.AddBefore(link, self.Head)

    def MoveHeadToTail(self):
        previousHead: FPyDoubleLinkedListNode = self.Head

        self.Head = self.Head.GetNextLink()

        previousHead.Unlink();
        self.AddToTail(previousHead)

    def Remove(self, link: FPyDoubleLinkedListNode):
        # Check to Update HEAD
        if link == self.Head:
            self.Head = link.GetNextLink()

            if self.Head == None:
                self.Tail = None
        # Check to Update TAIL
        elif link == self.Tail:
            self.Tail = link.GetPrevLink()
        link.Unlink()

    def MoveToHead(self, index: int):
        link: FPyDoubleLinkedListNode = self.Links[index]

        self.Remove(link)
        self.AddBeforeHead(link)

    def Advance(self) -> any:
        value: any = self.Head.Element

        self.MoveHeadToTail();
        return value

    def Promote(self, index: int):
        self.MoveToHead(index)