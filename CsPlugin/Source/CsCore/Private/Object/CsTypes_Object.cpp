// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/CsTypes_Object.h"

// Library
#include "Library/CsLibrary_World.h"
// Actor
#include "GameFramework/Actor.h"

namespace NCsObject
{
	namespace NCreate
	{
		using HandleType = NCsObject::NCreate::FHandle;
		using ObjectType = NCsObject::NCreate::FObject;

		void FCreated::DestroyByOwner(UObject* Owner)
		{
			checkf(Owner, TEXT("NCsObject::NCreate::FCreated::DestroyByOwner: Owner is NULL."));

			for (TPair<HandleType, ObjectType>& Pair : Map)
			{
				ObjectType& O = Pair.Value;

				if (O.GetOwner() == Owner)
				{
					if (UObject* Object = O.GetObject())
					{
						if (IsValid(Object))
						{
							if (AActor* Actor = Cast<AActor>(Object))
								Actor->Destroy();
							else
								Object->MarkAsGarbage();
						}
					}
					ToRemove.Add(Pair.Key);
				}
			}

			for (const HandleType& Handle : ToRemove)
			{
				Map.Remove(Handle);
			}
			ToRemove.Reset(ToRemove.Max());
		}

		void FCreated::DestroyByWorld(UWorld* World)
		{
			checkf(World, TEXT("NCsObject::NCreate::FCreated::DestroyByWorld: Owner is NULL."));

			for (TPair<HandleType, ObjectType>& Pair : Map)
			{
				const HandleType& Handle = Pair.Key;
				ObjectType& O			 = Pair.Value;

				if (UObject* Owner = O.GetOwner())
				{
					if (Owner->GetWorld() == World)
					{
						if (UObject* Object = O.GetObject())
						{
							if (IsValid(Object))
							{
								if (AActor* Actor = Cast<AActor>(Object))
									Actor->Destroy();
								else
									Object->MarkAsGarbage();
							}
						}
						ToRemove.Add(Handle);
					}
				}
				else
				if (UObject* Object = O.GetObject())
				{
					if (Object->GetWorld() == World)
					{
						if (IsValid(Object))
						{
							if (AActor* Actor = Cast<AActor>(Object))
								Actor->Destroy();
							else
								Object->MarkAsGarbage();
						}
						ToRemove.Add(Handle);
					}
				}
			}
			for (const HandleType& Handle : ToRemove)
			{
				Map.Remove(Handle);
			}
			ToRemove.Reset(ToRemove.Max());
		}

		void FCreated::DestroyAndRemoveNullPendingKillOrOrphaned()
		{
			for (TPair<HandleType, ObjectType>& Pair : Map)
			{
				const HandleType& Handle = Pair.Key;
				ObjectType& O			 = Pair.Value;

				// If Owner is Valid, check if the Object is Valid.
				if (UObject* Owner = O.GetOwner())
				{
					if (!IsValid(Owner) ||
						CsWorldLibrary::IsEditorPreviewOrphaned(Owner))
					{
						// If the Object is Valid, check if the Object is about to be destroyed.
						if (UObject* Object = O.GetObject())
						{
							if (IsValid(Object))
							{
								if (AActor* Actor = Cast<AActor>(Object))
									Actor->Destroy();
								else
									Object->MarkAsGarbage();
							}
						}
						ToRemove.Add(Handle);
					}
					else
					{
						// If the Object is Valid, check if the Object is about to be destroyed.
						if (UObject* Object = O.GetObject())
						{
							// If the Object is NOT Valid, add it to the list to be removed.
							if (!IsValid(Object) ||
								CsWorldLibrary::IsEditorPreviewOrphaned(Object))
							{
								ToRemove.Add(Handle);
							}
						}
						// If Object is NULL, add it to the list to be removed.
						else
						{
							ToRemove.Add(Handle);
						}
					}
				}
				// If the Owner is NULL, add it to the list to be removed.
				else
				{
					// If the Object is Valid, Mark the Object to be destroyed.
					if (UObject* Object = O.GetObject())
					{
						if (IsValid(Object))
						{
							if (AActor* Actor = Cast<AActor>(Object))
								Actor->Destroy();
							else
								Object->MarkAsGarbage();
						}
					}
					ToRemove.Add(Handle);
				}
			}

			for (const HandleType& Handle : ToRemove)
			{
				Map.Remove(Handle);
			}
			ToRemove.Reset(ToRemove.Max());
		}
	}
}