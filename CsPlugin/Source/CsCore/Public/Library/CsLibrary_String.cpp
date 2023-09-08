// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_String.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsCached.h"

namespace NCsString
{
	namespace NCached
	{
		namespace Str
		{
			const FString Default__ = TEXT("Default__");
			const FString _C = TEXT("_C");
		}
	}

	// Stream
	#pragma region

	FString FLibrary::Stream_GetString(const TCHAR*& Str, bool IsLowerCase)
	{
		FString Arg;
		FParse::Token(Str, Arg, false);

		return IsLowerCase ? Arg.ToLower() : Arg;
	}

	FName FLibrary::Stream_GetName(const TCHAR*& Str)
	{
		return FName(*Stream_GetString(Str, false));
	}

	bool FLibrary::Stream_GetBool(const TCHAR*& Str)
	{
		FString Arg;
		FParse::Token(Str, Arg, false);

		const FString Bool = Arg.ToLower();

		if (Bool == TEXT("true") || Bool == TEXT("1"))
			return true;
		if (Bool == TEXT("false") || Bool == TEXT("0"))
			return false;
		return false;
	}

	int32 FLibrary::Stream_GetBoolAsInt(const TCHAR*& Str)
	{
		FString Arg = Stream_GetString(Str, true);

		if (Arg == TEXT("true") || Arg == TEXT("1"))
			return 1;
		if (Arg == TEXT("false") || Arg == TEXT("0"))
			return 0;
		return INDEX_NONE;
	}

	int32 FLibrary::Stream_GetInt(const TCHAR*& Str)
	{
		FString Arg;
		FParse::Token(Str, Arg, false);

		return FCString::Atoi(*Arg);
	}

