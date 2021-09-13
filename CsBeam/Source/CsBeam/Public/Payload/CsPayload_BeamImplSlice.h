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

			// ICsPayload_Beam

			FECsBeam Type;

			FVector Direction;

			FVector Location;

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

		// IPayload
		#pragma region
		public:

			FORCEINLINE const FECsBeam& GetType() const { return Type; }
			FORCEINLINE const FVector& GetDirection() const { return Direction; }
			FORCEINLINE const FVector& GetLocation() const { return Location; }

		#pragma endregion IPayload

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