// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsUserWidgetPooled.h"
#include "CsUI.h"

UCsUserWidgetPooled::UCsUserWidgetPooled(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsUserWidgetPooled FCsUserWidgetPooled::Empty;

FCsUserWidgetPooled::FCsUserWidgetPooled() :
	Super(),
	UserWidgetPooled(nullptr),
	bScriptUserWidgetPooled(false),
	Script_GetUserWidget_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsUserWidgetPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT(": Non-UObject implementing the interface: ICsUserWidgetPooled not Supported."))
	}
}

void FCsUserWidgetPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsUserWidgetPooled
		{
			// Interface
			if (ICsUserWidgetPooled* O = Cast<ICsUserWidgetPooled>(Object))
			{
				SetUserWidgetPooled(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsUserWidgetPooled::StaticClass()))
			{
				SetScriptUserWidgetPooled();
			}
			else
			{
				checkf(false, TEXT("FCsUserWidgetPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsUserWidgetPooled."), *(Object->GetName()), *(Class->GetName()));
			}
		}

		checkf(Implements_ICsOnConstructObject(), TEXT("FCsUserWidgetPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsOnConstructObject."), *(Object->GetName()), *(Class->GetName()));
	}
}

void FCsUserWidgetPooled::Reset()
{
	Super::Reset();

	UserWidgetPooled = nullptr;
	bScriptUserWidgetPooled = false;

	Script_GetUserWidget_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsUserWidgetPooled
#pragma region

UUserWidget* FCsUserWidgetPooled::GetUserWidget() const
{
	if (bScriptUserWidgetPooled)
		return Script_GetUserWidget_Impl.Execute(Object);
	return UserWidgetPooled->GetUserWidget();
}

#pragma endregion ICsUserWidgetPooled

void FCsUserWidgetPooled::SetPooledObject(const FCsPooledObject& PooledObject)
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
		checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsUserWidgetPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Allocate
		checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsUserWidgetPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Update
		checkf(Script_Update_Impl.IsBound(), TEXT("FCsUserWidgetPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		// Deallocate
		checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsUserWidgetPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
	}
}