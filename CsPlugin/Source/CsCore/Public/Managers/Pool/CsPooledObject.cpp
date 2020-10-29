// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObject.h"
#include "CsCore.h"

#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsOnConstructObject.h"

UCsPooledObject::UCsPooledObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsPooledObject
#pragma region

const FCsPooledObject FCsPooledObject::Empty;

FCsPooledObject::FCsPooledObject() :
	Super(),
	_Update(nullptr),
	bScriptUpdate(false),
	_OnConstructObject(nullptr),
	bScriptOnConstructObject(false),
	Script_GetCache_Impl(),
	Script_Allocate_Impl(),
	Script_Deallocate_Impl(),
	Script_Update_Impl(),
	Script_OnConstructObject_Impl()
{
}

// TCsInterfaceObject
#pragma region

void FCsPooledObject::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
#if UE_BUILD_SHIPPING
		SetUpdate((ICsUpdate*)InInterface);
#else
		SetUpdate(dynamic_cast<ICsUpdate*>(InInterface));
#endif // #if UE_BUILD_SHIPPING
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
	}
}

void FCsPooledObject::Reset()
{
	Super::Reset();

	_Update = nullptr;
	bScriptUpdate = false;
	_OnConstructObject = nullptr;
	bScriptOnConstructObject = false;

	Script_GetCache_Impl.Unbind();
	Script_Allocate_Impl.Unbind();
	Script_Deallocate_Impl.Unbind();
	Script_Update_Impl.Unbind();
	Script_OnConstructObject_Impl.Unbind();
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

#pragma endregion FCsPooledObject