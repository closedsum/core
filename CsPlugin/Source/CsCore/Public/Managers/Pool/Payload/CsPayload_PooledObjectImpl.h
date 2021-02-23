// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;

			FCsTime Time;

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// IPayload
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate() { bAllocated = true; }

			void Reset();

		#pragma endregion IPayload
		};
	}
}