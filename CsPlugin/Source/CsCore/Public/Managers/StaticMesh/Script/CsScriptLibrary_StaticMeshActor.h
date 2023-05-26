// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsScriptLibrary_StaticMeshActor.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_StaticMeshActor : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (AutoCreateRefTerm = "Name"))
	static FECsStaticMeshActor Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (AutoCreateRefTerm = "Index"))
	static FECsStaticMeshActor GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsStaticMeshActor& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor")
	static void GetAll(TArray<FECsStaticMeshActor>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (AutoCreateRefTerm = "Name"))
	static FECsStaticMeshActor GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (StaticMeshActor)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|StaticMeshActor")
	static bool EqualEqual(const FECsStaticMeshActor& A, const FECsStaticMeshActor& B);

#pragma endregion Enum
};