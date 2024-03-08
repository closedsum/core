// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_UI.h"

#include "CsScriptLibrary_UI_Types.generated.h"

class UClass;

UCLASS()
class CSUI_API UCsScriptLibrary_UI_Types : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Types", meta = (DisplayName = "Get Class (UUserWidget)", Keywords = "get class", AutoCreateRefTerm = "Context"))
	static UClass* FCsUserWidget_GetClass(const FString& Context, const FCsUserWidget& A);

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Types", meta = (DisplayName = "Get Class (UUserWidget | Checked)", Keywords = "get class", AutoCreateRefTerm = "Context"))
	static UClass* FCsUserWidget_GetClassChecked(const FString& Context, const FCsUserWidget& A, bool& OutSuccess);
};