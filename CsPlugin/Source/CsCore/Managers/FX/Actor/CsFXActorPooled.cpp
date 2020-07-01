// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsFXActorPooled.h"
#include "CsCore.h"

UCsFXActorPooled::UCsFXActorPooled(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsFXActorPooled FCsFXActorPooled::Empty;

FCsFXActorPooled::FCsFXActorPooled() :
	Super(),
	FXActor(nullptr),
	bScriptFXActor(false),
	Script_GetFX_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsFXActorPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetFXActorPooled((ICsFXActorPooled*)InInterface);
#else
		SetFXActorPooled(dynamic_cast<ICsFXActorPooled*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsFXActorPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		UClass* Class = Object->GetClass();

		// ICsFXActorPooled
		{
			// Interface
			if (ICsFXActorPooled* O = Cast<ICsFXActorPooled>(Object))
			{
				SetFXActorPooled(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsFXActorPooled::StaticClass()))
			{
				SetScriptFXActor();
			}
			else
			{
				checkf(false, TEXT("FCsFXActorPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsFXActorPooled."), *(Object->GetName()), *(Class->GetName()));
			}
		}

		checkf(Implements_ICsOnConstructObject(), TEXT("FCsFXActorPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsOnConstructObject."), *(Object->GetName()), *(Class->GetName()));
	}
}

void FCsFXActorPooled::Reset()
{
	Super::Reset();

	FXActor = nullptr;
	bScriptFXActor = false;

	Script_GetFX_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsFXActorPooled
#pragma region

ANiagaraActor* FCsFXActorPooled::GetFX() const
{
	if (bScriptFXActor)
		return Script_GetFX_Impl.Execute(Object);
	return FXActor->GetFX();
}

#pragma endregion ICsProjectile

void FCsFXActorPooled::SetPooledObject(const FCsPooledObject& PooledObject)
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
		UClass* Class = Object->GetClass();

		// GetCache
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsFXActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsFXActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsFXActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsFXActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}