// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"

// Data
#include "Managers/Trace/Data/Damage/CsData_TraceDamage.h"
#include "Managers/Trace/Data/Visual/CsData_Trace_VisualTracer.h"
#include "Managers/Trace/Data/Visual/CsData_Trace_VisualImpact.h"
#include "Managers/Trace/Data/Sound/CsData_Trace_SoundImpact.h"

namespace NCsTrace
{
	namespace NData
	{
		#define DataType NCsTrace::NData::IData
		bool FLibrary::IsValidChecked(const FString& Context, DataType* Data)
		{
		#undef DataType

			checkf(Data, TEXT("%s: Data is NULL."), *Context);

			// DamageDataType (NCsTrace::NData::NDamage::IDamage
			typedef NCsTrace::NData::NDamage::IDamage DamageDataType;

			if (DamageDataType* DamageData = GetSafeInterfaceChecked<DamageDataType>(Context, Data))
			{
				checkf(DamageData->GetDamageData(), TEXT("%s: Data implements interface: %s but GetDamageData() is NULL."), *Context, *(DamageDataType::Name.ToString()));
			}
			
			// TracerVisualDataType  (NCsTrace::NData::NVisual::NTracer::ITracer)
			typedef NCsTrace::NData::NVisual::NTracer::ITracer TracerVisualDataType;

			if (TracerVisualDataType* VisualTracerData = GetSafeInterfaceChecked<TracerVisualDataType>(Context, Data))
			{
				checkf(VisualTracerData->GetTracerFX().Get(), TEXT("%s: Data implements interface: %s but GetTracerFX().Get() is NULL."), *Context, *(TracerVisualDataType::Name.ToString()));
			}

			// ImpactVisualDataType (NCsTrace::NData::NVisual::NImpact::IImpact)
			typedef NCsTrace::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

			if (ImpactVisualDataType* VisualImpactData = GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
			{
				checkf(VisualImpactData->GetImpactFX(EPhysicalSurface::SurfaceType_Default).Get(), TEXT("%s: Data implements interface: %s but GetImpactFX('Default').Get() is NULL."), *Context, *(ImpactVisualDataType::Name.ToString()));
			}

			// ImpactSoundDataType (NCsTrace::NData::NSound::NImpact::IImpact)
			typedef NCsTrace::NData::NSound::NImpact::IImpact ImpactSoundDataType;

			if (ImpactSoundDataType* VisualImpactData = GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
			{
				checkf(VisualImpactData->GetImpactSound(EPhysicalSurface::SurfaceType_Default).Get(), TEXT("%s: Data implements interface: %s but GetImpactSound('Default').Get() is NULL."), *Context, *(ImpactSoundDataType::Name.ToString()));
			}

			return true;
		}
	}
}