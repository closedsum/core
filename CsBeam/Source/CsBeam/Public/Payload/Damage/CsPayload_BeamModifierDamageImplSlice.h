// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Payload/Damage/CsPayload_BeamModifierDamage.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsBeam
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				/**
				* 
				*/
				struct CSBEAM_API FImplSlice : public IDamage,
											  public ICsReset
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// IDamage

					TArray<NCsDamage::NModifier::IModifier*> Modifiers;

				public:

					FImplSlice();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

				// IDamage
				#pragma region
				public:

					FORCEINLINE const TArray<NCsDamage::NModifier::IModifier*>& GetDamageModifiers() const { return Modifiers; }

				#pragma endregion IDamage

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
	}
}