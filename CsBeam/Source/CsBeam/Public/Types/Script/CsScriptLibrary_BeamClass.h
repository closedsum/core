// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Beam.h"

#include "CsScriptLibrary_BeamClass.generated.h"

UCLASS()
class CSBEAM_API UCsScriptLibrary_BeamClass : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Name"))
	static FECsBeamClass Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Index"))
	static FECsBeamClass GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsBeamClass& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam")
	static void GetAll(TArray<FECsBeamClass>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Beam", meta = (AutoCreateRefTerm = "Name"))
	static FECsBeamClass GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (BeamClass)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Beam")
	static bool EqualEqual(const FECsBeamClass& A, const FECsBeamClass& B);

#pragma endregion Enum
};