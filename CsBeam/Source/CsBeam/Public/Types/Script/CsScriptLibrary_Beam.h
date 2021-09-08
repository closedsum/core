// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Beam.h"

#include "CsScriptLibrary_Beam.generated.h"

UCLASS()
class CSBEAM_API UCsScriptLibrary_Beam : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Name,DisplayName"))
	static FECsBeam Create(const FString& Name, const FString& DisplayName);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Name"))
	static FECsBeam Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Index"))
	static FECsBeam GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsBeam& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam")
	static void GetAll(TArray<FECsBeam>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Name"))
	static FECsBeam GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Beam)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Beam")
	static bool EqualEqual(const FECsBeam& A, const FECsBeam& B);

#pragma endregion Enum
};