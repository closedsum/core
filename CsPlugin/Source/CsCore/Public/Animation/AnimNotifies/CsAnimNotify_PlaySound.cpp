// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/AnimNotifies/CsAnimNotify_PlaySound.h"
#include "CsCore.h"

// Library
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
	// Common
#include "Library/CsLibrary_Math.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Components
#include "Components/SkeletalMeshComponent.h"
// Sound
#include "Sound/SoundBase.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#include "Kismet/GameplayStatics.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsAnimNotifyPlaySound
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsAnimNotify_PlaySound, GetNotifyName_Implementation);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsAnimNotify_PlaySound, Notify);
		}
	}
}

#pragma endregion Cached

UCsAnimNotify_PlaySound::UCsAnimNotify_PlaySound() : 
	Super(),
	Sound()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

FString UCsAnimNotify_PlaySound::GetNotifyName_Implementation() const
{
	using namespace NCsAnimNotifyPlaySound::NCached;

	const FString& Context = Str::GetNotifyName_Implementation;

	if (USoundBase* S = Sound.SafeLoad(Context))
	{
		return S->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

void UCsAnimNotify_PlaySound::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	using namespace NCsAnimNotifyPlaySound::NCached;

	const FString& Context = Str::Notify;

	typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
	typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadImplType;

#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	UWorld* CurrentWorld = MeshComp->GetWorld();

	if (WorldLibrary::IsPlayInGame(CurrentWorld) ||
		WorldLibrary::IsPlayInPIE(CurrentWorld))
	{
		PooledPayloadImplType PooledPayload;
		PooledPayload.Instigator = MeshComp;
		PooledPayload.Owner		 = MeshComp->GetOwner() ? Cast<UObject>(MeshComp->GetOwner()) : Cast<UObject>(MeshComp->GetAttachParent());
		PooledPayload.Parent	 = MeshComp;

		SoundManagerLibrary::SpawnChecked(Context, MeshComp, &PooledPayload, Sound);
	}
	else
	{
		if (USoundBase* S = Sound.SafeLoad(Context))
		{
			if (Sound.Bone != NAME_None)
			{
				typedef NCsMath::FLibrary MathLibrary;

				UGameplayStatics::SpawnSoundAttached(S, MeshComp, Sound.Bone, MathLibrary::Convert(Sound.Transform.GetLocation()), EAttachLocation::KeepRelativeOffset, false, 1.0f, 1.0f);
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(CurrentWorld,S, MeshComp->GetComponentLocation(), 1.0f, 1.0f);
			}
		}
	}
#else
	PooledPayloadImplType PooledPayload;
	PooledPayload.Instigator = MeshComp;
	PooledPayload.Owner		 = MeshComp->GetOwner() ? Cast<UObject>(MeshComp->GetOwner()) : Cast<UObject>(MeshComp->GetAttachParent());
	PooledPayload.Parent	 = MeshComp;

	SoundManagerLibrary::SpawnChecked(Context, MeshComp, &PooledPayload, Sound);
#endif // #if WITH_EDITOR

}