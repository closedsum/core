// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsResource_Allocated_StatusEffect.h"

// Data
#include "Data/CsData_StatusEffect.h"

namespace NCsStatusEffect
{
	namespace NAllocated
	{
		#define DataType NCsStatusEffect::NData::IData
		bool FManager::RemoveStatusEffects(const DataType* Data)
		{
		#undef DataType

			const TArray<FECsStatusEffect>& StatusEffectsToRemove = Data->GetStatusEffectsToRemove();

			if (StatusEffectsToRemove.Num() == CS_EMPTY)
				return false;

			bool AnyRemoved = false;

			typedef NCsStatusEffect::NAllocated::FResource ResourceType;
			typedef NCsStatusEffect::FAllocated AllocateType;

			TCsDoubleLinkedList<ResourceType*>* Current = GetAllocatedHead();
			TCsDoubleLinkedList<ResourceType*>* Next	= Current;

			while (Next)
			{
				Current					= Next;
				ResourceType* Container = **Current;
				Next					= Current->GetNextLink();

				AllocateType* R = Container->Get();

				const int32 Index = StatusEffectsToRemove.Find(R->Type);

				if (Index != INDEX_NONE)
				{
					R->Reset();
					Deallocate(Container);

					AnyRemoved = true;
				}
			}
			return AnyRemoved;
		}
	}
}