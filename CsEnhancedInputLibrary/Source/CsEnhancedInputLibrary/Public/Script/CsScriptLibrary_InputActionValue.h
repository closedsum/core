// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Namespace.h"
// Input
#include "InputActionValue.h"

#include "CsScriptLibrary_InputActionValue.generated.h"

// NCsInput::NEnhanced::NInputActionValue::FLibrary
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsInput, NEnhanced, NInputActionValue, FLibrary)

UCLASS()
class CSENHANCEDINPUTLIBRARY_API UCsScriptLibrary_InputActionValue : public UObject
{ 
	GENERATED_UCLASS_BODY() 

private:

	typedef NCsInput::NEnhanced::NInputActionValue::FLibrary NativeLibrary;

	static void(*LogError)(const FString&);

public:

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (AutoCreateRefTerm = "Value"))
	static bool GetBool(const FString& Context, const FInputActionValue& Value);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Get Bool (Checked)", AutoCreateRefTerm = "Value"))
	static bool GetBoolChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (AutoCreateRefTerm = "Value"))
	static float GetFloat(const FString& Context, const FInputActionValue& Value);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Get Float (Checked)", AutoCreateRefTerm = "Value"))
	static float GetFloatChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (AutoCreateRefTerm = "Value"))
	static FVector2D GetVector2D(const FString& Context, const FInputActionValue& Value);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Get Vector2D (Checked)", AutoCreateRefTerm = "Value"))
	static FVector2D GetVector2DChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (AutoCreateRefTerm = "Value"))
	static FVector GetVector(const FString& Context, const FInputActionValue& Value);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Get Vector (Checked)", AutoCreateRefTerm = "Value"))
	static FVector GetVectorChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess);

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "To Bool (InputActionValue)", CompactNodeTitle = "->", ScriptMethod = "InputActionValue", Keywords = "cast convert", BlueprintAutocast, AutoCreateRefTerm = "Value"))
	static bool Conv_InputActionValueToBool(const FInputActionValue& Value)
	{
		return Value.Get<bool>();
	}

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "To Float (InputActionValue)", CompactNodeTitle = "->", ScriptMethod = "InputActionValue", Keywords = "cast convert", BlueprintAutocast, AutoCreateRefTerm = "Value"))
	static float Conv_InputActionValueToFloat(const FInputActionValue& Value)
	{
		return Value.Get<float>();
	}

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "To Vector2D (InputActionValue)", CompactNodeTitle = "->", ScriptMethod = "InputActionValue", Keywords = "cast convert", BlueprintAutocast, AutoCreateRefTerm = "Value"))
	static FVector2D Conv_InputActionValueToVector2D(const FInputActionValue& Value)
	{
		return Value.Get<FVector2D>();
	}

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "To Vector (InputActionValue)", CompactNodeTitle = "->", ScriptMethod = "InputActionValue", Keywords = "cast convert", BlueprintAutocast, AutoCreateRefTerm = "Value"))
	static FVector Conv_InputActionValueToVector(const FInputActionValue& Value)
	{
		return Value.Get<FVector>();
	}
};