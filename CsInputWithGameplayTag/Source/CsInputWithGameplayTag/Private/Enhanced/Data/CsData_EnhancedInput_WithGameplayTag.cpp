// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Enhanced/Data/CsData_EnhancedInput_WithGameplayTag.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Property.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_EnhancedInput_WithGameplayTag)

UCsData_EnhancedInput_WithGameplayTag::UCsData_EnhancedInput_WithGameplayTag(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	Inner()
{
}

// UObject Interface
#pragma region

#if WITH_EDITOR

void UCsData_EnhancedInput_WithGameplayTag::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	//int32 Index;
	TSet<FString> PropertyNames;
	CsPropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);

	// Inner
	if (PropertyNames.Contains(TEXT("Inner")))
	{
		Inner.OnPostEditChange(PropertyNames);
	}
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion UObject Interface