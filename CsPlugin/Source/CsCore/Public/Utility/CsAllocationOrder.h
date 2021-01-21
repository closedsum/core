// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Containers
#include "Containers/CsDoubleLinkedList.h"
#pragma once

/**
*/
struct CSCORE_API FCsAllocationOrder
{
private:

	TArray<TCsDoubleLinkedList<int32>*> Links;

	TCsDoubleLinkedList<int32>* Head;

	TCsDoubleLinkedList<int32>* Tail;

	int32 Size;

public:

	FCsAllocationOrder() :
		Links(),
		Head(nullptr),
		Tail(nullptr),
		Size(0)
	{
	}

	~FCsAllocationOrder()
	{
		Shutdown();
	}

	void Shutdown()
	{
		for (int32 I = 0; I < Size; ++I)
		{
			TCsDoubleLinkedList<int32>* Link = Links[I];
			delete Link;
			Links[I] = nullptr;
		}
		Links.Reset();

		Head = nullptr;
		Tail = nullptr;
		Size = 0;
	}

	void Reset()
	{
		for (int32 I = 0; I < Size; ++I)
		{
			TCsDoubleLinkedList<int32>* Link = Links[I];
			Link->Unlink();
		}

		Head = nullptr;
		Tail = nullptr;

		for (int32 I = 0; I < Size; ++I)
		{
			TCsDoubleLinkedList<int32>* Link = Links[I];

			AddToTail(Link);
		}
	}

	void Create(const int32& InSize)
	{
		checkf(InSize > 0, TEXT("FCsAllocationOrder::Create: InSize: %d Is NOT > 0."), InSize);

		checkf(Size != InSize, TEXT("FCsAllocationOrder::Create: Size is already = %d."), Size);

		Shutdown();

		Size = InSize;

		Links.Reset(Size);

		for (int32 I = 0; I < Size; ++I)
		{
			AddNewToTail();
		}
	}

	FORCEINLINE const TArray<TCsDoubleLinkedList<int32>*>& GetLinks() const { return Links; }

	FORCEINLINE const TCsDoubleLinkedList<int32>* GetHead() const { return Head; }

	FORCEINLINE const TCsDoubleLinkedList<int32>* GetTail() const { return Tail; }

	FORCEINLINE const int32& GetSize() const { return Size; }

	FORCEINLINE void Add()
	{
		AddNewToTail();

		++Size;
	}

private:

	/**
	* Add the Link to the Tail (end).
	* Assume Link is Unlinked.
	*/
	FORCEINLINE void AddToTail(TCsDoubleLinkedList<int32>* Link)
	{
		if (Tail)
		{
			Link->LinkAfter(Tail);
			Tail = Link;
		}
		else
		{
			Head = Link;
			Tail = Head;
		}
	}

	/**
	* Add a new Link to the Tail (end). This increases the number (size) of Links.
	*/
	FORCEINLINE void AddNewToTail()
	{
		// Add Link
		Links.Add(new TCsDoubleLinkedList<int32>());
		// Set Element for Link
		TCsDoubleLinkedList<int32>* Link = Links.Last();
		(**Link) = Links.Num() - 1;

		AddToTail(Link);
	}

	/**
	* Add Link before LinkBefore.
	* Assume Link is Unlinked.
	* 
	* @param Link
	* @param LinkBefore
	*/
	FORCEINLINE void AddBefore(TCsDoubleLinkedList<int32>* Link, TCsDoubleLinkedList<int32>* LinkBefore)
	{
		Link->LinkBefore(LinkBefore);

		if (LinkBefore == Head)
		{
			Head = Link;
		}
	}

	/**
	* Add Link before Head. This is equivalent to a Push on a stack and makes Link the new Head.
	* Assume Link is Unlinked.
	* 
	* @param Link
	*/
	FORCEINLINE void AddBeforeHead(TCsDoubleLinkedList<int32>* Link)
	{
		AddBefore(Link, Head);
	}

	/**
	* Move the current Head to be the Tail.
	*/
	FORCEINLINE void MoveHeadToTail()
	{
		TCsDoubleLinkedList<int32>* PreviousHead = Head;

		Head = Head->GetNextLink();

		PreviousHead->Unlink();
		AddToTail(PreviousHead);
	}

	/**
	* Remove the Link and update any other links involved (Head, Tail, ... etc).
	* 
	* @param Link
	*/
	FORCEINLINE void Remove(TCsDoubleLinkedList<int32>* Link)
	{
		// Check to Update HEAD
		if (Link == Head)
		{
			Head = Link->GetNextLink();

			if (!Head)
			{
				Tail = nullptr;
			}
		}
		// Check to Update TAIL
		else
		if (Link == Tail)
		{
			Tail = Link->GetPrevLink();
		}
		Link->Unlink();
	}

	/**
	* Move the Link at Index to the Head. This is equivalent to Pushing the Link 
	* at Index on a stack.
	* 
	* @param Index
	*/
	FORCEINLINE void MoveToHead(const int32& Index)
	{
		TCsDoubleLinkedList<int32>* Link = Links[Index];

		Remove(Link);
		AddBeforeHead(Link);
	}

public:

	/**
	* Get the value of Head and move Head to Tail
	* 
	* return	Value at Head.
	*/
	FORCEINLINE const int32& Advance()
	{
		const int32& Value = **Head;

		MoveHeadToTail();

		return Value;
	}

	/**
	* 
	* 
	* @param Index
	*/
	FORCEINLINE void Promote(const int32& Index)
	{
		MoveToHead(Index);
	}
};