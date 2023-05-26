// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/Impact/CsData_Projectile_VisualImpactImplSlice.h"

// Types
#include "Managers/FX/CsTypes_FX_Impact.h"
// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"
// Engine
#include "Engine/DataTable.h"

#define SliceType NCsProjectile::NData::NVisual::NImpact::FImplSlice

SliceType* FCsData_Projectile_VisualImpactImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_VisualImpactImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_VisualImpactImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
{
	#define DataHandlerType NCsData::NManager::NHandler::TData
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;
	
	typedef NCsProjectile::NData::NVisual::NImpact::IImpact ImpactVisualDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, ImpactVisualDataType>(Context, Name);
	
	return Slice;
}

void FCsData_Projectile_VisualImpactImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetImpactVisuals(ImpactVisuals.GetPtr());
}

void FCsData_Projectile_VisualImpactImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetImpactVisuals(ImpactVisuals.Get());
}

#undef SliceType

bool FCsData_Projectile_VisualImpactImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	if (!ImpactVisuals.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsProjectile::NData::NVisual::NImpact::FImplSlice::Name = FName("NCsProjectile::NData::NVisual::NImpact::FImplSlice");

namespace NCsProjectile
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
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCProjectile::NData::NVisual::NImpact::FImplSlice, GetImpactVisualInfo);
						}

						namespace Name
						{
							const FName VisualImpactSlice = FName("VisualImpactSlice");

							const FName ImpactVisuals = FName("ImpactVisuals");
						}
					}
				}

				#define ImpactVisualInfoType NCsProjectile::NImpact::NVisual::FInfo
				const ImpactVisualInfoType& FImplSlice::GetImpactVisualInfo(const EPhysicalSurface& SurfaceType) const
				{
					using namespace NCsProjectile::NData::NVisual::NImpact::NImplSlice::NCached;

					const FString& Context = Str::GetImpactVisualInfo;

					// If SurfaceType does NOT exist, use Default
					EPhysicalSurface Surface		 = (uint8)SurfaceType >= ImpactVisualInfosProxy.Num() ? EPhysicalSurface::SurfaceType_Default : SurfaceType;
					const ImpactVisualInfoType& Info = ImpactVisualInfosProxy[(uint8)Surface];

					checkf(Info.GetSurface() == Surface, TEXT("%s: No Impact FX was set for Physics Surface: %d."), *Context, (uint8)Surface);

					CS_IS_VALID_CHECKED(Info);
					return Info;
				}
				#undef ImpactVisualInfoType

				void FImplSlice::GenerateCached()
				{
					// Populate ImpactVisualInfosProxy for quick look up
					const TMap<FName, uint8*>& RowMap = ImpactVisuals->GetRowMap();

					const int32 Count = (int32)EPhysicalSurface::SurfaceType_Max;

					ImpactVisualInfosProxy.Reset(Count);
					ImpactVisualInfosProxy.AddDefaulted(Count);

					TArray<int32> DefaultIndices;

					DefaultIndices.Reset(Count);

					for (int32 I = 0; I < Count; ++I)
					{
						DefaultIndices.Add(1);
					}

					for (const TPair<FName, uint8*>& Pair : RowMap)
					{
						uint8* Ptr								= const_cast<uint8*>(Pair.Value);
						FCsProjectile_Visual_ImpactInfo* RowPtr = reinterpret_cast<FCsProjectile_Visual_ImpactInfo*>(Ptr);

						const int32 Index = (int32)RowPtr->Surface;

						DefaultIndices[Index] = 0;

						RowPtr->CopyToInfo(&(ImpactVisualInfosProxy[Index]));
					}

					typedef NCsProjectile::NImpact::NVisual::FInfo ImpactVisualInfoType;

					const ImpactVisualInfoType& DefaultInfo = ImpactVisualInfosProxy[(uint8)EPhysicalSurface::SurfaceType_Default];

					for (int32& Index : DefaultIndices)
					{
						if (Index == 1)
						{
							ImpactVisualInfosProxy[Index].Copy(DefaultInfo);
						}
					}
				}

				/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
				{
					using namespace NCsProjectile::NData::NVisual::NImpact::NImplSlice::NCached;

					CS_IS_PTR_NULL_RET_NULL(Object)

					#define DataHandlerType NCsData::NManager::NHandler::TData
					typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
					typedef NCsProjectile::NData::IData DataType;
					typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

					DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
					#undef DataHandlerType

					if (!DataHandler)
						return nullptr;

					typedef NCsProjectile::NData::NVisual::NImpact::IImpact VisualImpactDataType;

					FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, VisualImpactDataType>(Context, DataName);

					if (!Slice)
						return nullptr;

					// Check for properties matching interface: ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact)
					typedef NCsProperty::FLibrary PropertyLibrary;

					bool Success = false;

					// Try FCsData_Projectile_VisualImpactImplSlice
					typedef FCsData_Projectile_VisualImpactImplSlice StructSliceType;

					if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualImpactSlice, nullptr))
					{
						SliceAsStruct->CopyToSlice(Slice);
						Success = true;
					}
					// Try individual properties
					else
					{
						UDataTable** ImpactVisualsPtr = PropertyLibrary::GetObjectPropertyValuePtr<UDataTable>(Context, Object, Object->GetClass(), Name::ImpactVisuals, nullptr);

						if (ImpactVisualsPtr)
						{
							Slice->SetImpactVisuals(ImpactVisualsPtr);
							Success = true;
						}
					}

					if (!Success)
					{
						if (Log)
						{
							Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: ImpactVisualDataType (NCsProjectile::NData::NVisual::NImpact::IImpact).")));
							Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Projectile_VisualImpactImplSlice with name: VisualImpactSlice.")));
							Log(FString::Printf(TEXT("%s: - OR")));
							Log(FString::Printf(TEXT("%s: - Failed to get object property of type: UDataTable with name: ImpactVisuals.")));
						}
					}
					Slice->GenerateCached();
					return Slice;
				}

				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(ImpactVisuals)
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_PTR_NULL(ImpactVisuals)
					return true;
				}
			}
		}
	}
}