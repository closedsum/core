// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsSeqRegisterStructOpsData.h"

#include "CsStructOps_Data.h"
// Structs
#include "Types/CsTypes_LevelSequence.h"

namespace NCsSeq
{
	namespace NStruct
	{
		namespace NOps
		{
			namespace NData
			{
				void FRegister::Execute()
				{
					typedef NCsStruct::NOps::NData::FTool ToolType;

				#define REGISTER_UNLOAD_FN(__Struct) ToolType::Get().RegisterUnloadFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_Data_Unload)

					// LevelSequence
					{
						REGISTER_UNLOAD_FN(FCsLevelSequence);
					}

				#undef REGISTER_UNLOAD_FN
				}
			}
		}
	}
}