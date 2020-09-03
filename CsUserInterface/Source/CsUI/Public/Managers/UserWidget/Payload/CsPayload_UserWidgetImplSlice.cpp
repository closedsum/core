// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_UserWidgetImplSlice::Name = FName("FCsPayload_UserWidgetImplSlice");;

FCsPayload_UserWidgetImplSlice::FCsPayload_UserWidgetImplSlice() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_UserWidget
	Visibility(ESlateVisibility::SelfHitTestInvisible)
{
}

void FCsPayload_UserWidgetImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
{
	checkf(InInterfaceMap, TEXT("FCsPayload_UserWidgetImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

	checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_UserWidgetImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

	InterfaceMap = InInterfaceMap;

	InterfaceMap->Add<ICsPayload_UserWidget>(FCsPayload_UserWidgetImplSlice::Name, static_cast<ICsPayload_UserWidget*>(this));
}


// ICsReset
#pragma region

void FCsPayload_UserWidgetImplSlice::Reset()
{
	// ICsPayload_UserWidget
	Visibility = ESlateVisibility::SelfHitTestInvisible;
}

#pragma endregion ICsReset

bool FCsPayload_UserWidgetImplSlice::CopyFrom(const FCsPayload_UserWidgetImplSlice* From)
{
	Visibility = From->Visibility;
	return true;
}