// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"

struct FCsInterfaceMap;
class UObject;

/**
*/
struct CSUI_API FCsData_WidgetActorInterfaceMap final : public ICsGetInterfaceMap
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_WidgetActorInterfaceMap();
	~FCsData_WidgetActorInterfaceMap();


	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap
};