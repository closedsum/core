// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/CsTdCreep.h"
#include "CsTd.h"

UCsTdCreep::UCsTdCreep(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FCsTdCreep FCsTdCreep::Empty;

// FCsTdCreepPooled
#pragma region

const FCsTdCreepPooled FCsTdCreepPooled::Empty;

// TCsInterfaceObject
#pragma region

void FCsTdCreepPooled::SetInterface(ICsPooledObject* InInterface)
{
	Super::SetInterface(InInterface);
}

void FCsTdCreepPooled::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		UClass* Class = Object->GetClass();

		// ICsTdCreep
		{
			// Interface
			if (ICsTdCreep* O = Cast<ICsTdCreep>(Object))
			{
				SetCreep(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
			{
				SetScriptCreep();
			}
			else
			{
				checkf(false, TEXT("FCsTdCreepPooled:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsTdCreep."), *(Object->GetName()));
			}
		}
	}
}
	
#pragma endregion TCsInterfaceObject

#pragma endregion FCsTdCreepPooled