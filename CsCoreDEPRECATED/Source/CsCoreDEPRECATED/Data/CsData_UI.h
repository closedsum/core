// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "UI/CsTypes_UI.h"
#include "CsData_UI.generated.h"

/* Current Order of Categories

*/

UCLASS(Abstract)
class CSCOREDEPRECATED_API UCsData_UI : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

// Widgets
#pragma region

	virtual class UBlueprintGeneratedClass* GetWidget(const FECsWidgetType& WidgetType);

#pragma endregion Widgets
};