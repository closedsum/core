// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Projectile
#include "Payload/CsPayload_Weapon.h"
// Reset
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NPayload
	{
	#define PayloadType NCsWeapon::NPayload::IPayload

		/**
		* Basic implementation of the interface: PayloadType (NCsWeapon::NPayload::IPayload).
		*/
		struct CSWP_API FImplSlice : public PayloadType,
									 public ICsReset
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			// PayloadType (NCsWeapon::NPayload::IPayload)

			FECsWeapon Type;

			FECsUpdateGroup UpdateGroup;

			FTransform Transform;

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

		// PayloadType (NCsWeapon::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const FECsWeapon& GetType() const { return Type; }
			FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const { return UpdateGroup; }
			FORCEINLINE const FTransform& GetTransform() const { return Transform; }

		#pragma endregion PayloadType (NCsWeapon::NPayload::IPayload)

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset

		public:

			bool CopyFrom(const FImplSlice* From);
		};

	#undef PayloadType
	}
}