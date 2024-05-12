// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/StaticMesh/CsData_Skin_VisualStaticMeshImplSlice.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"
// Components
#include "Components/StaticMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Skin_VisualStaticMeshImplSlice)

#define SliceType NCsSkin::NData::NVisual::NStaticMesh::FImplSlice

void FCsData_Skin_VisualStaticMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetStaticMesh(Mesh.GetPtr());
}

void FCsData_Skin_VisualStaticMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetStaticMesh(Mesh.Get());
}

SliceType* FCsData_Skin_VisualStaticMeshImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh InterfaceType;

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

bool FCsData_Skin_VisualStaticMeshImplSlice::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualStaticMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualStaticMeshImplSlice::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetStaticMesh(Mesh.Get());
}

bool FCsData_Skin_VisualStaticMeshImplSlice::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	Component->SetStaticMesh(Mesh.Get());
	return true;
}

const FName NCsSkin::NData::NVisual::NStaticMesh::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NStaticMesh::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				namespace NImplSlice
				{
					namespace NCached
					{
						namespace Name
						{
							const FName VisualStaticMeshSlice = FName("VisualStaticMeshSlice");

							const FName StaticMesh = FName("StaticMesh");
						}
					}
				}

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
				{
					using namespace NCsSkin::NData::NVisual::NStaticMesh::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

					typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh InterfaceType;

					if (InterfaceMap->Implements(InterfaceType::Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
						return nullptr;
					}

					CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

					CS_IS_PTR_NULL_RET_NULL(Object)

					// Check for properties matching interface: StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
					typedef NCsProperty::FLibrary PropertyLibrary;

					FImplSlice* Slice = nullptr;
					bool Success	  = false;

					// Try FCsData_Skin_VisualStaticMeshImplSlice
					typedef FCsData_Skin_VisualStaticMeshImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualStaticMeshSlice, nullptr))
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
						FCsStaticMesh* StaticMeshPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsStaticMesh>(Context, Object, Object->GetClass(), Name::StaticMesh, nullptr);

						if (StaticMeshPtr)
						{
							Slice = new FImplSlice();

							// Add slice as type SkinType
							InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
							// Set the InterfaceMap of Data to the "root" InterfaceMap
							Slice->SetInterfaceMap(InterfaceMap);

							DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
							DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

							Slice->SetStaticMesh(StaticMeshPtr->GetPtr());
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							typedef NCsObject::FLibrary ObjectLibrary;

							Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMeshImplSlice with name: VisualStaticMeshSlice."), *Context));
							Log(FString::Printf(TEXT("%s: - OR"), *Context));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsStaticMesh with name: StaticMesh."), *Context));
						}
					}
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetStaticMesh())
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetStaticMesh())
					return true;
				}

				void FImplSlice::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetStaticMesh(GetStaticMesh());
				}

				bool FImplSlice::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return false;

					CS_IS_PTR_NULL(Component)

					Component->SetStaticMesh(GetStaticMesh());
					return true;
				}
			}
		}
	}
}
