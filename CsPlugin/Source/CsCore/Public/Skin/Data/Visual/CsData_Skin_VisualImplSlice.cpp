// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualImplSlice.h"

// Library
#include "Library/CsLibrary_Property.h"

#define SliceType NCsSkin::NData::NVisual::FImplSlice

void FCsData_Skin_VisualImplSlice::CopyToSlice(SliceType* Slice)
{
}

void FCsData_Skin_VisualImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
}

#undef SliceType

bool FCsData_Skin_VisualImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

const FName NCsSkin::NData::NVisual::FImplSlice::Name = FName("NCsSkin::NData::NVisual::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName VisualSkinSlice = FName("VisualSkinSlice");
					}
				}
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
			{
				return true;
			}
		}
	}
}