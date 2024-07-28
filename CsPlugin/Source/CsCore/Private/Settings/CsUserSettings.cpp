// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsUserSettings.h"

#if WITH_EDITOR
// UI
#include "UI/Tool/CsGetSlateApplicationTool.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserSettings)

UCsUserSettings::UCsUserSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Editor
	EditorUI_ApplicationScale(1.0f),
	GCInterval(60.0f),
	bForceGCOnEndPIE(false),
	// Enum
	bOnSave_DataTable_EnumStructLayoutResolveChanges(true),
	// Data
	bOnSave_Data_PopulatePaths(true),
	bOnSave_DataTable_PopulatePaths(true)
{
}

// UObject Interface
#pragma region

#if WITH_EDITOR

void UCsUserSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	if (PropertyName == FName("EditorUI_ApplicationScale"))
	{
		ApplyEditorUI_ApplicationScale();
	}
	if (PropertyName == FName("GCInterval"))
	{
		IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("gc.TimeBetweenPurgingPendingKillObjects"));
		CVar->Set(GCInterval, ECVF_SetByCode);
	}
	Super::PostEditChangeProperty(e);
}

void UCsUserSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyFName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FString PropertyName	   = (e.Property != NULL) ? e.Property->GetName() : TEXT("");
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	//int32 Index;
	/*
	TSet<FString> PropertyNames;
	CsPropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);
	*/
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion UObject Interface

// Editor
#pragma region

#if WITH_EDITOR

void UCsUserSettings::ApplyEditorUI_ApplicationScale()
{
	if (ICsGetSlateApplicationTool* Interface = Cast<ICsGetSlateApplicationTool>(GEngine))
	{
		Interface->GetSlateApplicationTool()->ApplyApplicationScaleImpl(EditorUI_ApplicationScale);
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Editor