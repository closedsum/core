// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Enhanced/Data/CsEnhancedInputWithGameplayTagDataRootSet.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Enhanced/Data/CsData_EnhancedInput_WithGameplayTag.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsEnhancedInputWithGameplayTagDataRootSet)

bool FCsEnhancedInputWithGameplayTagDataRootSet::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(Data)
	return true;
}

UCsData_EnhancedInput_WithGameplayTag* FCsEnhancedInputWithGameplayTagDataRootSet::GetDataChecked(const FString& Context) const
{
	return CS_SUBCLASS_OF_GET_DEFAULT_OBJ_CHECKED(Data, UCsData_EnhancedInput_WithGameplayTag);
}