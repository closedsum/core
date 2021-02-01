// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsObject
{
	namespace NCreate
	{
		struct CSCORE_API FHandle
		{
		public:

			UPROPERTY()
			int32 Index;

			UPROPERTY()
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
		#define HandleType NCsObject::NCreate::FHandle
		#define ObjectType NCsObject::NCreate::FObject

		private:

			TMap<HandleType, ObjectType> Map;

			TArray<HandleType> ToRemove;

		public:

			FCreated() :
				Map(),
				ToRemove()
			{
			}

			FORCEINLINE TArray<HandleType>& GetToRemove() { return ToRemove; }

			FORCEINLINE ObjectType* Get(const HandleType& Handle) { return Map.Find(Handle); }

			FORCEINLINE void Get(UObject* Owner, TArray<HandleType>& OutHandles, TArray<ObjectType>& OutObjects)
			{
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

		#undef HandleType
		#undef ObjectType
		};
	}
}