	float FLibrary::Stream_GetFloat(const TCHAR*& Str)
	{
		FString Arg;
		FParse::Token(Str, Arg, false);

		return FCString::Atof(*Arg);
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, FString& OutValue, bool IsLowerCase)
	{
		if (FParse::Token(Str, OutValue, false))
		{
			if (IsLowerCase)
				OutValue = OutValue.ToLower();
			return true;
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, FName& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, false))
		{
			OutValue = FName(*OutString);
			return true;
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, bool& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, true))
		{
			if (OutString == NCsCached::Str::_true || OutString == NCsCached::Str::One)
			{
				OutValue = true;
				return true;
			}
			if (OutString == NCsCached::Str::_false || OutString == NCsCached::Str::Zero)
			{
				OutValue = false;
				return true;
			}
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, int32& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, false))
		{
			OutValue = FCString::Atoi(*OutString);

			return true;
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, uint32& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, false))
		{
			OutValue = (uint32)FMath::Abs(FCString::Atoi(*OutString));

			return true;
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, uint64& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, false))
		{
			uint64 Temp = FCString::Atoi64(*OutString);
			OutValue = Temp < 0ull ? 0ull : Temp;
			return true;
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, float& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, false))
		{
			OutValue = FCString::Atof(*OutString);

			return true;
		}
		return false;
	}

	bool FLibrary::Stream_GetValue(const TCHAR*& Str, FVector3f& OutValue)
	{
		return OutValue.InitFromString(FString(Str));
	}

	bool FLibrary::Stream_Get_bool_as_int32(const TCHAR*& Str, int32& OutValue)
	{
		FString OutString;

		if (Stream_GetValue(Str, OutString, true))
		{
			if (OutString == NCsCached::Str::_true || OutString == NCsCached::Str::One)
			{
				OutValue = 1;
				return true;
			}
			if (OutString == NCsCached::Str::_false || OutString == NCsCached::Str::Zero)
			{
				OutValue = 0;
				return true;
			}
		}
		return false;
	}

	#pragma endregion Stream

	// Bitfield
	#pragma region

	int32 FLibrary::CountOnes(const FString& Bitfield)
	{
		int32 Count	 = 0;
		const int32 Len = (uint32)Bitfield.Len();

		for (int32 I = 0; I < Len; ++I)
		{
			if (Bitfield[I] == '1')
				++Count;
		}
		return Count;
	}

	int32 FLibrary::CountZeros(const FString& Bitfield)
	{
		int32 Count		= 0;
		const int32 Len = Bitfield.Len();

		for (int32 I = 0; I < Len; ++I)
		{
			if (Bitfield[I] == '0')
				++Count;
		}
		return Count;
	}

	int32 FLibrary::CountOnesAndZeros(const FString& Bitfield)
	{
		int32 Count		= 0;
		const int32 Len = Bitfield.Len();

		for (int32 I = 0; I < Len; ++I)
		{
			if (Bitfield[I] == '0' || Bitfield[I] == '1')
				++Count;
		}
		return Count;
	}

	void FLibrary::GetBitfieldOrMask(const FString& A, const FString& B, FString& OutOrMask)
	{
		if (A.Len() != B.Len())
		{
			UE_LOG(LogCs, Warning, TEXT("NCsString::FLibrary::GetBitfieldOrMask: %s's Length != %s's Length (%d != %d)."), *A, *B, A.Len(), B.Len());
			return;
		}

		const int32 Len = A.Len();

		OutOrMask.Reserve(Len);

		for (int32 I = 0; I < Len; ++I)
		{
			if ((A[I] == '0' || A[I] == '1')
				&& B[I] == '0')
			{
				OutOrMask += '0';
			}

			if (A[I] == '0' && B[I] == '1')
			{
				OutOrMask += '1';
			}
		}
	}

	void FLibrary::CreateUnsetBitfield(FString& Bitfield, const int32& Length)
	{
		if (Length <= CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsString::FLibrary::CreateUnsetBitfield: Length: %d <= 0."), Length);
			return;
		}

		Bitfield.Reserve(Length);

		for (int32 I = 0; I < Length; ++I)
		{
			Bitfield += '0';
		}
	}

	void FLibrary::CreateSetBitfield(FString& Bitfield, const int32& Length)
	{
		if (Length <= CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsString::FLibrary::CreateSetBitfield: Length: %d <= 0."), Length);
			return;
		}

		Bitfield.Reserve(Length);

		for (int32 I = 0; I < Length; ++I)
		{
			Bitfield += '1';
		}
	}

	int32 FLibrary::SetBitfield(FString& Bitfield, const int32& Index /*=INDEX_NONE*/)
	{
		// All
		if (Index < 0)
		{
			const int32 Length = Bitfield.Len();
			int32 Zeros		   = 0;

			for (int32 I = 0; I < Length; ++I)
			{
				if (Bitfield[I] == '0')
				{
					++Zeros;
					Bitfield[I] = '1';
				}
			}
			return Zeros;
		}
		// Index
		else
		{
			if (Index >= Bitfield.Len())
			{
				UE_LOG(LogCs, Warning, TEXT("NCsString::FLibrary::SetBitfield: Index >= Bitfield.Len() (%d >= %d)."), Index, Bitfield.Len());
				return 0;
			}
		
			const int32 Zeros = Bitfield[Index] == '0' ? 1 : 0;
			Bitfield[Index]   = '1';

			return Zeros;
		}
		return 0;
	}

	int32 FLibrary::UnsetBitfield(FString& Bitfield, const int32& Index /*=INDEX_NONE*/)
	{
		// All
		if (Index < 0)
		{
			const int32 Length = Bitfield.Len();
			int32 Ones		   = 0;

			for (int32 I = 0; I < Length; ++I)
			{
				if (Bitfield[I] == '1')
				{
					++Ones;
					Bitfield[I] = '0';
				}
			}
			return Ones;
		}
		// Index
		else
		{
			if (Index >= Bitfield.Len())
			{
				UE_LOG(LogCs, Warning, TEXT("NCsString::FLibrary::UnsetBitfield: Index >= Bitfield.Len() (%d >= %d)."), Index, Bitfield.Len());
				return 0;
			}
		
			const int32 Ones = Bitfield[Index] == '1' ? 1 : 0;
			Bitfield[Index]   = '0';

			return Ones;
		}
		return 0;
	}

	void FLibrary::CopyBitfieldValues(const FString& From, FString& To)
	{
		const int32 Count = FMath::Min(From.Len(), To.Len());

		for (int32 I = 0; I < Count; ++I)
		{
			To[I] = From[I];
		}
	}

	void FLibrary::OrBitfieldValues(const FString& From, FString& To)
	{
		const int32 Count = FMath::Min(From.Len(), To.Len());

		for (int32 I = 0; I < Count; ++I)
		{
			if (From[I] == '1')
				To[I] = '1';
		}
	}

	bool FLibrary::AreAllOnes(const FString& Bitfield)
	{
		const int32 Length = Bitfield.Len();
		int32 Ones		   = 0;

		for (int32 I = 0; I < Length; ++I)
		{
			if (Bitfield[I] == '1')
				++Ones;
		}
		return Ones == Length;
	}

	bool FLibrary::AreAllZeros(const FString& Bitfield)
	{
		const int32 Length = Bitfield.Len();
		int32 Zeros		   = 0;

		for (int32 I = 0; I < Length; ++I)
		{
			if (Bitfield[I] == '0')
				++Zeros;
		}
		return Zeros == Length;
	}

	void FLibrary::AddZeros(FString& Bitfield, const int32& Count)
	{
		for (int32 I = 0; I < Count; ++I)
		{
			Bitfield += '0';
		}
	}

	#pragma endregion Bitfield

	// Default Object
	#pragma region

	bool FLibrary::RemoveDefaultObjectPrefix(FString& Str)
	{
		return Str.RemoveFromStart(NCached::Str::Default__);
	}

	#pragma endregion Default Object

	// Class
	#pragma region

	bool FLibrary::RemoveClassSuffix(FString& Str)
	{
		return Str.RemoveFromEnd(NCached::Str::_C);
	}

	#pragma endregion Class
}