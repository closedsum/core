// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/CsTraceWeapon.h"
#include "CsWp.h"

// Weapon
#include "CsWeapon.h"
// Update
#include "Managers/Time/CsUpdate.h"

UCsTraceWeapon::UCsTraceWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsTraceWeapon
#pragma region

const FCsTraceWeapon FCsTraceWeapon::Empty;

// TCsInterfaceObject
#pragma region

void FCsTraceWeapon::SetInterface(ICsTraceWeapon* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT("FCsTraceWeapon::SetInterface: Currently do NOT support a non-UObject based weapon implmenting the interface: ICsTraceWeapon."));
	}
}

void FCsTraceWeapon::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsWeapon
		{
			// Interface
			if (ICsWeapon* O = Cast<ICsWeapon>(Object))
			{
				SetWeapon(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsWeapon::StaticClass()))
			{
				SetScriptWeapon();
			}
			else
			{
				checkf(false, TEXT("FCsProjectileWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()));
			}
		}
		// ICsTraceWeapon
		{
			// Interface
			if (ICsTraceWeapon* O = Cast<ICsTraceWeapon>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsTraceWeapon::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsProjectileWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsProjectileWeapon."), *(Object->GetName()));
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
	}
}

void FCsTraceWeapon::Reset()
{
	Super::Reset();

	Weapon = nullptr;
	bScriptWeapon = false;

	_Update = nullptr;
	bScriptUpdate = false;

	Script_GetData_Impl.Unbind();
	Script_StartFire_Impl.Unbind();
	Script_StopFire_Impl.Unbind();
	Script_Update_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsUpdate
#pragma region

void FCsTraceWeapon::Update(const FCsDeltaTime& DeltaTime)
{
	if (bScriptUpdate)
		Script_Update_Impl.Execute(Object, DeltaTime);
	else
		_Update->Update(DeltaTime);
}

#pragma endregion ICsUpdate

#pragma endregion FCsProjectileWeapon