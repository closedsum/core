// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Property.h"
#include "CsCore.h"

namespace NCsProperty
{
	#if WITH_EDITOR

	TArrayView<const TMap<FString, int32>>& FLibrary::GetArrayIndicesPerObject(FPropertyChangedChainEvent& e)
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

		return *((TArrayView<const TMap<FString, int32>>*)(Base + Offset));
	}

	bool FLibrary::GetArrayIndex(FPropertyChangedChainEvent& e, const FString& Name, int32& OutIndex)
	{
		TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = GetArrayIndicesPerObject(e);

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

	void FLibrary::GetPropertyNamesInChain(FPropertyChangedChainEvent& e, TSet<FString>& OutNames)
	{
		TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = GetArrayIndicesPerObject(e);

		if (ArrayIndicesPerObject.IsValidIndex(e.ObjectIteratorIndex))
		{
			const TMap<FString, int32>& Map = ArrayIndicesPerObject[e.ObjectIteratorIndex];

			for (const TPair<FString, int32>& Pair : Map)
			{
				OutNames.Add(Pair.Key);
			}
		}
	}

	void FLibrary::GetPropertyNamesWithIndexInChain(FPropertyChangedChainEvent& e, TMap<FString, int32>& OutIndexByNameMap)
	{
		TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = GetArrayIndicesPerObject(e);

		if (ArrayIndicesPerObject.IsValidIndex(e.ObjectIteratorIndex))
		{
			const TMap<FString, int32>& Map = ArrayIndicesPerObject[e.ObjectIteratorIndex];

			for (const TPair<FString, int32>& Pair : Map)
			{
				OutIndexByNameMap.Add(Pair.Key, Pair.Value);
			}
		}
	}

	#endif // #if WITH_EDITOR
}