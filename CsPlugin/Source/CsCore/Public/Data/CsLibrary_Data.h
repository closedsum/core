// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

class ICsData;

namespace NCsData
{
	/**
	*/
	struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<IData>
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

		static FString PrintObjectAndClass(UObject* Object);

		/**
		*/
		static FString PrintObjectAndClass(ICsData* Data, const FString& MemberName);
		
		/**
		*/
		static FString PrintObjectAndClass(ICsData* Data);

		static IData* SafeLoadData(const FString& Context, UObject* Object);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* SafeLoadData(const FString& Context, UObject* Object)
		{
			IData* Data = SafeLoadData(Context, Object);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		*
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Object that implements the interface: NCsData::IData.
		*/
		static IData* GetSafeData(const FString& Context, UObject* Object);

		/**
		*
		*
		* @param Context		The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetSafeData(const FString& Context, UObject* Object)
		{
			IData* Data = GetSafeData(Context, Object);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		* Get Data with name DataName which implements the interface: NCsData::IData.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* return
		*/
		static IData* GetDataChecked(const FString& Context, UObject* WorldContext, const FName& DataName);

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* return
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetDataChecked(const FString& Context, UObject* WorldContext, const FName& DataName)
		{
			IData* Data = GetDataChecked(Context, WorldContext, DataName);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* 
		* 
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Object that implements the interface: NCsData::IData.
		*/
		static IData* GetDataChecked(const FString& Context, UObject* Object);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Data		UObject that SHOULD implement the interface: ICsData.
		* return			Object that implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetDataChecked(const FString& Context, UObject* Object)
		{
			IData* Data = GetDataChecked(Context, Object);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* Get the underlying data that implements the interface: NCsData::IData
		* from the UObject, UData, which implements the interface: ICsData.
		* 
		* @param Context	The calling context.
		* @param Data		UObject that implements the interface: ICsData.
		* return			Object that implements the interface: NCsData::IData.
		*/
		static IData* GetDataChecked(const FString& Context, ICsData* UData);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Data
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetDataChecked(const FString& Context, ICsData* UData)
		{
			IData* Data = GetDataChecked(Context, UData);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}
	};
}