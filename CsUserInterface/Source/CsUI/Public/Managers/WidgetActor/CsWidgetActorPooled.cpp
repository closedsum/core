// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsWidgetActorPooled.h"
#include "CsCore.h"

// Widget
#include "Managers/WidgetActor/CsWidgetActor.h"

const FCsWidgetActorPooled FCsWidgetActorPooled::Empty;

FCsWidgetActorPooled::FCsWidgetActorPooled() :
	Super(),
	WidgetActor(nullptr),
	bScriptWidgetActor(false),
	Script_GetWidgetComponent_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsWidgetActorPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetWidgetActor((ICsWidgetActor*)InInterface);
#else
		SetWidgetActor(dynamic_cast<ICsWidgetActor*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
	}
}

void FCsWidgetActorPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsFXActorPooled
		{
			// Interface
			if (ICsWidgetActor* O = Cast<ICsWidgetActor>(Object))
			{
				SetWidgetActor(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsWidgetActor::StaticClass()))
			{
				SetScriptWidgetActor();
			}
			else
			{
				checkf(false, TEXT("FCsWidgetActorPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWidgetActor."), *(Object->GetName()), *(Class->GetName()));
			}
		}
	}
}

void FCsWidgetActorPooled::Reset()
{
	Super::Reset();

	WidgetActor = nullptr;
	bScriptWidgetActor = false;

	Script_GetWidgetComponent_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsWidgetActor
#pragma region

UCsWidgetComponent* FCsWidgetActorPooled::GetWidgetComponent() const
{
	if (bScriptWidgetActor)
		return Script_GetWidgetComponent_Impl.Execute(Object);
	return WidgetActor->GetWidgetComponent();
}

#pragma endregion ICsWidgetActor

void FCsWidgetActorPooled::SetPooledObject(const FCsPooledObject& PooledObject)
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
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsWidgetActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsWidgetActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsWidgetActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsWidgetActorPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}