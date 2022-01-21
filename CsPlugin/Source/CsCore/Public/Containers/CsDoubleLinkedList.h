// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Misc/AssertionMacros.h"

template <class ContainerType>
class TCsDoubleLinkedListIteratorBase
{
public:
	explicit TCsDoubleLinkedListIteratorBase(ContainerType* FirstLink)
		: CurrentLink(FirstLink)
	{ }

	/**
	 * Advances the iterator to the next element.
	 */
	FORCEINLINE void Next()
	{
		checkSlow(CurrentLink);
		CurrentLink = (ContainerType*)CurrentLink->GetNextLink();
	}

	FORCEINLINE TCsDoubleLinkedListIteratorBase& operator++()
	{
		Next();
		return *this;
	}

	FORCEINLINE TCsDoubleLinkedListIteratorBase operator++(int)
	{
		auto Tmp = *this;
		Next();
		return Tmp;
	}

	/** conversion to "bool" returning true if the iterator is valid. */
	FORCEINLINE explicit operator bool() const
	{ 
		return CurrentLink != nullptr;
	}

protected:

	ContainerType* CurrentLink;

	FORCEINLINE friend bool operator==(const TCsDoubleLinkedListIteratorBase& Lhs, const TCsDoubleLinkedListIteratorBase& Rhs) { return Lhs.CurrentLink == Rhs.CurrentLink; }
	FORCEINLINE friend bool operator!=(const TCsDoubleLinkedListIteratorBase& Lhs, const TCsDoubleLinkedListIteratorBase& Rhs) { return Lhs.CurrentLink != Rhs.CurrentLink; }
};

template <class ContainerType, class ElementType>
class TCsDoubleLinkedListIterator : public TCsDoubleLinkedListIteratorBase<ContainerType>
{
	typedef TCsDoubleLinkedListIteratorBase<ContainerType> Super;

public:
	explicit TCsDoubleLinkedListIterator(ContainerType* FirstLink)
		: Super(FirstLink)
	{
	}

	// Accessors.
	FORCEINLINE ElementType& operator->() const
	{
		checkSlow(this->CurrentLink);
		return **(this->CurrentLink);
	}

	FORCEINLINE ElementType& operator*() const
	{
		checkSlow(this->CurrentLink);
		return **(this->CurrentLink);
	}
};

/**
 * Base double linked list class
 */
template <class ContainerType, class ElementType, template<class, class> class IteratorType>
class TCsDoubleLinkedListBase
{
public:
	/**
	 * Used to iterate over the elements of a linked list.
	 */
	typedef IteratorType<ContainerType,       ElementType> TIterator;
	typedef IteratorType<ContainerType, const ElementType> TConstIterator;


	/**
	 * Default constructor (empty list)
	 */
	TCsDoubleLinkedListBase() : 
		NextLink(nullptr), 
		PrevLink(nullptr)
	{
	}

	/**
	 * Removes this element from the list in constant time.
	 *
	 * This function is safe to call even if the element is not linked.
	 */
	FORCEINLINE void Unlink()
	{
		if (NextLink)
			NextLink->PrevLink = PrevLink;

		if (PrevLink)
			PrevLink->NextLink = NextLink;

		// Make it safe to call Unlink again.
		NextLink = nullptr;
		PrevLink = nullptr;
	}

	/**
	 * Adds this element to a list, before the given element.
	 *
	 * @param Before	The link to insert this element before.
	 */
	FORCEINLINE void LinkBefore(ContainerType* Before)
	{
		checkf(Before, TEXT("TCsDoubleLinkedListBase::LinkBefore: Before is NULL."));

		if (NextLink)
			NextLink->PrevLink = PrevLink;

		if (PrevLink)
			PrevLink->NextLink = NextLink;

		PrevLink = Before->PrevLink;

		if (Before->PrevLink)
			Before->PrevLink->NextLink = (ContainerType*)this;

		Before->PrevLink = (ContainerType*)this;
		NextLink		 = Before;
	}

	/**
	 * Adds this element to the linked list, after the specified element
	 *
	 * @param After		The link to insert this element after.
	 */
	void LinkAfter(ContainerType* After)
	{
		checkf(After, TEXT("TCsDoubleLinkedListBase::LinkAfter: After is NULL."));

		if (NextLink)
			NextLink->PrevLink = PrevLink;

		if (PrevLink)
			PrevLink->NextLink = NextLink;

		PrevLink = After;

		if (After->NextLink)
			After->NextLink->PrevLink = (ContainerType*)this;

		NextLink		= After->NextLink;
		After->NextLink = (ContainerType*)this;
	}

