// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

/**
* Basic implementation of the interface: ICsPayload_UserWidget.
*/
struct CSUI_API FCsPayload_UserWidgetImplSlice : public ICsPayload_UserWidget,
												 public ICsReset
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsPayload_UserWidget

	ESlateVisibility Visibility;

public:

	FCsPayload_UserWidgetImplSlice();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

public:

	void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

// ICsPayload_UserWidget
#pragma region
public:

	FORCEINLINE const ESlateVisibility& GetVisibility() const
	{
		return Visibility;
	}

#pragma endregion ICsPayload_UserWidget

// ICsReset
#pragma region
public:

	void Reset();

#pragma endregion ICsReset

public:

	bool CopyFrom(const FCsPayload_UserWidgetImplSlice* From);
};