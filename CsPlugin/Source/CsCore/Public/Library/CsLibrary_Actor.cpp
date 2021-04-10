// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Actor.h"

// Types
#include "Types/CsTypes_Macro.h"
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
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeActorByName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeActorByLabel);
			}
		}
	}

	AActor* FLibrary::GetActorWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		checkf(Tag != NAME_None, TEXT("%s: Tag: None is NOT Valid."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
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
			if (!A || A->IsPendingKill())
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
	
	AActor* FLibrary::GetSafeActorByName(const FString& Context, UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Ctxt = Context.IsEmpty() ? Str::GetSafeActorByName : Context;

		if (!WorldContext)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: WorldContext is NULL."), *Ctxt));
			return nullptr;
		}

		if (Name == NAME_None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Ctxt));
			return nullptr;
		}

		UWorld* World = WorldContext->GetWorld();

		if (!World)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get World from WorldContext: %s."), *Ctxt, *(WorldContext->GetName())));
			return nullptr;
		}

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Name: %s."), *Ctxt, *(Name.ToString())));
		return nullptr;
	}

	AActor* FLibrary::GetSafeActorByName(UObject* WorldContext, const FName& Name)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeActorByName;

		return GetSafeActorByName(Context, WorldContext, Name, nullptr);
	}

	AActor* FLibrary::GetSafeActorByLabel(const FString& Context, UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Ctxt = Context.IsEmpty() ? Str::GetSafeActorByLabel : Context;

	#if WITH_EDITOR
		if (!WorldContext)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: WorldContext is NULL."), *Ctxt));
			return nullptr;
		}

		if (Label.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Label is EMPTY."), *Ctxt));
			return nullptr;
		}

		UWorld* World = WorldContext->GetWorld();

		if (!World)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get World from WorldContext: %s."), *Ctxt, *(WorldContext->GetName())));
			return nullptr;
		}

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Actor with Label: %s."), *Ctxt, *Label));
		return nullptr;
#else
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Ctxt));
		return nullptr;
#endif // #if !WITH_EDITOR
	}

	AActor* FLibrary::GetSafeActorByLabel(UObject* WorldContext, const FString& Label)
	{
		using namespace NCsActor::NLibrary::NCached;

		const FString& Context = Str::GetSafeActorByLabel;

		return GetSafeActorByLabel(Context, WorldContext, Label, nullptr);
	}
}