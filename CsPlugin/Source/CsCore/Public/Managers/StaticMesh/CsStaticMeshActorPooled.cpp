// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsStaticMeshActorPooled.h"
#include "CsCore.h"

#include "Managers/StaticMesh/CsStaticMeshActor.h"

const FCsStaticMeshActorPooled FCsStaticMeshActorPooled::Empty;

FCsStaticMeshActorPooled::FCsStaticMeshActorPooled() :
	Super(),
	StaticMeshActor(nullptr),
	bScriptStaticMeshActor(false),
	Script_GetMeshComponent_Impl(),
	Script_GetMIDs_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsStaticMeshActorPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT("FCsStaticMeshActorPooled::SetInterface: This not support Non UObject objects."));
	}
}

void FCsStaticMeshActorPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsStaticMeshActor
		{
			// Interface
			if (ICsStaticMeshActor* O = Cast<ICsStaticMeshActor>(Object))
			{
				SetStaticMeshActorPooled(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsStaticMeshActor::StaticClass()))
			{
				SetScriptStaticMeshActor();
			}
			else
			{
				checkf(false, TEXT("FCsStaticMeshActorPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsStaticMeshActor."), *(Object->GetName()), *(Class->GetName()));
			}
		}
	}
}

void FCsStaticMeshActorPooled::Reset()
{
	Super::Reset();

	StaticMeshActor = nullptr;
	bScriptStaticMeshActor = false;

	Script_GetMeshComponent_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsStaticMeshActor
#pragma region

UStaticMeshComponent* FCsStaticMeshActorPooled::GetMeshComponent() const
{
	if (bScriptStaticMeshActor)
		return Script_GetMeshComponent_Impl.Execute(Object);
	return StaticMeshActor->GetMeshComponent();
}

const TArray<UMaterialInstanceDynamic*>& FCsStaticMeshActorPooled::GetMIDs() const
{
	if (bScriptStaticMeshActor)
		return Script_GetMIDs_Impl.Execute(Object);
	return StaticMeshActor->GetMIDs();
}

#pragma endregion ICsStaticMeshActor

void FCsStaticMeshActorPooled::SetPooledObject(const FCsPooledObject& PooledObject)
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
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsStaticMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsStaticMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsStaticMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsStaticMeshActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}