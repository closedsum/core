// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"

class UObject;
struct FCsInterfaceMap;
struct ICsReset;

namespace NCsPooledObject
{
	namespace NPayload
	{
		/**
		* Basic "slice" implementation of the interface: NCsPooledObject::NPayload::IPayload.
		* The slice is intended to "layered" with other objects of the same category
		* (implementing interfaces related to payloads and pooled objects).
		* In this case, payload.
		* The slice shares a InterfaceMap with other slices.
		* The InterfaceMap is usually stored in a separate object for that category.
		*/
		struct CSCORE_API FImplSlice : IPayload
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap
			FCsInterfaceMap* InterfaceMap;

		public:

			// ICsPayload_PooledObject

			bool bAllocated;

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;

			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			FImplSlice();

		protected:

			TArray<ICsReset*> Resets;

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		public:

			void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

		// IPayload
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
			FORCEINLINE const NCsPooledObject::EUpdate& GetUpdateType() const { return UpdateType; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate() { bAllocated = true; }

			void Reset();

			FORCEINLINE const uint32& GetPreserveChangesFromDefaultMask() const { return PreserveChangesFromDefaultMask; }

		#pragma endregion IPayload

		public:

			void AddReset(ICsReset* InReset);

			bool Copy(const FImplSlice* From);
			bool CopyFrom(const FImplSlice* From);

			FORCEINLINE static void Deconstruct(void* Ptr)
			{
				delete static_cast<NCsPooledObject::NPayload::FImplSlice*>(Ptr);
			}
		};
	}
}