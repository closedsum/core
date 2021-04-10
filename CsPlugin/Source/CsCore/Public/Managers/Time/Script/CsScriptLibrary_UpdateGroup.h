// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

// Managers
#include "Managers/Time/CsTypes_Update.h"

#include "CsScriptLibrary_UpdateGroup.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_UpdateGroup : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (DisplayName = "ECsUpdateGroup - Get", AutoCreateRefTerm = "Name"))
	static FECsUpdateGroup ECsUpdateGroup_Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (DisplayName = "ECsUpdateGroup - Get by Index", AutoCreateRefTerm = "Index"))
	static FECsUpdateGroup ECsUpdateGroup_GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (DisplayName = "ECsUpdateGroup - To String", AutoCreateRefTerm = "Enum"))
	static FString ECsUpdateGroup_ToString(const FECsUpdateGroup& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (DisplayName = "ECsUpdateGroup - Get Count"))
	static uint8 ECsUpdateGroup_GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (DisplayName = "ECsUpdateGroup - Get All"))
	static void ECsUpdateGroup_GetAll(TArray<FECsUpdateGroup>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|UpdateGroup", meta = (DisplayName = "ECsUpdateGroup - Get Max", AutoCreateRefTerm = "Name"))
	static FECsUpdateGroup ECsUpdateGroup_GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UpdateGroup)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|UpdateGroup")
	static bool EqualEqual_UpdateGroupUpdateGroup(const FECsUpdateGroup& A, const FECsUpdateGroup& B);
};