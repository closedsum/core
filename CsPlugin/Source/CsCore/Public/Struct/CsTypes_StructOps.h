// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// IsValid
#pragma region

// Assume Function Signature bool(void* StructValue, const UStruct* Struct, const FString& Context)
#define CS_STRUCT_OPS_IS_VALID_CHECKED(__StructType) FORCEINLINE static bool StructOps_IsValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess) \
	{ \
		OutSuccess = false; \
		\
		if (!StructValue) \
			return false; \
		\
		checkf(Struct, TEXT("%s::StructOps_IsValidChecked: Struct is NULL."), *(__StructType::StaticStruct()->GetName())); \
		\
		if (Struct == __StructType::StaticStruct()) \
		{ \
			reinterpret_cast<__StructType*>(StructValue)->IsValidChecked(Context); \
			OutSuccess = true; \
			return true; \
		} \
		return false; \
	}
// Assume Function Signature bool(void* StructValue, const UStruct* Struct, const FString& Context, void(*Log)(const FString&))
#define CS_STRUCT_OPS_IS_VALID(__StructType) FORCEINLINE static bool StructOps_IsValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&)) \
	{ \
		OutSuccess = false; \
		\
		if (!StructValue) \
			return false; \
		\
		checkf(Struct, TEXT("%s::StructOps_IsValid: Struct is NULL."), *(__StructType::StaticStruct()->GetName())); \
		\
		if (Struct == __StructType::StaticStruct()) \
		{ \
			reinterpret_cast<__StructType*>(StructValue)->IsValid(Context, Log); \
			OutSuccess = true; \
			return true; \
		} \
		return false; \
	}
// Assume Function Signature bool(void* StructValue, const UStruct* Struct, const FString& Context)
#define CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(__StructType) FORCEINLINE static bool StructOps_IsTopValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess) \
	{ \
		OutSuccess = false; \
		\
		if (!StructValue) \
			return false; \
		\
		checkf(Struct, TEXT("%s::StructOps_IsTopValidChecked: Struct is NULL."), *(__StructType::StaticStruct()->GetName())); \
		\
		if (Struct == __StructType::StaticStruct()) \
		{ \
			reinterpret_cast<__StructType*>(StructValue)->IsTopValidChecked(Context); \
			OutSuccess = true; \
			return true; \
		} \
		return false; \
	}
// Assume Function Signature bool(void* StructValue, const UStruct* Struct, const FString& Context, void(*Log)(const FString&))
#define CS_STRUCT_OPS_IS_TOP_VALID(__StructType) FORCEINLINE static bool StructOps_IsTopValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&)) \
	{ \
		OutSuccess = false; \
		\
		if (!StructValue) \
			return false; \
		\
		checkf(Struct, TEXT("%s::StructOps_IsTopValid: Struct is NULL."), *(__StructType::StaticStruct()->GetName())); \
		\
		if (Struct == __StructType::StaticStruct()) \
		{ \
			reinterpret_cast<__StructType*>(StructValue)->IsTopValid(Context, Log); \
			OutSuccess = true; \
			return true; \
		} \
		return false; \
	}

#pragma endregion IsValid

// Data
#pragma region

// Assume Function Signature bool(void* StructValue, const UStruct* Struct)
#define CS_STRUCT_OPS_DATA_UNLOAD(__StructType) FORCEINLINE static bool StructOps_Data_Unload(void* StructValue, const UStruct* Struct) \
	{ \
		if (!StructValue) \
			return false; \
		\
		checkf(Struct, TEXT("%s::StructOps_Data_Unload: Struct is NULL."), *(__StructType::StaticStruct()->GetName())); \
		\
		if (Struct == __StructType::StaticStruct()) \
		{ \
			reinterpret_cast<__StructType*>(StructValue)->Unload(); \
			return true; \
		} \
		return false; \
	}

#pragma endregion Data