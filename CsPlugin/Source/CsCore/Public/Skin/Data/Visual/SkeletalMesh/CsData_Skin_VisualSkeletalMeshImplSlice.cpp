// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMeshImplSlice.h"

// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"
// Components
#include "Components/SkeletalMeshComponent.h"

#define SliceType NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice

void FCsData_Skin_VisualSkeletalMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetSkeletalMesh(Mesh.GetPtr());
}

void FCsData_Skin_VisualSkeletalMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetSkeletalMesh(Mesh.Get());
}

SliceType* FCsData_Skin_VisualSkeletalMeshImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh InterfaceType;

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

bool FCsData_Skin_VisualSkeletalMeshImplSlice::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualSkeletalMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualSkeletalMeshImplSlice::SetChecked(const FString& Context, USkeletalMeshComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetSkeletalMesh(Mesh.Get());
}

bool FCsData_Skin_VisualSkeletalMeshImplSlice::SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	Component->SetSkeletalMesh(Mesh.Get());
	return true;
}

const FName NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMesh
			{
				namespace NImplSlice
				{
					namespace NCached
					{
						namespace Name
						{
							const FName VisualSkeletalMeshSlice = FName("VisualSkeletalMeshSlice");

							const FName SkeletalMesh = FName("SkeletalMesh");
						}
					}
				}

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
				{
					using namespace NCsSkin::NData::NVisual::NSkeletalMesh::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

					typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh InterfaceType;

					if (InterfaceMap->Implements(InterfaceType::Name))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
						return nullptr;
					}

					CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

					CS_IS_PTR_NULL_RET_NULL(Object)

					// Check for properties matching interface: SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
					typedef NCsProperty::FLibrary PropertyLibrary;

					FImplSlice* Slice = nullptr;
					bool Success	  = false;

					// Try FCsData_Skin_VisualSkeletalMeshImplSlice
					typedef FCsData_Skin_VisualSkeletalMeshImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualSkeletalMeshSlice, nullptr))
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
						FCsSkeletalMesh* SkeletalMeshPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsSkeletalMesh>(Context, Object, Object->GetClass(), Name::SkeletalMesh, nullptr);

						if (SkeletalMeshPtr)
						{
							Slice = new FImplSlice();

							// Add slice as type SkinType
							InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
							// Set the InterfaceMap of Data to the "root" InterfaceMap
							Slice->SetInterfaceMap(InterfaceMap);

							DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
							DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

							Slice->SetSkeletalMesh(SkeletalMeshPtr->GetPtr());
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							typedef NCsObject::FLibrary ObjectLibrary;

							Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)."), *(ObjectLibrary::PrintObjectAndClass(Object))));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualSkeletalMeshImplSlice with name: VisualSkeletalMeshSlice.")));
							Log(FString::Printf(TEXT("%s: - OR")));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsSkeletalMesh with name: SkeletalMesh.")));
						}
					}
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetSkeletalMesh())
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetSkeletalMesh())
					return true;
				}

				void FImplSlice::SetChecked(const FString& Context, USkeletalMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetSkeletalMesh(GetSkeletalMesh());
				}

				bool FImplSlice::SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return false;

					CS_IS_PTR_NULL(Component)

					Component->SetSkeletalMesh(GetSkeletalMesh());
					return true;
				}
			}
		}
	}
}
