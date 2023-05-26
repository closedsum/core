// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/StaticMesh/CsData_Beam_VisualStaticMeshImplSlice.h"

// Library
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"

#define SliceType NCsBeam::NData::NVisual::NStaticMesh::FImplSlice

SliceType* FCsData_Beam_VisualStaticMeshImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_VisualStaticMeshImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_VisualStaticMeshImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
	typedef NCsBeam::NData::IData DataType;
	typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;
	
	typedef NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, StaticMeshVisualDataType>(Context, Name);
	
	return Slice;
}

void FCsData_Beam_VisualStaticMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetStaticMesh(Mesh.GetPtr());
}

void FCsData_Beam_VisualStaticMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetStaticMesh(Mesh.Get());
}

#undef SliceType

bool FCsData_Beam_VisualStaticMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsBeam::NData::NVisual::NStaticMesh::FImplSlice::Name = FName("NCsBeam::NData::NVisual::NStaticMesh::FImplSlice");

namespace NCsBeam
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

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
				{
					using namespace NCsBeam::NData::NVisual::NStaticMesh::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(Object)

					#define DataHandlerType NCsData::NManager::NHandler::TData
					typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
					typedef NCsBeam::NData::IData DataType;
					typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;

					DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
					#undef DataHandlerType

					if (!DataHandler)
						return nullptr;

					typedef NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;

					FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, StaticMeshVisualDataType>(Context, DataName);

					if (!Slice)
						return nullptr;

					// Check for properties matching interface: BeamDataType (NCsBeam::NData::IData)
					typedef NCsProperty::FLibrary PropertyLibrary;

					bool Success = false;

					// Try FCsData_Beam_VisualStaticMeshImplSlice
					typedef FCsData_Beam_VisualStaticMeshImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualStaticMeshSlice, nullptr))
					{
						SliceAsStruct->CopyToSlice(Slice);
						Success = true;
					}
					// Try individual properties
					else
					{
						FCsStaticMesh* StaticMeshPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsStaticMesh>(Context, Object, Object->GetClass(), Name::StaticMesh, nullptr);

						if (StaticMeshPtr)
						{
							Slice->SetStaticMesh(StaticMeshPtr->GetPtr());
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh.")));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Beam_VisualStaticMeshImplSlice with name: VisualStaticMeshSlice.")));
							Log(FString::Printf(TEXT("%s: - OR")));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsStaticMesh with name: StaticMesh.")));
						}
					}
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetStaticMesh())
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetStaticMesh())
					return true;
				}
			}
		}
	}
}
