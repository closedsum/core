// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Object/CsTypes_Object.h"

// Library
#include "Library/CsLibrary_World.h"

namespace NCsObject
{
	namespace NCreate
	{
		void FCreated::DestroyByOwner(UObject* Owner)
		{
			checkf(Owner, TEXT("NCsObject::NCreate::FCreated::DestroyByOwner: Owner is NULL."));

			typedef NCsObject::NCreate::FHandle HandleType;
			typedef NCsObject::NCreate::FObject ObjectType;

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

			typedef NCsObject::NCreate::FHandle HandleType;
			typedef NCsObject::NCreate::FObject ObjectType;

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
			typedef NCsObject::NCreate::FHandle HandleType;
			typedef NCsObject::NCreate::FObject ObjectType;

			for (TPair<HandleType, ObjectType>& Pair : Map)
			{
				const HandleType& Handle = Pair.Key;
				ObjectType& O			 = Pair.Value;

				// If Owner is Valid, check if the Object is Valid.
				if (UObject* Owner = O.GetOwner())
				{
					typedef NCsWorld::FLibrary WorldLibrary;

					if (!IsValid(Owner) ||
						WorldLibrary::IsEditorPreviewOrphaned(Owner))
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
								WorldLibrary::IsEditorPreviewOrphaned(Object))
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