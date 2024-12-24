// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Managers/Trace/Data/Damage/CsData_TraceDamage.h"
//#include "Trace/Data/Visual/CsData_Trace_VisualTracer.h"
//#include "Trace/Data/Visual/CsData_Trace_VisualImpact.h"
//#include "Trace/Data/Sound/CsData_Trace_SoundImpact.h"

namespace NCsTrace
{
	namespace NData
	{
		namespace NLibrary
		{
			bool FLibrary::IsValidChecked(const FString& Context, DataType* Data)
			{
				CS_IS_PTR_NULL_CHECKED(Data)

				// DamageDataType (NCsTrace::NData::NDamage::IDamage
				typedef NCsTrace::NData::NDamage::IDamage DamageDataType;

				if (DamageDataType* DamageData = GetSafeInterfaceChecked<DamageDataType>(Context, Data))
				{
					checkf(DamageData->GetDamageData(), TEXT("%s: Data implements interface: %s but GetDamageData() is NULL."), *Context, *(DamageDataType::Name.ToString()));
				}
			
				// TracerVisualDataType  (NCsTrace::NData::NVisual::NTracer::ITracer)
				/*typedef NCsTrace::NData::NVisual::NTracer::ITracer TracerVisualDataType;

				if (TracerVisualDataType* VisualTracerData = GetSafeInterfaceChecked<TracerVisualDataType>(Context, Data))
				{
					const FCsFX& FX = VisualTracerData->GetTracerFX();

					checkf(FX.Get(), TEXT("%s: Data implements interface: %s but GetTracerFX().Get() is NULL."), *Context, *(TracerVisualDataType::Name.ToString()));

					CS_IS_VALID_CHECKED(FX);
				}*/

				// ImpactVisualDataType (NCsTrace::NData::NVisual::NImpact::IImpact)
				/*typedef NCsTrace::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

				if (ImpactVisualDataType* VisualImpactData = GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
				{
					const FCsFX& FX = VisualImpactData->GetImpactFX(EPhysicalSurface::SurfaceType_Default);

					checkf(FX.Get(), TEXT("%s: Data implements interface: %s but GetImpactFX('Default').Get() is NULL."), *Context, *(ImpactVisualDataType::Name.ToString()));

					CS_IS_VALID_CHECKED(FX);
				}*/

				// ImpactSoundDataType (NCsTrace::NData::NSound::NImpact::IImpact)
				/*typedef NCsTrace::NData::NSound::NImpact::IImpact ImpactSoundDataType;

				if (ImpactSoundDataType* VisualImpactData = GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
				{
					const FCsSound& Sound = VisualImpactData->GetImpactSound(EPhysicalSurface::SurfaceType_Default);

					checkf(Sound.Get(), TEXT("%s: Data implements interface: %s but GetImpactSound('Default').Get() is NULL."), *Context, *(ImpactSoundDataType::Name.ToString()));

					CS_IS_VALID_CHECKED(Sound);
				}*/

				return true;
			}
		}
	}
}