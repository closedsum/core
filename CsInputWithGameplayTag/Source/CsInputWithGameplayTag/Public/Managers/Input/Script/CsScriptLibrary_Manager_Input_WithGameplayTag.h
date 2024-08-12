// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Namespace.h"
#include "GameplayTagContainer.h"

#include "CsScriptLibrary_Manager_Input_WithGameplayTag.generated.h"

// NCsInput::NWithGameplayTag::NManager::FLibrary
CS_FWD_DECLARE_CLASS_NAMESPACE_3(NCsInput, NWithGameplayTag, NManager, FLibrary)

UCLASS()
class CSINPUTWITHGAMEPLAYTAG_API UCsScriptLibrary_Manager_Input_WithGameplayTag : public UObject
{ 
	GENERATED_UCLASS_BODY() 

private:

	typedef NCsInput::NWithGameplayTag::NManager::FLibrary NativeLibrary;

	static void(*LogError)(const FString&);

// Get
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static UObject* GetAsObject(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Get as Object (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess);

#pragma endregion Get

// Tag
#pragma region
public:

	// HasMapping

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool HasMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag);

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool HasMappingByName(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FName& Tag);

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool HasMappingByString(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FString& Tag);

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Has Mapping (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool HasMappingChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess);

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Has Mapping by Name (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool HasMappingByNameChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FName& Tag, bool& OutSuccess);

	UFUNCTION(BlueprintPure, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Has Mapping By String (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool HasMappingByStringChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FString& Tag, bool& OutSuccess);

	// SetMappingActive

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool SetMappingActive(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool SetMappingActiveByName(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FName& Tag);

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool SetMappingActiveByString(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FString& Tag);

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Set Mapping Active (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess);

	// SetMappingInactive

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool SetMappingInctive(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Set Mapping Inactive (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static void SetMappingInctiveChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess);

	// BlockMapping

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static bool BlockMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = "CsInputWithGameplayTag|Managers|Input|WithGameplayTag|Library", meta = (DisplayName = "Block Mapping (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Tag"))
	static void BlockMappingChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess);

#pragma endregion Tag
};