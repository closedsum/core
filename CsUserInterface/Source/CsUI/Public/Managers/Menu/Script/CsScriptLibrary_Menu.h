// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Menu/CsTypes_Menu.h"

#include "CsScriptLibrary_Menu.generated.h"


UCLASS()
class CSUI_API UCsScriptLibrary_Menu : public UObject
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

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Menu)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Menu")
	static bool EqualEqual(const FECsMenu& A, const FECsMenu& B);

#pragma endregion Menu
};