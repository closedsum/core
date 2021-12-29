// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Beam.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsBeam
{
	namespace NPayload
	{
		/**
		* Basic implementation of the interface: NCsBeam::NPayload::IPayload.
		*/
		struct CSBEAM_API FImplSlice : public IPayload,
									   public ICsReset
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			// BeamPayloadType (NCsBeam::Payload::IPayload)

			FECsBeam Type;

			ECsAttachmentTransformRules AttachRules;

			FVector Location;

			FVector Direction;

			FVector Scale;

		public:

			FImplSlice();
			~FImplSlice(){}

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		public:

			void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

		// BeamPayloadType (NCsBeam::Payload::IPayload)
		#pragma region
		public:

			FORCEINLINE const FECsBeam& GetType() const { return Type; }
			FORCEINLINE const ECsAttachmentTransformRules& GetAttachRules() const { return AttachRules; }
			FORCEINLINE const FVector& GetLocation() const { return Location; }
			FORCEINLINE const FVector& GetDirection() const { return Direction; }
			FORCEINLINE const FVector& GetScale() const { return Scale; }

		#pragma endregion BeamPayloadType (NCsBeam::Payload::IPayload)

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset

		public:

			bool CopyFrom(const FImplSlice* From);
		};
	}
}