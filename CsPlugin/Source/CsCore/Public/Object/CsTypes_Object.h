// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "UObject/WeakObjectPtr.h"

class UObject;

namespace NCsObject
{
	namespace NCreate
	{
		struct CSCORE_API FHandle
		{
		public:

			int32 Index;

			FGuid Handle;

			FHandle() :
				Index(INDEX_NONE),
				Handle()
			{
			}

			FORCEINLINE bool operator==(const FHandle& B) const
			{
				return Index == B.Index && Handle == B.Handle;
			}

			FORCEINLINE bool operator!=(const FHandle& B) const
			{
				return !(*this == B);
			}

			FORCEINLINE const int32& GetIndex() const { return Index; }

			friend uint32 GetTypeHash(const FHandle& InHandle)
			{
				return GetTypeHash(InHandle.Handle);
			}

			FORCEINLINE bool IsValid() const
			{
				return Index > INDEX_NONE && Handle.IsValid();
			}

			FORCEINLINE void New()
			{
				Handle = FGuid::NewGuid();
			}

			FORCEINLINE void Reset()
			{
				Handle.Invalidate();
			}
		};

		struct CSCORE_API FObject
		{
			TWeakObjectPtr<UObject> Object;

			TWeakObjectPtr<UObject> Owner;

			FObject() :
				Object(nullptr),
				Owner(nullptr)
			{
			}

			FORCEINLINE UObject* GetObject() { return Object.IsValid() ? Object.Get() : nullptr; }

			FORCEINLINE UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
			
		};

		struct CSCORE_API FCreated
		{
		private:

			using HandleType = NCsObject::NCreate::FHandle;
			using ObjectType = NCsObject::NCreate::FObject;

			TMap<HandleType, ObjectType> Map;

			TArray<HandleType> ToRemove;

		public:

			FCreated() :
				Map(),
				ToRemove()
			{
			}

			FORCEINLINE TArray<HandleType>& GetToRemove() { return ToRemove; }

			FORCEINLINE ObjectType* Find(const HandleType& Handle) { return Map.Find(Handle); }

			FORCEINLINE ObjectType* FindByObject(UObject* Object)
			{
				checkf(Object, TEXT("NCsObject::NCreate::FCreated::FindByOwner: Object is NULL."));

				for (TPair<HandleType, ObjectType>& Pair : Map)
				{
					HandleType& Handle = Pair.Key;
					ObjectType& O	   = Pair.Value;

					if (O.GetObject() == Object)
					{
						return &O;
					}
				}
				return nullptr;
			}

			FORCEINLINE void FindByOwner(UObject* Owner, TArray<HandleType>& OutHandles, TArray<ObjectType>& OutObjects)
			{
				checkf(Owner, TEXT("NCsObject::NCreate::FCreated::FindByOwner: Owner is NULL."));

				for (TPair<HandleType, ObjectType>& Pair : Map)
				{
					HandleType& Handle = Pair.Key;
					ObjectType& O	   = Pair.Value;

					if (O.GetOwner() == Owner)
					{
						OutHandles.Add(Handle);
						OutObjects.Add(O);
					}
				}
			}

			FORCEINLINE HandleType Add(UObject* Object, UObject* Owner)
			{
				checkf(Object, TEXT("NCsObject::NCreate::FCreated::Add: Object is NULL."));
				checkf(Owner, TEXT("NCsObject::NCreate::FCreated::Add: Owner is NULL."));

				HandleType Handle;
				Handle.New();

				ObjectType& O = Map.Add(Handle);
				O.Object = Object;
				O.Owner  = Owner;

				return Handle;
			}

			FORCEINLINE void Remove(const HandleType& Handle) { Map.Remove(Handle); }

			FORCEINLINE void Remove(const TArray<HandleType>& Handles)
			{
				for (const HandleType& Handle : Handles)
				{
					Map.Remove(Handle);
				}

				if (&ToRemove == &Handles)
					ToRemove.Reset(ToRemove.Max());
			}

			FORCEINLINE void RemoveByOwner(UObject* Owner)
			{
				checkf(Owner, TEXT("NCsObject::NCreate::FCreated::RemoveByOwner: Owner is NULL."));

				for (TPair<HandleType, ObjectType>& Pair : Map)
				{
					ObjectType& O = Pair.Value;

					if (O.GetOwner() == Owner)
						ToRemove.Add(Pair.Key);
				}

				for (const HandleType& Handle : ToRemove)
				{
					Map.Remove(Handle);
				}
				ToRemove.Reset(ToRemove.Max());
			}

			void DestroyByOwner(UObject* Owner);

			void DestroyByWorld(UWorld* World);

			void DestroyAndRemoveNullPendingKillOrOrphaned();
		};
	}
}