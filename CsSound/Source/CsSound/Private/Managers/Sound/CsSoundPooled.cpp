// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/CsSoundPooled.h"
#include "CsSound.h"

UCsSoundPooled::UCsSoundPooled(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsSoundPooled::Name = FName("ICsSoundPooled");

const FCsSoundPooled FCsSoundPooled::Empty;

FCsSoundPooled::FCsSoundPooled() :
	Super(),
	Sound(nullptr),
	bScriptSound(false),
	Script_GetAudioComponent_Impl(),
	Script_Stop_Impl(),
	Script_FadeIn_Impl(),
	Script_FadeOut_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsSoundPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetSoundPooled((ICsSoundPooled*)InInterface);
#else
		SetSoundPooled(dynamic_cast<ICsSoundPooled*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsSoundPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsSoundPooled
		{
			// Interface
			if (ICsSoundPooled* O = Cast<ICsSoundPooled>(Object))
			{
				SetSoundPooled(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsSoundPooled::StaticClass()))
			{
				SetScriptSound();
			}
			else
			{
				checkf(false, TEXT("FCsSoundPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsSoundPooled."), *(Object->GetName()), *(Class->GetName()));
			}
		}
	}
}

void FCsSoundPooled::Reset()
{
	Super::Reset();

	Sound = nullptr;
	bScriptSound = false;

	Script_GetAudioComponent_Impl.Unbind();
	Script_Stop_Impl.Unbind();
	Script_FadeIn_Impl.Unbind();
	Script_FadeOut_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

void FCsSoundPooled::SetPooledObject(const FCsPooledObject& PooledObject)
{
	SetInterface(PooledObject.GetInterface());
	SetObject(PooledObject.GetObject());

	if (PooledObject.IsScript())
		SetScript();

	Script_GetCache_Impl = PooledObject.Script_GetCache_Impl;
	Script_Allocate_Impl = PooledObject.Script_Allocate_Impl;
	Script_Update_Impl = PooledObject.Script_Update_Impl;
	Script_Deallocate_Impl = PooledObject.Script_Deallocate_Impl;

	if (bScript)
	{
		// GetCache
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsSoundPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsSoundPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsSoundPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsSoundPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}