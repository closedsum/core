// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Skin/Data/Visual/CsData_Skin_VisualImplSlice.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"

#define SliceType NCsSkin::NData::NVisual::FImplSlice

void FCsData_Skin_VisualImplSlice::CopyToSlice(SliceType* Slice)
{
}

void FCsData_Skin_VisualImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
}

SliceType* FCsData_Skin_VisualImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::IVisual InterfaceType;

	if (InterfaceMap->Implements(InterfaceType::Name))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
		return nullptr;
	}

	CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

	SliceType* Slice = new SliceType();

	// Add slice as type SkinType
	InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
	// Set the InterfaceMap of Data to the "root" InterfaceMap
	Slice->SetInterfaceMap(InterfaceMap);

	DeconstructInterfaceSliceMap->AddSlice(SliceType::Name, Slice);
	DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(SliceType::Name, &SliceType::Deconstruct);

	CopyToSliceAsValue(Slice);

	return Slice;
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

			/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				using namespace NCsSkin::NData::NVisual::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

				typedef NCsSkin::NData::NVisual::IVisual InterfaceType;

				if (InterfaceMap->Implements(InterfaceType::Name))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
					return nullptr;
				}

				CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

				CS_IS_PTR_NULL_RET_NULL(Object)

				// Check for properties matching interface: SkinDataType (NCsSkin::NData::NVisual::IVisual)
				typedef NCsProperty::FLibrary PropertyLibrary;

				FImplSlice* Slice = nullptr;
				bool Success	  = false;

				// Try FCsData_Skin_VisualImplSlice
				typedef FCsData_Skin_VisualImplSlice StructSliceType;

				if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualSkinSlice, nullptr))
				{
					Slice = new FImplSlice();

					// Add slice as type SkinType
					InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
					// Set the InterfaceMap of Data to the "root" InterfaceMap
					Slice->SetInterfaceMap(InterfaceMap);

					DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
					DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}

				if (!Success)
				{
					if (Log)
					{
						typedef NCsObject::FLibrary ObjectLibrary;

						Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: SkinDataType (NCsSkin::NData::NVisual::IVisual)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualImplSlice with name: VisualSkinSlice."), *Context));
					}
				}
				return Slice;
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