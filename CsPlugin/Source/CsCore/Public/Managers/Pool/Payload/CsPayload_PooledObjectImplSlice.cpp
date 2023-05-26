// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Reset
#include "Reset/CsReset.h"

const FName NCsPooledObject::NPayload::FImplSlice::Name = FName("NCsPooledObject::NPayload::FImplSlice");

namespace NCsPooledObject
{
	namespace NPayload
	{ 
		FImplSlice::FImplSlice() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// IPayload
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			Resets()
		{
		}

		void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
		{
			checkf(InInterfaceMap, TEXT("NCsPooledObject::NPayload::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

			checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsPooledObject::NPayload::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

			InterfaceMap = InInterfaceMap;

			InterfaceMap->Add<IPayload>(FImplSlice::Name, static_cast<IPayload*>(this));
		}

		// IPayload
		#pragma region

		void FImplSlice::Reset()
		{
			// IPayload
			bAllocated = false;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();

			for (ICsReset* R : Resets)
			{
				R->Reset();
			}

			PreserveChangesFromDefaultMask = 0;
		}

		#pragma endregion IPayload

		void FImplSlice::AddReset(ICsReset* InReset)
		{
			Resets.Add(InReset);
		}

		bool FImplSlice::Copy(const FImplSlice* From)
		{
			UpdateType = From->UpdateType;
			Instigator = From->Instigator;
			Owner	   = From->Owner;
			Parent	   = From->Parent;
			Time	   = From->Time;
			PreserveChangesFromDefaultMask = From->PreserveChangesFromDefaultMask;
			return true;
		}

		bool FImplSlice::CopyFrom(const FImplSlice* From)
		{
			return Copy(From);
		}
	}
}