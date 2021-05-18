// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/Impact/CsData_Projectile_VisualImpactImplSlice.h"

// Types
#include "Managers/FX/CsTypes_FX_Impact.h"
// Library
#include "Library/CsLibrary_Valid.h"

#define SliceType NCsProjectile::NData::NVisual::NImpact::FImplSlice

void FCsData_Projectile_VisualImpactImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetImpactFXs(ImpactFXs.GetPtr());
}

void FCsData_Projectile_VisualImpactImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetImpactFXs(ImpactFXs.Get());
}

#undef SliceType

bool FCsData_Projectile_VisualImpactImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	if (!ImpactFXs.IsValid(Context, Log))
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
				const FCsFX& FImplSlice::GetImpactFX(const EPhysicalSurface& SurfaceType) const
				{
					// If SurfaceType does NOT exist, use Default
					EPhysicalSurface Surface = (uint8)SurfaceType >= ImpactFXRows.Num() ? EPhysicalSurface::SurfaceType_Default : SurfaceType;
					FCsFXImpact* ImpactFX	 = ImpactFXRows[(uint8)Surface];

					checkf(ImpactFX->Surface == Surface, TEXT("NCsProjectile::NData::NVisual::NImpact::FImplSlice::GetImpactFX: No Impact FX was set for Physics Surface: %d."), (uint8)Surface);

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

						checkf(ImpactFXRows[Index] == nullptr, TEXT("NCsProjectile::NData::NVisual::NImpact::FImplSlice::GenerateCached: Impact FX already exists for Physics Surface: %d."), Index);

						ImpactFXRows[Index] = RowPtr;
					}
				}
			}
		}
	}
}