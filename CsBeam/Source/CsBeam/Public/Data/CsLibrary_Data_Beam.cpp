// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Beam.h"


namespace NCsBeam
{
	namespace NData
	{
		#define DataType NCsBeam::NData::IData

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
		{
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			return true;
		}

		#undef DataType
	}
}