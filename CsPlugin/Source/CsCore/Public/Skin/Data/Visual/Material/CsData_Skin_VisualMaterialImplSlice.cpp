// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterialImplSlice.h"

// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"

#define SliceType NCsSkin::NData::NVisual::NMaterial::FImplSlice

void FCsData_Skin_VisualMaterialImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetMaterials(Materials.GetPtr());
}

void FCsData_Skin_VisualMaterialImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetMaterials(Materials.Get());
}

SliceType* FCsData_Skin_VisualMaterialImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::NMaterial::IMaterial InterfaceType;

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

bool FCsData_Skin_VisualMaterialImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Materials.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualMaterialImplSlice::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
{
	check(Materials.IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Component, Materials.Get());
}

bool FCsData_Skin_VisualMaterialImplSlice::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Materials.IsValid(Context, Log))
		return false;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials.Get(), Log);
}

const FName NCsSkin::NData::NVisual::NMaterial::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NMaterial::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				namespace NImplSlice
				{
					namespace NCached
					{
						namespace Name
						{
							const FName VisualMaterialSlice = FName("VisualMaterialSlice");

							const FName Materials = FName("Materials");
						}
					}
				}

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
				{
					using namespace NCsSkin::NData::NVisual::NMaterial::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial InterfaceType;

					if (InterfaceMap->Implements(InterfaceType::Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
						return nullptr;
					}

					CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

					CS_IS_PTR_NULL_RET_NULL(Object)

					// Check for properties matching interface: MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
					typedef NCsProperty::FLibrary PropertyLibrary;

					FImplSlice* Slice = nullptr;
					bool Success	  = false;

					// Try FCsData_Skin_VisualStaticMeshImplSlice
					typedef FCsData_Skin_VisualMaterialImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualMaterialSlice, nullptr))
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
					// Try individual properties
					else
					{
						FCsTArrayMaterialInterface* MaterialsPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsTArrayMaterialInterface>(Context, Object, Object->GetClass(), Name::Materials, nullptr);

						if (MaterialsPtr)
						{
							Slice = new FImplSlice();

							// Add slice as type SkinType
							InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
							// Set the InterfaceMap of Data to the "root" InterfaceMap
							Slice->SetInterfaceMap(InterfaceMap);

							DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
							DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

							Slice->SetMaterials(MaterialsPtr->GetPtr());
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							typedef NCsObject::FLibrary ObjectLibrary;

							Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: FCsData_Skin_VisualMaterialImplSlice (NCsSkin::NData::NVisual::NMaterial::IMaterial)."), *(ObjectLibrary::PrintObjectAndClass(Object))));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMeshImplSlice with name: VisualMaterialSlice.")));
							Log(FString::Printf(TEXT("%s: - OR")));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsTArrayMaterialInterface with name: Materials.")));
						}
					}
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_TARRAY_EMPTY_CHECKED(GetMaterials(), UMaterialInterface*)

					CS_IS_TARRAY_ANY_NULL_CHECKED(GetMaterials(), UMaterialInterface)
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_TARRAY_EMPTY(GetMaterials(), UMaterialInterface*)

					CS_IS_TARRAY_ANY_NULL(GetMaterials(), UMaterialInterface)
					return true;
				}

				void FImplSlice::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
				{
					typedef NCsMaterial::FLibrary MaterialLibrary;

					MaterialLibrary::SetChecked(Context, Component, GetMaterials());
				}

				bool FImplSlice::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					typedef NCsMaterial::FLibrary MaterialLibrary;

					return MaterialLibrary::SetSafe(Context, Component, GetMaterials(), Log);
				}
			}
		}
	}
}
