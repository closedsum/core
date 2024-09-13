// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/CsBeamWeapon.h"

// Weapon
#include "CsWeapon.h"
// Update
#include "Managers/Time/CsUpdate.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsBeamWeapon)

UCsBeamWeapon::UCsBeamWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsBeamWeapon
#pragma region

const FCsBeamWeapon FCsBeamWeapon::Empty;

// TCsInterfaceObject
#pragma region

void FCsBeamWeapon::SetInterface(ICsBeamWeapon* InInterface)
{
	Super::SetInterface(InInterface);

	if (!Object)
	{
		checkf(0, TEXT("FCsBeamWeapon::SetInterface: Currently do NOT support a non-UObject based weapon implmenting the interface: ICsBeamWeapon."));
	}
}

void FCsBeamWeapon::SetObject(UObject* InObject)
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
				checkf(false, TEXT("FCsBeamWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()), *(Object->GetClass()->GetName()));
			}
		}
		// ICsBeamWeapon
		{
			// Interface
			if (ICsBeamWeapon* O = Cast<ICsBeamWeapon>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsBeamWeapon::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsBeamWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsBeamWeapon."), *(Object->GetName()), *(Object->GetClass()->GetName()));
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

void FCsBeamWeapon::Reset()
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

void FCsBeamWeapon::Update(const FCsDeltaTime& DeltaTime)
{
	if (bScriptUpdate)
		Script_Update_Impl.Execute(Object, DeltaTime);
	else
		_Update->Update(DeltaTime);
}

#pragma endregion ICsUpdate

#pragma endregion FCsProjectileWeapon