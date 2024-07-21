// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/CsLibrary_Actor.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Math.h"
#include "Material/CsLibrary_Material.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/PrimitiveComponent.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

namespace NCsActor
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByTag);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByLabel);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetScaleChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetSafeScale);
				// Orientation
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetRotationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeRotation);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetQuatChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetRotationChecked);
				// Movement
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetLocationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetLocationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetLocationAndRotationChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetForwardChecked);

				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeRootComponent);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeRootPrimitiveComponent);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetSafeMaterial);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, SetSafeMaterials);

				const FString _C = TEXT("_C");
			}
		}
	}

	#define LogLevel void(*Log)(const FString&)/*=&NCsCore::NLibrary::FLog::Warning*/
	#define WorldLibrary NCsWorld::FLibrary
	#define MathLibrary NCsMath::FLibrary
	#define NameLibrary NCsName::FLibrary

	FString FLibrary::PrintActorAndClass(const AActor* Actor)
	{
		if (!Actor)
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("Actor: %s with Class: %s"), *(Actor->GetName()), *(Actor->GetClass()->GetName()));
	}

	// Get
	#pragma region

	void FLibrary::GetAllChecked(const FString& Context, const UObject* WorldContext, TArray<AActor*>& OutActors)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			OutActors.Add(A);
		}
		checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find Actors."), *Context);
	}

	void FLibrary::GetAllOfClassChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, TArray<AActor*>& OutActors)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		checkf(ActorClass.Get(), TEXT("%s: ActorClass is NULL"), *Context);

		for (TActorIterator<AActor> It(World, ActorClass); It; ++It)
		{
			AActor* A = *It;

			if (!IsValid(A))
				continue;

			OutActors.Add(A);
		}
		checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find any Actors of type: %s."), *Context, *(ActorClass.Get()->GetName()));
	}

	bool FLibrary::GetSafeAllOfClass(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, TArray<AActor*>& OutActors, LogLevel)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return false;

		CS_IS_SUBCLASS_OF_NULL(ActorClass, AActor)

		for (TActorIterator<AActor> It(World, ActorClass); It; ++It)
		{
			AActor* A = *It;

			if (!IsValid(A))
				continue;

			OutActors.Add(A);
		}

		if (OutActors.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find any Actors of type: %s."), *Context, *(ActorClass.Get()->GetName())));
			return false;
		}
		return true;
	}

	AActor* FLibrary::GetByClassChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_SUBCLASS_OF_NULL_CHECKED(ActorClass, AActor)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			return A;
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			if (!Actor)
			{
				Actor = A;
			}
			else
			{
				checkf(0, TEXT("%s: There are more than one Actor of type ActorClass: %s."), *Context, *(ActorClass.Get()->GetName()));
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(ActorClass.Get()->GetName()));
		return nullptr;
	}

	AActor* FLibrary::GetByClassAndTagChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const FName& Tag)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_SUBCLASS_OF_NULL_CHECKED(ActorClass, AActor)
		CS_IS_NAME_NONE_CHECKED(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (!A->Tags.Contains(Tag))
				continue;
			return A;
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (!A->Tags.Contains(Tag))
				continue;

			if (!Actor)
			{
				Actor = A;
			}
			else
			{
				checkf(0, TEXT("%s: There are more than one Actor of type ActorClass: %s."), *Context, *(ActorClass.Get()->GetName()));
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(ActorClass.Get()->GetName()));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByClassAndTag(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const FName& Tag, LogLevel)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		CS_IS_SUBCLASS_OF_NULL_RET_NULL(ActorClass, AActor)
		CS_IS_NAME_NONE_RET_NULL(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		AActor* Actor = nullptr;

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Actors with the Tag: %s."), *Context, *(Tag.ToString())));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(Tag.ToString())));
		return nullptr;
	}

	AActor* FLibrary::GetByClassAndInterfaceChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const UClass* InterfaceClass)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_SUBCLASS_OF_NULL_CHECKED(ActorClass, AActor)
		CS_IS_PENDING_KILL_CHECKED(InterfaceClass)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass))
			{
				return A;
			}
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors with Class: %s and implements interface: %s."), *Context, *(ActorClass->GetName()), *(InterfaceClass->GetName()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Class: %s and implements interface: %s."), *Context, *(ActorClass->GetName()), *(InterfaceClass->GetName()));
		return nullptr;
	}

	AActor* FLibrary::GetByClassAndInterfaceAndTagChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const UClass* InterfaceClass, const FName& Tag)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_SUBCLASS_OF_NULL_CHECKED(ActorClass, AActor)
		CS_IS_PENDING_KILL_CHECKED(InterfaceClass)
		CS_IS_NAME_NONE_CHECKED(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass) &&
				A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass) &&
				A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors with Class: %s and implements interface: %s and has Tag: %s."), *Context, *(ActorClass->GetName()), *(InterfaceClass->GetName()), *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Class: %s and implements interface: %s."), *Context, *(ActorClass->GetName()), *(InterfaceClass->GetName()));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByClassAndInterfaceAndTag(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const UClass* InterfaceClass, const FName& Tag, LogLevel)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		CS_IS_SUBCLASS_OF_NULL_RET_NULL(ActorClass, AActor)
		CS_IS_PENDING_KILL_RET_NULL(InterfaceClass)
		CS_IS_NAME_NONE_RET_NULL(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass) &&
				A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		AActor* Actor = nullptr;

		for (TActorIterator<AActor> Itr(World, ActorClass); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass) &&
				A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Actors with Class: %s and implements the interface: %s and with the Tag: %s."), *Context, *(ActorClass->GetName()), *(InterfaceClass->GetName()), *(Tag.ToString())));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Class: %s and implements the interface: %s and with Tag: %s."), *Context, *(ActorClass->GetName()), *(InterfaceClass->GetName()), *(Tag.ToString())));
		return nullptr;
	}

	AActor* FLibrary::GetByInterfaceChecked(const FString& Context, const UObject* WorldContext, const UClass* InterfaceClass)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_PENDING_KILL_CHECKED(InterfaceClass)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass))
			{
				return A;
			}
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetClass()->ImplementsInterface(InterfaceClass))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors that implements interface: %s."), *Context, *(InterfaceClass->GetName()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor that implements interface: %s."), *Context, *(InterfaceClass->GetName()));
		return nullptr;
	}

	void FLibrary::GetAllByInterfaceChecked(const FString& Context, const UObject* WorldContext, const UClass* InterfaceClass, TArray<AActor*>& OutActors)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_PENDING_KILL_CHECKED(InterfaceClass)

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			if (A->GetClass()->ImplementsInterface(InterfaceClass))
			{
				OutActors.Add(A);
			}
		}
		checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find Actors that implement interface: %s."), *Context, *(InterfaceClass->GetName()));
	}

	bool FLibrary::GetSafeAllByInterface(const FString& Context, const UObject* WorldContext, const UClass* InterfaceClass, TArray<AActor*>& OutActors, LogLevel)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return false;

		CS_IS_PENDING_KILL(InterfaceClass)


		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* A = *It;

			if (!IsValid(A))
				continue;

			if (A->GetClass()->ImplementsInterface(InterfaceClass))
				OutActors.Add(A);
		}

		if (OutActors.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find any Actors that implement the interface: %s."), *Context, *(InterfaceClass->GetName())));
			return false;
		}
		return true;
	}

	AActor* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_NAME_NONE_CHECKED(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors with the Tag: %s."), *Context, *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(Tag.ToString()));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogLevel)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		CS_IS_NAME_NONE_RET_NULL(Tag)

#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
#else
		AActor* Actor = nullptr;

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Actors with the Tag: %s."), *Context, *(Tag.ToString())));
				}
			}
		}

		if (Actor)
			return Actor;
