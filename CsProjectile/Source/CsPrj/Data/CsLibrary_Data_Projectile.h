// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class ICsData_Projecitle;

struct CSPRJ_API FCsLibrary_Data_Projectile
{
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsData_Projectile>(Context, Data);
	}

	template<typename OtherInterfaceType>
	FORCEINLINE static OtherInterfaceType* GetInterfaceChecked(const FString& Context, ICsData_Projectile* Data)
	{
		return NCsInterfaceMap::GetInterfaceChecked<OtherInterfaceType>(Context, Data);
	}
};