// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Types/CsData_GetBeamTypeImplSlice.h"

// Library
#include "Library/CsLibrary_Valid.h"

#define SliceType NCsBeam::NData::NType::FImplSlice

void FCsData_GetBeamTypeImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetBeamType(Type);
}

void FCsData_GetBeamTypeImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetBeamType(Type);
}

#undef SliceType

bool FCsData_GetBeamTypeImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsBeam, FECsBeam, Type)
	return true;
}

const FName NCsBeam::NData::NType::FImplSlice::Name = FName("NCsBeam::NData::NType::FImplSlice");

namespace NCsBeam
{
	namespace NData
	{
		namespace NType
		{
			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				EMCsBeam::Get().IsValidEnumChecked(Context, GetBeamType());
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsBeam, FECsBeam, GetBeamType())
				return true;
			}
		}
	}
}