#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(Tag.ToString())));
		return nullptr;
	}

	void FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			if (A->Tags.Num() < Tags.Num())
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				OutActors.Add(A);
		}
		checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find Actors with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
	}

	bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors, LogLevel)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY(Tags, FName)
		CS_IS_TARRAY_ANY_NONE(Tags)

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			if (A->Tags.Num() < Tags.Num())
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				OutActors.Add(A);
		}

		if (OutActors.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actors with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
		}
		return OutActors.Num() > CS_EMPTY;
	}

	AActor* FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				return A;
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors with the Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, LogLevel)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_RET_NULL(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_RET_NULL(Tags)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				return A;
		}
	#else
		AActor* Actor = nullptr;
		
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Actors with the Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
		return nullptr;
	}

	AActor* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
	{
		CS_IS_PTR_NULL_CHECKED(WorldContext)
		CS_IS_NAME_NONE_CHECKED(Name)

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Actor with Name: %s."), *Context, *(Name.ToString()));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, LogLevel)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (Name == NAME_None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
			return nullptr;
		}

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Name: %s."), *Context, *(Name.ToString())));
		return nullptr;
	}

	AActor* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeByName;

		return GetSafeByName(Context, WorldContext, Name, nullptr);
	}

	AActor* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
	{
	#if WITH_EDITOR
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		checkf(!Label.IsEmpty(), TEXT("%s: Label is EMPTY."), *Context);

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Actor with Label: %s."), *Context, *Label);
		return nullptr;
	#else
		checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
		return nullptr;
	#endif // #if WITH_EDITOR
	}

	AActor* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, LogLevel)
	{
	#if WITH_EDITOR
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (Label.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Label is EMPTY."), *Context));
			return nullptr;
		}

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Label: %s."), *Context, *Label));
		return nullptr;
#else
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Context));
		return nullptr;
