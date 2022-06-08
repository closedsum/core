// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsProjectile
{
	namespace NData
	{
		#define DataType NCsProjectile::NData::IData

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
		{
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			return true;
		}

		#undef DataType
	}
}