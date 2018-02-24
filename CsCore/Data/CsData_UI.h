// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_UI.h"
#include "CsData_UI.generated.h"

/* Current Order of Categories

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_UI : public ACsData
{
	GENERATED_UCLASS_BODY()

// Widgets
#pragma region

	virtual class UBlueprintGeneratedClass* GetWidget(const TCsWidgetType& WidgetType);

#pragma endregion Widgets
};