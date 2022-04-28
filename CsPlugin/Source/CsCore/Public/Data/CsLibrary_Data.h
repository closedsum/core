// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Data
#include "Data/CsData.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsLog.h"

namespace NCsData
{
	namespace NCached
	{
		namespace Str
		{
			extern CSCORE_API const FString SafeLoad;
		}
	}

#define DataType NCsData::IData

	/**
	*/
	struct CSCORE_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
	{
	public:

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

	// Load
	#pragma region
	public:

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: DataType (NCsData::IData).
		* 
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* @param Log		Log function.
		* return			Loaded object of type: DataType (NCsData::IData).
		*/
		static DataType* SafeLoad(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: InterfaceType.
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* @param Log		Log function.
		* return			Loaded object of type: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* SafeLoad(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			DataType* Data = SafeLoad(Context, Object, Log);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: DataType (NCsData::IData).
		*
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Loaded object of type: DataType (NCsData::IData).
		*/
		static DataType* SafeLoad(UObject* Object);

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: InterfaceType.
		*
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Loaded object of type: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* SafeLoad(UObject* Object)
		{
			using namespace NCached;

			const FString& Context = Str::SafeLoad;

			DataType* Data = SafeLoad(Object);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

	#pragma endregion Load

		/**
		* Get Data with name DataName which implements the interface: DataType (NCsData::IData).
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* return				Data which implements the interface: DataType (NCsData::IData).	
		*/
		static DataType* GetChecked(const FString& Context, const UObject* WorldContext, const FName& DataName);

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
		FORCEINLINE static InterfaceType* GetChecked(const FString& Context, const UObject* WorldContext, const FName& DataName)
		{
			DataType* Data = GetChecked(Context, WorldContext, DataName);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* Safely get Data with name DataName which implements the interface: DataType (NCsData::IData).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* @param Log			(optional)
		* return				Data which implements the interface: DataType (NCsData::IData).
		*/
		static DataType* GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get Data with name DataName which implements the interface: InterfaceType.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* @param Log			(optional)
		* return				Data which implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			DataType* Data = GetSafe(Context, WorldContext, DataName, Log);

			if (!Data)
				return nullptr;

			InterfaceType* Other = GetSafeInterfaceChecked<InterfaceType>(Context, Data);

			if (!Other)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Data: %s does NOT implement the interface: %s."), *Context, *(DataName.ToString()), *(InterfaceType::Name.ToString())));
			}
			return Other;
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
		* Safely get the Data from Object.
		*  Data implements the interface: DataType (NCsData::IData).
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Data that implements the interface: DataType (NCsData::IData).
		*/
		static DataType* GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get the Data from Object.
		*  Data implements the interface: InterfaceType.
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Data that implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			DataType* Data = GetSafe(Context, Object, Log);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
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