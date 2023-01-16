// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_BeamImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsBeam::NPayload::FImplSlice::Name = FName("NCsBeam::NPayload::FImplSlice");;

namespace NCsBeam
{
	namespace NPayload
	{
		FImplSlice::FImplSlice() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// IPayload
			Type(),
			AttachRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Location(0.0f),
			Direction(0.0f),
			Scale(0.0f)
		{
		}

		void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
		{
			checkf(InInterfaceMap, TEXT("FCsPayload_BeamImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

			checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_BeamImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

			InterfaceMap = InInterfaceMap;

			InterfaceMap->Add<IPayload>(FImplSlice::Name, static_cast<IPayload*>(this));
		}


		// ICsReset
		#pragma region

		void FImplSlice::Reset()
		{
			// BeamPayloadType (NCsBeam::Payload::IPayload)
			Type = EMCsBeam::Get().GetMAX();
			AttachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Location = FVector::ZeroVector;
			Direction = FVector::ZeroVector;
			Scale = FVector::OneVector;
		}

		#pragma endregion ICsReset

		bool FImplSlice::CopyFrom(const FImplSlice* From)
		{
			Type = From->Type;
			AttachRules = From->AttachRules;
			Location = From->Location;
			Direction = From->Direction;
			Scale = From->Scale;
			return true;
		}
	}
}