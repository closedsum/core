// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObject.h"
#include "CsCore.h"

// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsPause.h"

UCsPooledObject::UCsPooledObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsPooledObject
#pragma region

const FCsPooledObject FCsPooledObject::Empty;

FCsPooledObject::FCsPooledObject() :
	Super(),
	// ICsUpdate
	_Update(nullptr),
	bScriptUpdate(false),
	// ICsOnContructObject
	_OnConstructObject(nullptr),
	bScriptOnConstructObject(false),
	// ICsPause
	_Pause(nullptr),
	bScriptPause(false),
	// Script
		// ICsPooledObject
	Script_GetCache_Impl(),
	Script_Allocate_Impl(),
	Script_Deallocate_Impl(),
		// ICsUpdate
	Script_Update_Impl(),
		// ICsOnConstructObject
	Script_OnConstructObject_Impl(),
		// ICsPause
	Script_Pause_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsPooledObject::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT("FCsPooledObject::SetInterface: This is NOT supported. InInterface must be a UObject."))
	}
}

void FCsPooledObject::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsPooledObject
		{
			// Interface
			if (ICsPooledObject* O = Cast<ICsPooledObject>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsPooledObject:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsPooledObject."), *(Object->GetName()), *(Object->GetClass()->GetName()));
			}
		}
		// ICsUpdate
		{
			// Interface
			if (ICsUpdate* U = Cast<ICsUpdate>(Object))
			{
				SetUpdate(U);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsUpdate::StaticClass()))
			{
				SetScriptUpdate();
			}
		}
		// ICsOnConstructObject
		{
			// Interface
			if (ICsOnConstructObject* O = Cast<ICsOnConstructObject>(Object))
			{
				SetOnConstructObject(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsOnConstructObject::StaticClass()))
			{
				SetScriptOnConstructObject();
			}
		}
		// ICsPause
		{
			// Interface
			if (ICsPause* U = Cast<ICsPause>(Object))
			{
				SetPause(U);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsPause::StaticClass()))
			{
				SetScriptPause();
			}
		}
	}
}

void FCsPooledObject::Reset()
{
	Super::Reset();

	_Update = nullptr;
	bScriptUpdate = false;
	_OnConstructObject = nullptr;
	bScriptOnConstructObject = false;
	_Pause = nullptr;
	bScriptPause = false;

	Script_GetCache_Impl.Unbind();
	Script_Allocate_Impl.Unbind();
	Script_Deallocate_Impl.Unbind();
	Script_Update_Impl.Unbind();
	Script_OnConstructObject_Impl.Unbind();
	Script_Pause_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsUpdate
#pragma region

void FCsPooledObject::Update(const FCsDeltaTime& DeltaTime)
{
	if (bScriptUpdate)
		Script_Update_Impl.Execute(Object, DeltaTime);
	else
		_Update->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsOnConstructObject
#pragma region

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
void FCsPooledObject::OnConstructObject(const ConstructParamsType& Params)
{
#undef ConstructParamsType

	if (bScriptOnConstructObject)
		Script_OnConstructObject_Impl.Execute(Object, Params);
	else
		_OnConstructObject->OnConstructObject(Params);
}

#pragma endregion ICsOnConstructObject

// ICsPause
#pragma region

void FCsPooledObject::Pause(bool bPaused)
{
	if (bScriptPause)
		Script_Pause_Impl.Execute(Object, bPaused);
	else
		_Pause->Pause(bPaused);
}

#pragma endregion ICsPause

#pragma endregion FCsPooledObject