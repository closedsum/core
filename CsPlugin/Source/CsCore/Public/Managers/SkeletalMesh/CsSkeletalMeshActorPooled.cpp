// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/SkeletalMesh/CsSkeletalMeshActorPooled.h"
#include "CsCore.h"

#include "Managers/SkeletalMesh/CsSkeletalMeshActor.h"

const FCsSkeletalMeshActorPooled FCsSkeletalMeshActorPooled::Empty;

FCsSkeletalMeshActorPooled::FCsSkeletalMeshActorPooled() :
	Super(),
	SkeletalMeshActor(nullptr),
	bScriptSkeletalMeshActor(false),
	Script_GetMeshComponent_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsSkeletalMeshActorPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT("FCsSkeletalMeshActorPooled::SetInterface: This not support Non UObject objects."));
	}
}

void FCsSkeletalMeshActorPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsSkeletalMeshActor
		{
			// Interface
			if (ICsSkeletalMeshActor* O = Cast<ICsSkeletalMeshActor>(Object))
			{
				SetSkeletalMeshActorPooled(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsSkeletalMeshActor::StaticClass()))
			{
				SetScriptSkeletalMeshActor();
			}
			else
			{
				checkf(false, TEXT("FCsSkeletalMeshActorPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsSkeletalMeshActor."), *(Object->GetName()), *(Class->GetName()));
			}
		}
	}
}

void FCsSkeletalMeshActorPooled::Reset()
{
	Super::Reset();

	SkeletalMeshActor = nullptr;
	bScriptSkeletalMeshActor = false;

	Script_GetMeshComponent_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsSkeletalMeshActor
#pragma region

USkeletalMeshComponent* FCsSkeletalMeshActorPooled::GetMeshComponent() const
{
	if (bScriptSkeletalMeshActor)
		return Script_GetMeshComponent_Impl.Execute(Object);
	return SkeletalMeshActor->GetMeshComponent();
}

#pragma endregion ICsSkeletalMeshActor

void FCsSkeletalMeshActorPooled::SetPooledObject(const FCsPooledObject& PooledObject)
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
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsSkeletalMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsSkeletalMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsSkeletalMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsSkeletalMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}