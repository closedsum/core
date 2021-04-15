// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#include "CsScriptLibrary_SkeletalMeshActor.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_SkeletalMeshActor : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - Get", AutoCreateRefTerm = "Name"))
	static FECsSkeletalMeshActor ECsSkeletalMeshActor_Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - Get by Index", AutoCreateRefTerm = "Index"))
	static FECsSkeletalMeshActor ECsSkeletalMeshActor_GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - To String", AutoCreateRefTerm = "Enum"))
	static FString ECsSkeletalMeshActor_ToString(const FECsSkeletalMeshActor& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - Get Count"))
	static uint8 ECsSkeletalMeshActor_GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (DisplayName = "ECsECsSkeletalMeshActorFX - Get All"))
	static void ECsSkeletalMeshActor_GetAll(TArray<FECsSkeletalMeshActor>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|StaticMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - Get Max", AutoCreateRefTerm = "Name"))
	static FECsSkeletalMeshActor ECsSkeletalMeshActor_GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (StaticMeshActor)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|FX")
	static bool EqualEqual_SkeletalMeshActorSkeletalMeshActor(const FECsSkeletalMeshActor& A, const FECsSkeletalMeshActor& B);

#pragma endregion Enum
};