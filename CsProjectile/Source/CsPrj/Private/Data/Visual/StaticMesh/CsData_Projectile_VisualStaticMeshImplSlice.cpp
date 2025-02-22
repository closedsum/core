// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMeshImplSlice.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Projectile_VisualStaticMeshImplSlice)

using SliceType = NCsProjectile::NData::NVisual::NStaticMesh::NImplSlice::FImplSlice;

SliceType* FCsData_Projectile_VisualStaticMeshImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_VisualStaticMeshImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_VisualStaticMeshImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = CsPrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;
	
	typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, StaticMeshVisualDataType>(Context, Name);
	
	return Slice;
}

void FCsData_Projectile_VisualStaticMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Mesh.CopyToInfo(Slice->GetStaticMeshInfoPtr());
}

void FCsData_Projectile_VisualStaticMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Mesh.CopyToInfoAsValue(Slice->GetStaticMeshInfoPtr());
}

bool FCsData_Projectile_VisualStaticMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NData::NVisual::NStaticMesh::NImplSlice::FImplSlice);

namespace NCsProjectile
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

					/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
					{
						using namespace NCsProjectile::NData::NVisual::NStaticMesh::NImplSlice::NCached;

						CS_IS_PTR_NULL_RET_NULL(Object)

						#define DataHandlerType NCsData::NManager::NHandler::TData
						typedef NCsProjectile::NData::IData DataType;
						typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

						DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = CsPrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
						#undef DataHandlerType

						if (!DataHandler)
							return nullptr;

						typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;

						FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, StaticMeshVisualDataType>(Context, DataName);

						if (!Slice)
							return nullptr;

						// Check for properties matching interface: ProjectileDataType (NCsProjectile::NData::IData)
						typedef NCsProperty::FLibrary PropertyLibrary;

						bool Success = false;

						// Try FCsData_Projectile_VisualStaticMeshImplSlice
						typedef FCsData_Projectile_VisualStaticMeshImplSlice StructSliceType;

						if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualStaticMeshSlice, nullptr))
						{
							SliceAsStruct->CopyToSlice(Slice);
							Success = true;
						}
						// Try individual properties
						else
						{
							FCsPrjStaticMesh* StaticMeshPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsPrjStaticMesh>(Context, Object, Object->GetClass(), Name::StaticMesh, nullptr);

							if (StaticMeshPtr)
							{
								StaticMeshPtr->CopyToInfo(Slice->GetStaticMeshInfoPtr());
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh.")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Projectile_VisualStaticMeshImplSlice with name: VisualStaticMeshSlice.")));
								Log(FString::Printf(TEXT("%s: - OR")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsPrjStaticMesh with name: StaticMesh.")));
							}
						}
						return Slice;
					}

					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetStaticMeshInfo());
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						CS_IS_VALID(GetStaticMeshInfo())
						return true;
					}
				}
			}
		}
	}
}