	// TODO: Update

	/**
	 * Adds this element to the linked list, replacing the specified element.
	 * This is equivalent to calling LinkBefore(Replace); Replace->Unlink();
	 *
	 * @param Replace	Pointer to the element to be replaced
	 */
	/*
	FORCEINLINE void LinkReplace(ContainerType* Replace)
	{
		checkSlow(Replace != nullptr);

		ContainerType**& ReplacePrev = Replace->PrevNextLink;
		ContainerType*& ReplaceNext  = Replace->NextLink;

		PrevNextLink = ReplacePrev;
		NextLink	 = ReplaceNext;

		if (PrevNextLink != nullptr)
		{
			*PrevNextLink = (ContainerType*)this;
		}

		if (NextLink != nullptr)
		{
			NextLink->PrevNextLink = &NextLink;
		}

		ReplacePrev = nullptr;
		ReplaceNext = nullptr;
	}
	*/

	// TODO: Update

	/**
	 * Adds this element as the head of the linked list, linking the input Head pointer to this element,
	 * so that when the element is linked/unlinked, the Head linked list pointer will be correctly updated.
	 *
	 * If Head already has an element, this functions like LinkBefore.
	 *
	 * @param Head		Pointer to the head of the linked list - this pointer should be the main reference point for the linked list
	 */
	/*
	FORCEINLINE void LinkHead(ContainerType*& Head)
	{
		if (Head != nullptr)
		{
			Head->PrevNextLink = &NextLink;
		}

		NextLink	 = Head;
		PrevNextLink = &Head;
		Head		 = (ContainerType*)this;
	}
	*/

	/**
	 * Returns whether element is currently linked.
	 *
	 * @return true if currently linked, false otherwise
	 */
	FORCEINLINE bool IsLinked()
	{
		return NextLink != nullptr || PrevLink != nullptr;
	}

	FORCEINLINE ContainerType* Next()
	{
		return NextLink;
	}

	FORCEINLINE ContainerType* Prev()
	{
		return PrevLink;
	}

	FORCEINLINE ContainerType* GetNextLink() const
	{
		return NextLink;
	}

	FORCEINLINE ContainerType* GetPrevLink() const
	{
		return PrevLink;
	}

private:
	/** The next link in the linked list */
	ContainerType*  NextLink;

	ContainerType* PrevLink;

	FORCEINLINE friend TIterator      begin(      ContainerType& List) { return TIterator     (&List); }
	FORCEINLINE friend TConstIterator begin(const ContainerType& List) { return TConstIterator(const_cast<ContainerType*>(&List)); }
	FORCEINLINE friend TIterator      end  (      ContainerType& List) { return TIterator     (nullptr); }
	FORCEINLINE friend TConstIterator end  (const ContainerType& List) { return TConstIterator(nullptr); }
};

/**
 * Encapsulates a link in a single linked list with constant access time.
 *
 * This linked list is non-intrusive, i.e. it stores a copy of the element passed to it (typically a pointer)
 */
template <class ElementType>
class TCsDoubleLinkedList : public TCsDoubleLinkedListBase<TCsDoubleLinkedList<ElementType>, ElementType, TCsDoubleLinkedListIterator>
{
	typedef TCsDoubleLinkedListBase<TCsDoubleLinkedList<ElementType>, ElementType, TCsDoubleLinkedListIterator>		Super;

public:
	/** Default constructor (empty list). */
	TCsDoubleLinkedList()
		: Super()
	{
	}

	/**
	 * Creates a new linked list with a single element.
	 *
	 * @param InElement The element to add to the list.
	 */
	explicit TCsDoubleLinkedList(const ElementType& InElement)
		: Super()
		, Element(InElement)
	{
	}


	// Accessors.
	FORCEINLINE ElementType* operator->()
	{
		return &Element;
	}
	FORCEINLINE const ElementType* operator->() const
	{
		return &Element;
	}
	FORCEINLINE ElementType& operator*()
	{
		return Element;
	}
	FORCEINLINE const ElementType& operator*() const
	{
		return Element;
	}


private:
	ElementType   Element;
};