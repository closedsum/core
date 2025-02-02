// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Data
#include "Data/ICsData.h"
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsDataLog.h"

namespace NCsData
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSDATA_API const FString SafeLoad;
			}
		}
	}

	/**
	*/
	struct CSDATA_API FLibrary : public NCsInterfaceMap::TLibrary<CsDataType>
	{
		CS_DECLARE_STATIC_LOG_LEVEL

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

		/**
		* Print out Object as 'Data: %s with Class: %s'.
		* 
		* @param Object	Object to print.
		* return		String in the format: 'Object: %s with Class: %s'.
		*/
		static FString PrintDataAndClass(UObject* Object);

		/**
		* Print out Data as 'Data: %s with Class: %s'.
		* 
		* @param Data	Data to print.
		* return		String in the formate: 'Object: %s with Class: %s'.
		*/
		static FString PrintDataAndClass(ICsData* Data);

	// Convert
	#pragma region
	public:

		static CsDataType* ConvertChecked(const FString& Context, UObject* Object);

		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* ConvertChecked(const FString& Context, UObject* Object)
		{
			return GetInterfaceChecked<InterfaceType>(Context, ConvertChecked(Context, Object));
		}

		static CsDataType* SafeConvert(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* SafeConvert(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			if (CsDataType* Data = SafeConvert(Context, Object, Log))
				return GetSafeInterfaceChecked<InterfaceType>(Context, Data);
			return nullptr;
		}

	#pragma endregion Convert

	// Load
	#pragma region
	public:

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: CsDataType (NCsData::IData).
		* 
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* @param Log		Log function.
		* return			Loaded object of type: CsDataType (NCsData::IData).
		*/
		static CsDataType* SafeLoad(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
		FORCEINLINE static InterfaceType* SafeLoad(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			CsDataType* Data = SafeLoad(Context, Object, Log);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		* Safely load the Data from Object.
		*  Data implements the interface: CsDataType (NCsData::IData).
		*
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Loaded object of type: CsDataType (NCsData::IData).
		*/
		static CsDataType* SafeLoad(UObject* Object);

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
			using namespace NCsData::NLibrary::NCached;

			const FString& Context = Str::SafeLoad;

			CsDataType* Data = SafeLoad(Object);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		static const CsDataType* TopLoadChecked(const FString& Context, UObject* Object);

		template<typename InterfaceType>
		FORCEINLINE static const InterfaceType* TopLoadChecked(const FString& Context, UObject* Object)
		{
			return GetInterfaceChecked<InterfaceType>(Context, TopLoadChecked(Context, Object));
		}

		static const CsDataType* SafeTopLoad(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		template<typename InterfaceType>
		static const InterfaceType* SafeTopLoad(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			if (const CsDataType* Data = SafeTopLoad(Context, Object, Log))
			{
				if (const InterfaceType* Interface = GetSafeInterfaceChecked<InterfaceType>(Context, Data))
					return Interface;

				if (Log)
				{
					Log(FString::Printf(TEXT("%s: %s does NOT implement the interface: %s."), *Context, *PrintDataAndClass(Object), *(InterfaceType::Name.ToString())));
				}
			}
			return nullptr;
		}

		static void UnloadChecked(const FString& Context, UObject* Object);

		static void Script_UnloadChecked(const FString& Context, UObject* Object);

	#pragma endregion Load

	// ICsScriptData
	#pragma region
	public:

		/**
		* Call the method Script_Load for Object.
		*  Object MUST implement the interface: ICsScriptData
		* 
		* @param Context	The calling context.
		* @param Object
		* @param LoadFlags
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			Whether the Load was successful or not.			
		*/
		static bool SafeScript_Load(const FString& Context, UObject* Object, const int32& LoadFlags, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static bool SafeScript_Load(const FString& Context, UObject* Object, const int32& LoadFlags, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			bool OutSuccess = false;
			return SafeScript_Load(Context, Object, LoadFlags, OutSuccess, Log);
		}

		/**
		* Call the method Script_Load for the Default Object loaded from Path.
		*  Object MUST implement the interface: ICsScriptData
		* 
		* @param Context	The calling context.
		* @param Path
		* @param LoadFlags
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			Object that implements the interface: ICsScriptData		
		*/
		static UObject* SafeScript_Load(const FString& Context, const FString& Path, const int32& LoadFlags, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static UObject* SafeScript_Load(const FString& Context, const FString& Path, const int32& LoadFlags, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			bool OutSuccess = false;
			return SafeScript_Load(Context, Path, LoadFlags, OutSuccess, Log);
		}

	#pragma endregion ICsScriptData

	// Implement
	#pragma region
	public:

		static bool ScriptImplementsChecked(const FString& Context, const UObject* Object);

		static bool SafeScriptImplements(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static bool ImplementsChecked(const FString& Context, const UObject* Object);

		static bool SafeImplements(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static bool SafeImplements(const UObject* Object);

	#pragma endregion Implment

	// Get
	#pragma region
	public:

		/**
		* Get Data with name DataName which implements the interface: CsDataType (NCsData::IData).
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* return				Data which implements the interface: CsDataType (NCsData::IData).	
		*/
		static CsDataType* GetChecked(const FString& Context, const UObject* WorldContext, const FName& DataName);

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
			CsDataType* Data = GetChecked(Context, WorldContext, DataName);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* Safely get Data with name DataName which implements the interface: CsDataType (NCsData::IData).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the data to get. This is the EntryName in Manager_Data.
		* @param Log			(optional)
		* return				Data which implements the interface: CsDataType (NCsData::IData).
		*/
		static CsDataType* GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
		FORCEINLINE static InterfaceType* GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			CsDataType* Data = GetSafe(Context, WorldContext, DataName, Log);

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
		* Get Data from Object which implements the interface: CsDataType (NCsData::IData).
		* 
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Object that implements the interface: CsDataType (NCsData::IData).
		*/
		static CsDataType* GetChecked(const FString& Context, UObject* Object);

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
			CsDataType* Data = GetChecked(Context, Object);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		/**
		* Safely get the Data from Object.
		*  Data implements the interface: CsDataType (NCsData::IData).
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Data that implements the interface: CsDataType (NCsData::IData).
		*/
		static CsDataType* GetSafe(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		/**
		* Safely get the Data from Object.
		*  Data implements the interface: InterfaceType.
		*
		* @param Context	The calling context.
		* @param Object		UObject that SHOULD implement the interface: ICsData.
		* return			Data that implements the interface: InterfaceType.
		*/
		template<typename InterfaceType>
		FORCEINLINE static InterfaceType* GetSafe(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			CsDataType* Data = GetSafe(Context, Object, Log);

			return Data ? GetSafeInterfaceChecked<InterfaceType>(Context, Data) : nullptr;
		}

		/**
		* Get the underlying data that implements the interface: CsDataType (NCsData::IData)
		* from the UObject, UData, which implements the interface: ICsData.
		* 
		* @param Context	The calling context.
		* @param Data		UObject that implements the interface: ICsData.
		* return			Object that implements the interface: CsDataType (NCsData::IData).
		*/
		static CsDataType* GetChecked(const FString& Context, ICsData* UData);

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
			CsDataType* Data = GetChecked(Context, UData);

			return GetInterfaceChecked<InterfaceType>(Context, Data);
		}

		// Script
	#pragma region
	public:

		/**
		* Get Script Data with name DataName which implements the interface: ICsScriptData.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the Script Data to get. This is the EntryName in Manager_Data.
		* return				Script Data which implements the interface: ICsScriptData.	
		*/
		static UObject* GetScriptChecked(const FString& Context, const UObject* WorldContext, const FName& DataName);

		/**
		* Safely get Script Data with name DataName which implements the interface: ICsScriptData.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has a reference to a UWorld (GetWorld() is Valid).
		*						Used to route to Manager_Data.
		* @param DataName		Name of the Script Data to get. This is the EntryName in Manager_Data.
		* @param Log			(optional)
		* return				Script Data which implements the interface: ICsScriptData.
		*/
		static UObject* GetSafeScript(const FString& Context, const UObject* WorldContext, const FName& DataName, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

	#pragma endregion Script

	#pragma endregion Get
	};
}

using CsDataLibrary = NCsData::FLibrary;