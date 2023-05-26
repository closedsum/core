// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/Impact/CsData_Beam_VisualImpactImplSlice.h"

// Types
#include "Managers/FX/CsTypes_FX_Impact.h"
// Library
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"
// Engine
#include "Engine/DataTable.h"

#define SliceType NCsBeam::NData::NVisual::NImpact::FImplSlice

SliceType* FCsData_Beam_VisualImpactImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_VisualImpactImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Beam_VisualImpactImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
	typedef NCsBeam::NData::IData DataType;
	typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;
	
	typedef NCsBeam::NData::NVisual::NImpact::IImpact ImpactVisualDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, ImpactVisualDataType>(Context, Name);
	
	return Slice;
}

void FCsData_Beam_VisualImpactImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetImpactFXs(ImpactFXs.GetPtr());
}

void FCsData_Beam_VisualImpactImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetImpactFXs(ImpactFXs.Get());
}

#undef SliceType

bool FCsData_Beam_VisualImpactImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
{
	if (!ImpactFXs.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsBeam::NData::NVisual::NImpact::FImplSlice::Name = FName("NCsBeam::NData::NVisual::NImpact::FImplSlice");

namespace NCsBeam
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NImpact
			{
				namespace NImplSlice
				{
					namespace NCached
					{
						namespace Name
						{
							const FName VisualImpactSlice = FName("VisualImpactSlice");

							const FName ImpactFXs = FName("ImpactFXs");
						}
					}
				}

				const FCsFX& FImplSlice::GetImpactFX(const EPhysicalSurface& SurfaceType) const
				{
					// If SurfaceType does NOT exist, use Default
					EPhysicalSurface Surface = (uint8)SurfaceType >= ImpactFXRows.Num() ? EPhysicalSurface::SurfaceType_Default : SurfaceType;
					FCsFXImpact* ImpactFX	 = ImpactFXRows[(uint8)Surface];

					checkf(ImpactFX->Surface == Surface, TEXT("NCsBeam::NData::NVisual::NImpact::FImplSlice::GetImpactFX: No Impact FX was set for Physics Surface: %d."), (uint8)Surface);

					return ImpactFX->FX;
				}

				void FImplSlice::GenerateCached()
				{
					// Populate ImpactFXRows for quick look up
					const TMap<FName, uint8*>& RowMap = ImpactFXs->GetRowMap();

					ImpactFXRows.Reset((int32)EPhysicalSurface::SurfaceType_Max);

					for (const TPair<FName, uint8*>& Pair : RowMap)
					{
						uint8* Ptr			= const_cast<uint8*>(Pair.Value);
						FCsFXImpact* RowPtr = reinterpret_cast<FCsFXImpact*>(Ptr);

						const int32 Num	  = ImpactFXRows.Num();
						const int32 Index = (int32)RowPtr->Surface;

						for (int32 I = Num - 1; I < Index; ++I)
						{
							ImpactFXRows.AddDefaulted();
						}

						checkf(ImpactFXRows[Index] == nullptr, TEXT("NCsBeam::NData::NVisual::NImpact::FImplSlice::GenerateCached: Impact FX already exists for Physics Surface: %d."), Index);

						ImpactFXRows[Index] = RowPtr;
					}
				}

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
				{
					using namespace NCsBeam::NData::NVisual::NImpact::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(Object)

					#define DataHandlerType NCsData::NManager::NHandler::TData
					typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;
					typedef NCsBeam::NData::IData DataType;
					typedef NCsBeam::NData::FInterfaceMap DataInterfaceMapType;

					DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler = BeamManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
					#undef DataHandlerType

					if (!DataHandler)
						return nullptr;

					typedef NCsBeam::NData::NVisual::NImpact::IImpact VisualImpactDataType;

					FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, VisualImpactDataType>(Context, DataName);

					if (!Slice)
						return nullptr;

					// Check for properties matching interface: ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact)
					typedef NCsProperty::FLibrary PropertyLibrary;

					bool Success = false;

					// Try FCsData_Beam_VisualImpactImplSlice
					typedef FCsData_Beam_VisualImpactImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualImpactSlice, nullptr))
					{
						SliceAsStruct->CopyToSlice(Slice);
						Success = true;
					}
					// Try individual properties
					else
					{
						UDataTable** ImpactFXsPtr = PropertyLibrary::GetObjectPropertyValuePtr<UDataTable>(Context, Object, Object->GetClass(), Name::ImpactFXs, nullptr);

						if (ImpactFXsPtr)
						{
							Slice->SetImpactFXs(ImpactFXsPtr);
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact).")));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Beam_VisualImpactImplSlice with name: VisualImpactSlice.")));
							Log(FString::Printf(TEXT("%s: - OR")));
							Log(FString::Printf(TEXT("%s: - Failed to get object property of type: UDataTable with name: ImpactFXs.")));
						}
					}
					Slice->GenerateCached();
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(ImpactFXs)
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsBeam::FLog::Warning*/) const
				{
					CS_IS_PTR_NULL(ImpactFXs)
					return true;
				}
			}
		}
	}
}