#endif // #if !WITH_EDITOR
	}

	AActor* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeByLabel;

		return GetSafeByLabel(Context, WorldContext, Label, nullptr);
	}

	#pragma endregion Get

	// Has
	#pragma region
	
	bool FLibrary::HasTagsChecked(const FString& Context, const AActor* A, const TArray<FName>& Tags)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		int32 Count = Tags.Num();

		for (const FName& Tag : Tags)
		{
			if (A->Tags.Contains(Tag))
				--Count;
		}
		return Count <= 0;
	}

	bool FLibrary::SafeHasTags(const FString& Context, const AActor* A, const TArray<FName>& Tags, LogLevel)
	{
		CS_IS_PTR_NULL(A)
		CS_IS_TARRAY_EMPTY(Tags, FName)
		CS_IS_TARRAY_ANY_NONE(Tags)

		int32 Count = Tags.Num();

		for (const FName& Tag : Tags)
		{
			if (A->Tags.Contains(Tag))
				--Count;
		}
		return Count <= 0;
	}

	bool FLibrary::SafeHasTags(const FString& Context, const AActor* A, const TArray<FName>& Tags, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		CS_IS_PTR_NULL(A)
		CS_IS_TARRAY_EMPTY(Tags, FName)
		CS_IS_TARRAY_ANY_NONE(Tags)

		int32 Count = Tags.Num();

		for (const FName& Tag : Tags)
		{
			if (A->Tags.Contains(Tag))
				--Count;
		}
		OutSuccess = true;
		return Count <= 0;
	}

	bool FLibrary::HasTagChecked(const FString& Context, const AActor* A, const FName& Tag)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_NAME_NONE_CHECKED(Tag)

		return A->Tags.Contains(Tag);
	}

	bool FLibrary::SafeHasTag(const FString& Context, const AActor* A, const FName& Tag, LogLevel)
	{
		CS_IS_PTR_NULL(A)
		CS_IS_NAME_NONE(Tag)

		return A->Tags.Contains(Tag);
	}

	bool FLibrary::SafeHasTag(const FString& Context, const AActor* A, const FName& Tag, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		CS_IS_PTR_NULL(A)
		CS_IS_NAME_NONE(Tag)

		OutSuccess = true;
		return A->Tags.Contains(Tag);
	}

	#pragma endregion Has

	// RootComponent
	#pragma region

	USceneComponent* FLibrary::GetRootComponentChecked(const FString& Context, AActor* Actor)
	{
		CS_IS_PTR_NULL_CHECKED(Actor)

		USceneComponent* RootComponent = Actor->GetRootComponent();

		checkf(RootComponent, TEXT("%s: Actor: %s with Class: %s does NOT have a RootComponent."), *Context, *(Actor->GetName()), *(Actor->GetClass()->GetName()));

		return RootComponent;
	}

	USceneComponent* FLibrary::GetSafeRootComponent(const FString& Context, AActor* Actor, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(Actor)

		USceneComponent* RootComponent = Actor->GetRootComponent();

		if (!RootComponent)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Actor: %s with Class: %s does NOT have a RootComponent."), *Context, *(Actor->GetName()), *(Actor->GetClass()->GetName())));
			return nullptr;
		}
		return RootComponent;
	}

	USceneComponent* FLibrary::GetSafeRootComponent(AActor* Actor)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeRootComponent;

		return GetSafeRootComponent(Context, Actor, nullptr);
	}

	UPrimitiveComponent* FLibrary::GetRootPrimitiveComponentChecked(const FString& Context, AActor* Actor)
	{
		USceneComponent* RootComponent = GetRootComponentChecked(Context, Actor);
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(RootComponent);

		checkf(Component, TEXT("%s: RootComponent: %s with Class: %s is not of type: UPrimitiveComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));

		return Component;
	}

	UPrimitiveComponent* FLibrary::GetSafeRootPrimitiveComponent(const FString& Context, AActor* Actor, LogLevel)
	{
		if (USceneComponent* RootComponent = GetSafeRootComponent(Context, Actor, Log))
		{
			UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(RootComponent);

			if (!Component)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: RootComponent: %s with Class: %s is not of type: UPrimitiveComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName())));
				return nullptr;
			}
			return Component;
		}
		return nullptr;
	}

	UPrimitiveComponent* FLibrary::GetSafeRootPrimitiveComponent(AActor* Actor)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeRootPrimitiveComponent;

		return GetSafeRootPrimitiveComponent(Context, Actor, nullptr);
	}

	#pragma endregion RootComponent

	// Component
	#pragma region
	
	UActorComponent* FLibrary::GetSafeComponentByTag(const FString& Context, const AActor* A, const FName& Tag, LogLevel)
	{
		CS_IS_PENDING_KILL_RET_NULL(A)
		CS_IS_NAME_NONE_RET_NULL(Tag)

		const TSet<UActorComponent*>& Components = A->GetComponents();

		if (Components.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s has NO components."), *Context, *CsObjectLibrary::PrintNameAndClass(A)));
		}

		UActorComponent* Component = nullptr;

		for (UActorComponent* C : Components)
		{
			if (C->ComponentTags.Contains(Tag))
			{
				if (Component)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s has MORE than 1 component with Tag: %s."), *Context, *CsObjectLibrary::PrintNameAndClass(A), *(Tag.ToString())));
				}
				Component = C;
			}
		}

		if (!Component)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s has NO components with Tag: %s."), *Context, *CsObjectLibrary::PrintNameAndClass(A), *(Tag.ToString())));
		}
		return Component;
	}

	#pragma endregion Component

	// Visibility
	#pragma region

	void FLibrary::SetHiddenInGameChecked(const FString& Context, AActor* A, const bool& NewHidden, const bool& ApplyToAttachChildren)
	{
		CS_IS_PTR_NULL_CHECKED(A)

		A->SetActorHiddenInGame(NewHidden);

		if (USceneComponent* RootComponent = A->GetRootComponent())
		{
			RootComponent->SetHiddenInGame(NewHidden, ApplyToAttachChildren);
		}
	}

	bool FLibrary::SetSafeHiddenInGame(const FString& Context, AActor* A, const bool& NewHidden, const bool& ApplyToAttachChildren, LogLevel)
	{
		CS_IS_PTR_NULL(A)

		A->SetActorHiddenInGame(NewHidden);

		if (USceneComponent* RootComponent = A->GetRootComponent())
		{
			RootComponent->SetHiddenInGame(NewHidden, ApplyToAttachChildren);
		}
		return true;
	}

	#pragma endregion Visibility

	void FLibrary::SetScaleChecked(const FString& Context, AActor* A, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		A->SetActorScale3D(MathLibrary::Convert(Scale));
	}

	bool FLibrary::SetSafeScale(const FString& Context, AActor* A, const FVector3f& Scale, LogLevel)
	{
		CS_IS_PENDING_KILL(A)

		A->SetActorScale3D(MathLibrary::Convert(Scale));
		return true;
	}

	// Orientation
	#pragma region

	FRotator3f FLibrary::GetRotationChecked(const FString& Context, const AActor* A)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return MathLibrary::Convert(A->GetActorRotation());
	}

	FRotator3f FLibrary::GetSafeRotation(const FString& Context, const AActor* A, LogLevel)
	{
		CS_IS_PENDING_KILL_RET_VALUE(A, FRotator3f::ZeroRotator)

		return MathLibrary::Convert(A->GetActorRotation());
	}

	FQuat4f FLibrary::GetQuatChecked(const FString& Context, const AActor* A)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return MathLibrary::Convert(A->GetActorQuat());
	}

	void FLibrary::SetRotationChecked(const FString& Context, AActor* A, const FRotator3f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		A->SetActorRotation(MathLibrary::Convert(Rotation));
	}

	void FLibrary::SetRotationChecked(const FString& Context, AActor* A, const FQuat4f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		A->SetActorRotation(MathLibrary::Convert(Rotation));
	}

	#pragma endregion Orientation

	// Movement
	#pragma region 

	bool FLibrary::GetSafeLocation(const FString& Context, const AActor* A, FVector3f& OutLocation, LogLevel)
	{
		CS_IS_PENDING_KILL(A)

		const FVector3d Location = A->GetActorLocation();

		MathLibrary::Set(OutLocation, Location);
		return true;
	}

	FVector3f FLibrary::GetLocationChecked(const FString& Context, const AActor* A)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return MathLibrary::Convert(A->GetActorLocation());
	}

	void FLibrary::SetLocationChecked(const FString& Context, AActor* A, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		A->SetActorLocation(MathLibrary::Convert(Location));
	}

	bool FLibrary::SetLocationAndRotationChecked(const FString& Context, AActor* A, const FVector3f& Location, const FRotator3f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return A->SetActorLocationAndRotation(MathLibrary::Convert(Location), MathLibrary::Convert(Rotation));
	}

	bool FLibrary::SetLocationAndRotationChecked(const FString& Context, AActor* A, const FVector3f& Location, const FQuat4f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return A->SetActorLocationAndRotation(MathLibrary::Convert(Location), MathLibrary::Convert(Rotation));
	}

	FVector3f FLibrary::GetForwardChecked(const FString& Context, const AActor* A)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return MathLibrary::Convert(A->GetActorForwardVector());
	}

	bool FLibrary::TeleportToChecked(const FString& Context, AActor* A, const FVector3f& DestLocation, const FRotator3f& DestRotation, const bool& bIsATest /*=false*/, const bool& bNoCheck /*=false*/)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		return A->TeleportTo(MathLibrary::Convert(DestLocation), MathLibrary::Convert(DestRotation), bIsATest, bNoCheck);
	}

	#pragma endregion Movement

	// Material
	#pragma region


	void FLibrary::SetMaterialChecked(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index)
	{
		UPrimitiveComponent* Component = GetRootPrimitiveComponentChecked(Context, Actor);

		CsMaterialLibrary::SetChecked(Context, Component, Material, Index);
	}

	void FLibrary::SetSafeMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index, LogLevel)
	{
		if (UPrimitiveComponent* Component = GetSafeRootPrimitiveComponent(Context, Actor, Log))
		{
			CsMaterialLibrary::SetSafe(Context, Component, Material, Index, Log);
		}
	}

	void FLibrary::SetSafeMaterial(AActor* Actor, UMaterialInterface* Material, const int32& Index)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::SetSafeMaterial;

		SetSafeMaterial(Context, Actor, Material, Index, nullptr);
	}

	void FLibrary::SetMaterialsChecked(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials)
	{
		UPrimitiveComponent* Component = GetRootPrimitiveComponentChecked(Context, Actor);

		CsMaterialLibrary::SetChecked(Context, Component, Materials);
	}

	void FLibrary::SetSafeMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials, LogLevel)
	{
		if (UPrimitiveComponent* Component = GetSafeRootPrimitiveComponent(Context, Actor, Log))
		{
			CsMaterialLibrary::SetSafe(Context, Component, Materials, Log);
		}
	}

	#pragma endregion Material

	// Spawn
	#pragma region

	AActor* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return nullptr;

		UClass* Class = CsObjectLibrary::SafeLoad<UClass>(Context, Path, Log);

		if (!Class)
			return nullptr;

		AActor* Actor = World->SpawnActor<AActor>(Class);

		if (!Actor)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to Spawn Actor with Class: %s."), *Context, *(Class->GetName())));
		}
		return Actor;
	}

	AActor* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const FString& Path, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FSoftObjectPath SoftPath(Path);

		if (!Path.EndsWith(NCsActor::NLibrary::NCached::Str::_C))
		{
			SoftPath = FSoftObjectPath(Path + NCsActor::NLibrary::NCached::Str::_C);
		}
		return SafeSpawn(Context, WorldContext, SoftPath, Log);
	}

	#pragma endregion Spawn

	// Distance
	#pragma region
	
	float FLibrary::GetSafeDistanceSq(const FString& Context, const AActor* A, const AActor* B, LogLevel)
	{
		CS_IS_PTR_NULL_RET_VALUE(A, 0.0f)
		CS_IS_PTR_NULL_RET_VALUE(B, 0.0f)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();

		return FVector3d::DistSquared(VA, VB);
	}

	float FLibrary::GetDistanceSq2DChecked(const FString& Context, const AActor* A, const AActor* B)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_PTR_NULL_CHECKED(B)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();

		return FVector3d::DistSquared2D(VA, VB);
	}

	float FLibrary::GetSafeDistanceSq2D(const FString& Context, const AActor* A, const AActor* B, LogLevel)
	{
		CS_IS_PTR_NULL_RET_VALUE(A, 0.0f)
		CS_IS_PTR_NULL_RET_VALUE(B, 0.0f)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();

		return FVector3d::DistSquared2D(VA, VB);
	}

	bool FLibrary::IsDistanceSq2D_LessThanOrEqualChecked(const FString& Context, const AActor* A, const AActor* B, const float& R)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_PTR_NULL_CHECKED(B)
		CS_IS_FLOAT_GREATER_THAN_CHECKED(R, 0.0f)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();

		return FVector3d::DistSquared2D(VA, VB) <= (R * R);
	}

	bool FLibrary::SafeIsDistanceSq2D_LessThanOrEqual(const FString& Context, const AActor* A, const AActor* B, const float& R, LogLevel)
	{
		CS_IS_PTR_NULL(A)
		CS_IS_PTR_NULL(B)
		CS_IS_FLOAT_GREATER_THAN(R, 0.0f)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();

		return FVector3d::DistSquared2D(VA, VB) <= (R * R);
	}

	bool FLibrary::IsDistanceSq2D_LessThanOrEqualChecked(const FString& Context, const AActor* A, const FVector3f& Location, const float& R)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_FLOAT_GREATER_THAN_CHECKED(R, 0.0f)

		const FVector3f VA = GetLocationChecked(Context, A);

		return FVector3f::DistSquared2D(VA, Location) <= (R * R);
	}

	bool FLibrary::SafeIsDistanceSq2D_LessThanOrEqual(const FString& Context, const AActor* A, const FVector3f& Location, const float& R, LogLevel)
	{
		CS_IS_PTR_NULL(A)
		CS_IS_FLOAT_GREATER_THAN(R, 0.0f)

		FVector3f VA;
		
		if (!GetSafeLocation(Context, A, VA, Log))
			return false;

		return FVector3f::DistSquared2D(VA, Location) <= (R * R);
	}

	bool FLibrary::IsDistanceSq2D_GreaterThanChecked(const FString& Context, const AActor* A, const FVector3f& Location, const float& R)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_FLOAT_GREATER_THAN_CHECKED(R, 0.0f)

		const FVector3f VA = GetLocationChecked(Context, A);

		return FVector3f::DistSquared2D(VA, Location) > (R * R);
	}

	bool FLibrary::SafeIsDistanceSq2D_GreaterThan(const FString& Context, const AActor* A, const FVector3f& Location, const float& R, LogLevel)
	{
		CS_IS_PTR_NULL(A)
		CS_IS_FLOAT_GREATER_THAN(R, 0.0f)

		FVector3f VA;

		if (!GetSafeLocation(Context, A, VA, Log))
			return false;

		return FVector3f::DistSquared2D(VA, Location) > (R * R);
	}

	#pragma endregion Distance

	// Normal
	#pragma region
	
	bool FLibrary::GetSafeNormalAtoB(const FString& Context, const AActor* A, const AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance, LogLevel)
	{
		CS_IS_PTR_NULL_RET_VALUE(A, 0.0f)
		CS_IS_PTR_NULL_RET_VALUE(B, 0.0f)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();
		const FVector3d V = VB - VA;

		OutNormal = MathLibrary::Convert(MathLibrary::GetSafeNormal(V, OutDistanceSq, OutDistance));

		return V != FVector3d::ZeroVector && OutNormal != FVector3f::ZeroVector;
	}

	void FLibrary::GetNormal2DAtoBChecked(const FString& Context, const AActor* A, const AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance)
	{
		CS_IS_PTR_NULL_CHECKED(A)
		CS_IS_PTR_NULL_CHECKED(B)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();
		const FVector3d& V = VB - VA;

		OutNormal = MathLibrary::Convert(MathLibrary::GetSafeNormal2D(V, OutDistanceSq, OutDistance));
	}

	bool FLibrary::GetSafeNormal2DAtoB(const FString& Context, const AActor* A, const AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance, LogLevel)
	{
		CS_IS_PTR_NULL_RET_VALUE(A, 0.0f)
		CS_IS_PTR_NULL_RET_VALUE(B, 0.0f)

		const FVector3d VA = A->GetActorLocation();
		const FVector3d VB = B->GetActorLocation();
		const FVector3d V  = VB - VA;
		
		OutNormal = MathLibrary::Convert(MathLibrary::GetSafeNormal2D(V, OutDistanceSq, OutDistance));
		
		return V != FVector3d::ZeroVector && OutNormal != FVector3f::ZeroVector;
	}

	void FLibrary::GetNormal2DAtoBChecked(const FString& Context, const AActor* A, const FVector3f& B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance)
	{
		CS_IS_PTR_NULL_CHECKED(A)

		const FVector3f VA = GetLocationChecked(Context, A);
		const FVector3f V  = B - VA;

		OutNormal = MathLibrary::GetSafeNormal2D(V, OutDistanceSq, OutDistance);
	}

	bool FLibrary::GetSafeNormal2DAtoB(const FString& Context, const AActor* A, const FVector3f& B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance, LogLevel)
	{
		CS_IS_PTR_NULL_RET_VALUE(A, 0.0f)

		const FVector3f VA = GetLocationChecked(Context, A);
		const FVector3f V  = B - VA;

		OutNormal = MathLibrary::GetSafeNormal2D(V, OutDistanceSq, OutDistance);

		return V != FVector3f::ZeroVector && OutNormal != FVector3f::ZeroVector;
	}

	#pragma endregion Normal

	// Tag
	#pragma region
	
	void FLibrary::ClearTagsChecked(const FString& Context, AActor* A, const bool& bClearComponentTags /*=true*/)
	{
		CS_IS_PENDING_KILL_CHECKED(A);

		if (bClearComponentTags)
		{
			const TSet<UActorComponent*>& Components = A->GetComponents();

			for (UActorComponent* Component : Components)
			{
				Component->ComponentTags.Reset(Component->ComponentTags.Max());
			}
		}
		A->Tags.Reset(A->Tags.Max());
	}

	#pragma endregion Tag

	// Tick
	#pragma region
	
	void FLibrary::SetTickEnabledChecked(const FString& Context, AActor* A, const bool& bEnabled, const bool& bComponentsEnabled /*=true*/)
	{
		CS_IS_PENDING_KILL_CHECKED(A)

		if (bComponentsEnabled)
		{
			const TSet<UActorComponent*>& Components = A->GetComponents();

			for (UActorComponent* Component : Components)
			{
				Component->SetComponentTickEnabled(bEnabled);
			}
		}
		A->SetActorTickEnabled(bEnabled);
	}

	#pragma endregion Tick

	#undef LogLevel
	#undef WorldLibrary
	#undef MathLibrary
	#undef NameLibrary
}