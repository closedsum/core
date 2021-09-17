// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsPooledObject
{
	namespace NPayload
	{
		/**
		* Basic implementation of the interface: NCsPooledObject::NPayload::IPayload
		*/
		struct CSCORE_API FImpl : IPayload
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap
			FCsInterfaceMap* InterfaceMap;

		public:

			bool bAllocated;

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;

			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			FImpl();
			~FImpl();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

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
		};
	}
}