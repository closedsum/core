// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"
// Data
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/CsData_DamageInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NManager
	{
		namespace NHandler
		{
		#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
		#define DataType NCsDamage::NData::IData
		#define DataInterfaceMapType NCsDamage::NData::FInterfaceMap

			/**
			*/
			class CSCORE_API FData : public DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType> Super;

			public:

				FData();
			};

		#undef DataHandlerType
		#undef DataType
		#undef DataInterfaceMapType
		}
	}

}