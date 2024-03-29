// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Menu/CsTypes_Menu.h"

#include "CsScriptLibrary_Menu.generated.h"


UCLASS()
class CSMENU_API UCsScriptLibrary_Menu : public UObject
{
	GENERATED_UCLASS_BODY()

// Menu
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu", meta = (AutoCreateRefTerm = "Name,DisplayName"))
	static FECsMenu Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu", meta = (AutoCreateRefTerm = "Name"))
	static FECsMenu Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu", meta = (AutoCreateRefTerm = "Index"))
	static FECsMenu GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsMenu& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu")
	static void GetAll(TArray<FECsMenu>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Menu", meta = (AutoCreateRefTerm = "Name"))
	static FECsMenu GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (ECsMenu)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Menu")
	static bool EqualEqual(const FECsMenu& A, const FECsMenu& B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (ECsMenu)", CompactNodeTitle = "!=", ScriptMethod = "NotEquals", Keywords = "!= notequal"), Category = "CsCore|Library|Menu")
	static bool NotEqual(const FECsMenu& A, const FECsMenu& B);

#pragma endregion Menu
};