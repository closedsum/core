// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "CsLibrary_String.generated.h"

UCLASS()
class CSCORE_API UCsLibrary_String : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	// Stream
#pragma region

	static FString Stream_GetString(const TCHAR*& Str, bool IsLowerCase);
	static FName Stream_GetName(const TCHAR*& Str);
	static bool Stream_GetBool(const TCHAR*& Str);
	static int32 Stream_GetBoolAsInt(const TCHAR*& Str);
	static int32 Stream_GetInt(const TCHAR*& Str);
	static float Stream_GetFloat(const TCHAR*& Str);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* @param IsLowerCase
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, FString& OutValue, bool IsLowerCase);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, FName& OutValue);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, bool& OutValue);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, int32& OutValue);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, uint32& OutValue);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, uint64& OutValue);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_GetValue(const TCHAR*& Str, float& OutValue);

	/**
	*
	*
	* @param Str
	* @param OutValue
	* return
	*/
	static bool Stream_Get_bool_as_int32(const TCHAR*& Str, int32& OutValue);

#pragma endregion Stream

	// Bitfield
#pragma region
public:

	/**
	* Count the number of '1's in the string Str.
	*
	* @param Bitfield	Ideally of '1's and / or '0's.
	* return			Number of '1's found.
	*/
	static int32 CountOnes(const FString& Bitfield);

	/**
	* Count the number of '0's in the string Str.
	*
	* @param Bitfield	Ideally of '1's and / or '0's.
	* return			Number of '0's found.
	*/
	static int32 CountZeros(const FString& Bitfield);

	/**
	* Count the number of '1's and '0's in the string Str.
	*
	* @param Bitfield	Ideally of '1's and / or '0's.
	* return			Number of '1's and '0's found.
	*/
	static int32 CountOnesAndZeros(const FString& Bitfield);

	/**
	* Get the Mask such that A | Mask == A | B.
	*
	* @param A			A string (ideally of '1's and / or '0's).
	* @param B			A string (ideally of '1's and / or '0's).
	* @param OutOrMask	String of '1's or '0's that satisfies the
						condidtion A | Mask == A | B.
	*/
	static void GetBitfieldOrMask(const FString& A, const FString& B, FString& OutOrMask);

	/**
	* Create a string of '0's of size Length.
	* i.e. for Length = 4 the string would be "0000".
	*
	* @param Bitfield	A string.
	* @param Length		Size of the string of '0's to create.
	*/
	static void CreateUnsetBitfield(FString& Bitfield, const int32& Length);

	/**
	* Create a string of '1's of size Length.
	* i.e. for Length = 4 the string would be "1111".
	*
	* @param Bitfield	A string.
	* @param Length		Size of the string of '1's to create.
	*/
	static void CreateSetBitfield(FString& Bitfield, const int32& Length);

	/**
	* Set any '0's in the string Bitfield to '1'.
	*
	* @param Bitfield	A string of '1's and / or '0's
	* @param Index		The index in the Bitfield string to change
						to '1'. If Index < 0, set all '0's to '1's.
	* return			Number of '0's that changed to '1's
	*/
	static int32 SetBitfield(FString& Bitfield, const int32& Index = INDEX_NONE);

	/**
	* Set any '1's in the string Bitfield to '0'.
	*
	* @param Bitfield	A string of '1's and / or '0's
	* @param Index		The index in the Bitfield string to change
						to '0'. If Index < 0, set all '1's to '0's.
	* return			Number of '1's that changed to '0's
	*/
	static int32 UnsetBitfield(FString& Bitfield, const int32& Index = INDEX_NONE);

	/**
	* Copy string From to To.
	*
	* @param From
	* @param To
	*/
	static void CopyBitfieldValues(const FString& From, FString& To);

	/**
	* Or Bitfield string To with From.
	*
	* @param From
	* @param To
	*/
	static void OrBitfieldValues(const FString& From, FString& To);

	/**
	*
	*
	* @param Bitfield
	* return
	*/
	static bool AreAllOnes(const FString& Bitfield);

	/**
	*
	*
	* @param Bitfield
	* return
	*/
	static bool AreAllZeros(const FString& Bitfield);

	/**
	*
	*
	* @param Bitfield
	* @param Count
	*/
	static void AddZeros(FString& Bitfield, const int32& Count);

#pragma endregion Bitfield

	// Default Object
#pragma region
public:

	/**
	*
	*
	* @param Str
	* return
	*/
	static bool RemoveDefaultObjectPrefix(FString& Str);

#pragma endregion Default Object

	// Class
#pragma region
public:

	/**
	*
	*
	* @param Str
	* return
	*/
	static bool RemoveClassSuffix(FString& Str);

#pragma endregion Class
};