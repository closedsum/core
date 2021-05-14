// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsProjectile
{
	namespace NData
	{
	#define DataType NCsProjectile::NData::IData

		struct CSPRJ_API FLibrary final : public TCsLibrary_InterfaceMap<DataType>
		{
		};

	#undef DataType
	}
}