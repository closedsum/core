// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsWeapon.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsWeapon)

UCsWeapon::UCsWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// FCsWeapon
#pragma region

const FCsWeapon FCsWeapon::Empty;

	// TCsInterfaceObject
#pragma region

void FCsWeapon::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsWeapon
		{
			// Interface
			if (ICsWeapon* O = Cast<ICsWeapon>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsWeapon::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsWeapon:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsWeapon."), *(Object->GetName()), *(Object->GetClass()->GetName()));
			}
		}
	}
}

#pragma endregion TCsInterfaceObject

using DataType = NCsWeapon::NData::IData;

	// ICsWeapon
#pragma region

DataType* FCsWeapon::GetData()
{
	if (bScript)
		return Script_GetData_Impl.Execute(Object);
	return Interface->GetData();
}

const FECsWeaponState& FCsWeapon::GetCurrentState()
{
	if (bScript)
		return Script_GetCurrentState_Impl.Execute(Object);
	return Interface->GetCurrentState();
}

#pragma endregion ICsWeapon

#pragma endregion FCsWeapon