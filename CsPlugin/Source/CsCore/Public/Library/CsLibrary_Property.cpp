// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Property.h"
#include "CsCore.h"

#if WITH_EDITOR

bool FCsLibrary_Property::GetArrayIndex(FPropertyChangedChainEvent& e, const FString& Name, int32& OutIndex)
{
	// A bit of a hack to get access to e.ArrayIndicesPerObject, which is private.
	// Access is needed to determine if a property is part of the chain of events.

	// Get pointer to start of struct
	FProperty** Property = ((FProperty**)(&e));
	char* Base = (char*)Property;

	// Offset by Property
	size_t Offset = sizeof(FProperty*);
	// Offset by MemberProperty
	Offset += sizeof(FProperty*);
	// Offset by ChangeType
	Offset += sizeof(EPropertyChangeType::Type);
	// Offset by ObjectIteratorIndex
	Offset += sizeof(int32);

	TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = *((TArrayView<const TMap<FString, int32>>*)(Base + Offset));

	//default to unknown index
	OutIndex = INDEX_NONE;
	if (ArrayIndicesPerObject.IsValidIndex(e.ObjectIteratorIndex))
	{
		if (const int32* ValuePtr = ArrayIndicesPerObject[e.ObjectIteratorIndex].Find(Name))
		{
			OutIndex = *ValuePtr;

			return true;
		}
	}
	return false;
}

#endif // #if WITH_EDITOR