// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsData
{
#define DataType NCsData::IData

	/**
	*/
	struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<DataType>
	{
	public:

		/**
		* Get the Root for Manager_Data.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* return				Root for Manager_Data
		*/
		static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);

		/**
		* Print out Object as 'Object: %s with Class: %s'.
		* 
		* @param Object	Object to print.
		* return		String in the format: 'Object: %s with Class: %s'.
		*/
		static FString PrintObjectAndClass(UObject* Object);

		/**
		* Print out Data as '[MemberName]: %s with Class: %s'.
		* 
		* @param Data		Data to print.
		* @param MemberName	Name of the Data.
		* return			String in the format: '[MemberName]: %s with Class: %s'.
		*/
		static FString PrintObjectAndClass(ICsData* Data, const FString& MemberName);
		
		/**
		* Print out Data as 'Object: %s with Class: %s'.
		* 
		* @param Data	Data to print.
		* return		String in the formate: 'Object: %s with Class: %s'.
		*/
		static FString PrintObjectAndClass(ICsData* Data);

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: DataType (NCsData::IData).
		* 
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Loaded object of type: DataType (NCsData::IData).
		*/
		static DataType* SafeLoad(const FString& Context, UObject* Object);

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: InterfaceType.
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Loaded object of type: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* SafeLoad(const FString& Context, UObject* Object)
		{
			DataType* Data = SafeLoad(Context, Object);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		* Safely get the Data from Object.
		*  Data implements the interface: DataType (NCsData::IData).
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Data that implements the interface: DataType (NCsData::IData).
		*/
		static DataType* GetSafe(const FString& Context, UObject* Object);

		/**
		* Safely get the Data from Object.
		*  Data implements the interface: InterfaceType.
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Data that implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetSafe(const FString& Context, UObject* Object)
		{
			DataType* Data = GetSafe(Context, Object);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		* Get Data with name DataName which implements the interface: DataType (NCsData::IData).
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* return				Data which implements the interface: DataType (NCsData::IData).	
		*/
		static DataType* GetChecked(const FString& Context, UObject* WorldContext, const FName& DataName);

		/**
		* Get Data with name DataName which implements the interface: InterfaceType.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* return				Data which implements the interface: InterfaceType.	
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetChecked(const FString& Context, UObject* WorldContext, const FName& DataName)
		{
			DataType* Data = GetChecked(Context, WorldContext, DataName);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* Get Data from Object which implements the interface: DataType (NCsData::IData).
		* 
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Object that implements the interface: DataType (NCsData::IData).
		*/
		static DataType* GetChecked(const FString& Context, UObject* Object);

		/**
		* Get Data from Object which implements the interface: InterfaceType.
		*
		* @param Context	The calling context.
		* @param Data		UObject that SHOULD implement the interface: ICsData.
		* return			Object that implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetChecked(const FString& Context, UObject* Object)
		{
			DataType* Data = GetChecked(Context, Object);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* Get the underlying data that implements the interface: DataType (NCsData::IData)
		* from the UObject, UData, which implements the interface: ICsData.
		* 
		* @param Context	The calling context.
		* @param Data		UObject that implements the interface: ICsData.
		* return			Object that implements the interface: DataType (NCsData::IData).
		*/
		static DataType* GetChecked(const FString& Context, ICsData* UData);

		/**
		* Get the underlying data that implements the interface: InterfaceType
		* from the UObject, UData, which implements the interface: ICsData.
		*
		* @param Context	The calling context.
		* @param Data		UObject that implements the interface: ICsData.
		* return			Object that implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetChecked(const FString& Context, ICsData* UData)
		{
			DataType* Data = GetChecked(Context, UData);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}
	};
#undef DataType
}