// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			/**
			* Basic implementation of the interface: NCsDamage::NValue::IValue
			*/
			struct CSCORE_API FImpl : public IValue,
									  public IPoint,
									  public ICsReset
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap InterfaceMap;

				// IPoint

				float Value;
				float* Value_Emu;

			public:

				FImpl();

				FImpl(const FImpl&) = delete;
				FImpl& operator = (const FImpl&) = delete;

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return const_cast<FCsInterfaceMap*>(&InterfaceMap); }

			#pragma endregion ICsGetInterfaceMap

			// IValue
			#pragma region
			public:

			#pragma endregion IValue

			// IPoint
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Value, float)

			#pragma endregion IPoint

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset
			};
		}
	}
}