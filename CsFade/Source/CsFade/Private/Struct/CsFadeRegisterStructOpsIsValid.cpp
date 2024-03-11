// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsFadeRegisterStructOpsIsValid.h"

#include "Struct/CsStructOps_IsValid.h"
// Structs
#include "Managers/Fade/CsTypes_Fade.h"

namespace NCsFade
{
	namespace NStruct
	{
		namespace NOps
		{
			namespace NIsValid
			{
				void FRegister::Execute()
				{
					typedef NCsStruct::NOps::NIsValid::FTool ToolType;

				#define REGISTER_IS_VALID_FNS(__Struct) ToolType::Get().RegisterIsValidCheckedFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsValidChecked); \
					ToolType::Get().RegisterIsValidFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsValid); \
					ToolType::Get().RegisterIsTopValidCheckedFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsTopValidChecked); \
					ToolType::Get().RegisterIsTopValidFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsTopValid);

					// Fade
					{
						REGISTER_IS_VALID_FNS(FCsFade_ClearToBlackParams)
						REGISTER_IS_VALID_FNS(FCsFade_BlackToClearParams)
						REGISTER_IS_VALID_FNS(FCsFadeParams)
					}

				#undef REGISTER_IS_VALID_FNS
				}
			}
		}
	}
}