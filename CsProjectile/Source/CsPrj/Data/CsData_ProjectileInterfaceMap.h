// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"

struct FCsInterfaceMap;
class UObject;

/**
*/
struct CSPRJ_API FCsData_ProjectileInterfaceMap final : public ICsGetInterfaceMap
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_ProjectileInterfaceMap();
	~FCsData_ProjectileInterfaceMap();


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