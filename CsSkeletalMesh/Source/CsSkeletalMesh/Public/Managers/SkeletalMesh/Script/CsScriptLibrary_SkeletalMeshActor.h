// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#include "CsScriptLibrary_SkeletalMeshActor.generated.h"

UCLASS()
class CSSKELETALMESH_API UCsScriptLibrary_SkeletalMeshActor : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMeshActor", meta = (AutoCreateRefTerm = "Name"))
	static FECsSkeletalMeshActor Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMeshActor", meta = (AutoCreateRefTerm = "Index"))
	static FECsSkeletalMeshActor GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMeshActor", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsSkeletalMeshActor& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMeshActor")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMeshActor")
	static void GetAll(TArray<FECsSkeletalMeshActor>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMeshActor", meta = (AutoCreateRefTerm = "Name"))
	static FECsSkeletalMeshActor GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (SkeletalMeshActor)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|SkeletalMeshActor")
	static bool EqualEqual(const FECsSkeletalMeshActor& A, const FECsSkeletalMeshActor& B);

#pragma endregion Enum
};