// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_String.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_String)

// StringEscapeType
#pragma region

EMCsStringEscapeType* EMCsStringEscapeType::Instance;

EMCsStringEscapeType& EMCsStringEscapeType::Get()
{
	if (!Instance)
		Instance = new EMCsStringEscapeType();
	return *Instance;
}

namespace NCsStringEscapeType
{
	namespace Ref
	{
		CSTYPES_API const Type Int = EMCsStringEscapeType::Get().Add(Type::Int, TEXT("Int"));
		CSTYPES_API const Type Float = EMCsStringEscapeType::Get().Add(Type::Float, TEXT("Float"));
		CSTYPES_API const Type String = EMCsStringEscapeType::Get().Add(Type::String, TEXT("String"));
		CSTYPES_API const Type CR = EMCsStringEscapeType::Get().Add(Type::CR, TEXT("CR"), TEXT("Carriage Return"));
		CSTYPES_API const Type LF = EMCsStringEscapeType::Get().Add(Type::LF, TEXT("LF"), TEXT("Line Feed"));
		CSTYPES_API const Type EOL = EMCsStringEscapeType::Get().Add(Type::EOL, TEXT("End of Line"));
		CSTYPES_API const Type ECsStringEscapeType_MAX = EMCsStringEscapeType::Get().Add(Type::ECsStringEscapeType_MAX, TEXT("ECsStringEscapeType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion StringEscapeType

// StringCompare
#pragma region

namespace NCsStringCompare
{
	namespace Ref
	{
		CSTYPES_API const Type Equals = EMCsStringCompare::Get().Add(Type::Equals, TEXT("Equals"));
		CSTYPES_API const Type StartsWith = EMCsStringCompare::Get().Add(Type::StartsWith, TEXT("Starts With"));
		CSTYPES_API const Type EndsWith = EMCsStringCompare::Get().Add(Type::EndsWith, TEXT("Ends With"));
		CSTYPES_API const Type Contains = EMCsStringCompare::Get().Add(Type::Contains, TEXT("Contains"));
		CSTYPES_API const Type ECsStringCompare_MAX = EMCsStringCompare::Get().Add(Type::ECsStringCompare_MAX, TEXT("ECsStringCompare_MAX"), TEXT("MAX"));
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsStringCompare_MAX;
}
#pragma endregion StringCompare

// StringWordRule
#pragma region

EMCsStringWordRule* EMCsStringWordRule::Instance;

EMCsStringWordRule& EMCsStringWordRule::Get()
{
	if (!Instance)
		Instance = new EMCsStringWordRule();
	return *Instance;
}

namespace NCsStringWordRule
{
	namespace Ref
	{
		CSTYPES_API const Type MatchCase = EMCsStringWordRule::Get().Add(Type::MatchCase, TEXT("MatchCase"), TEXT("Match Case"));
		CSTYPES_API const Type Lower = EMCsStringWordRule::Get().Add(Type::Lower, TEXT("Lower"));
		CSTYPES_API const Type ECsStringWordRule_MAX = EMCsStringWordRule::Get().Add(Type::ECsStringWordRule_MAX, TEXT("ECsStringWordRule_MAX"), TEXT("MAX"));
	}
}

namespace NCsStringEscapeCharacter
{
	CSTYPES_API const FString Int = TEXT("%d");
	CSTYPES_API const FString Float = TEXT("%f");
	CSTYPES_API const FString String = TEXT("%s");
	CSTYPES_API const FString CR = TEXT("\r");
	CSTYPES_API const FString LF = TEXT("\n");
	CSTYPES_API const FString EOL = TEXT("\r\n");
}

#pragma endregion StringWordRule

// Word / Phrase / Sentence / Paragraph
#pragma region

FCsStringSentence NCsStringParagraphHelper::CreateOneWordSentence(const FString &Word, const ECsStringWordRule &Rule)
{
	FCsStringSentence Sentence;
	FCsStringPhrase Phrase;
	Phrase.AddAndToWord(0, Word, Rule);
	Sentence.AddPhrase(Phrase);

	return Sentence;
}

FCsStringParagraph NCsStringParagraphHelper::CreateOneWordParagraph(const FString &Word, const ECsStringWordRule &Rule)
{
	FCsStringParagraph Paragraph;
	FCsStringSentence Sentence;
	FCsStringPhrase Phrase;
	Phrase.AddAndToWord(0, Word, Rule);
	Sentence.AddPhrase(Phrase);
	Paragraph.AddSentence(Sentence);

	return Paragraph;
}

#pragma endregion Word / Phrase / Sentence / Paragraph

// FCsStringHelper
#pragma region

void FCsStringHelper::GetLines(const FString& Input, TArray<FString> &OutLines)
{
	int32 Index = INDEX_NONE;
	FString EscapeChar = TEXT("");

	GetLineTerminatingIndexAndCharacter(Input, Index, EscapeChar);

	int32 EscapeLen = EscapeChar.Len();
	int32 Start = 0;

	while (Index != INDEX_NONE)
	{
		OutLines.Add(Input.Mid(Start, Index));

		Start			 += Index + EscapeLen;
		FString Remaining = Input.Mid(Start);

		GetLineTerminatingIndexAndCharacter(Remaining, Index, EscapeChar);

		if (Index == INDEX_NONE)
		{
			Remaining.RemoveFromEnd(EscapeChar);
			OutLines.Add(Remaining);
			break;
		}
	}
}

void FCsStringHelper::GetLineTerminatingIndexAndCharacter(const FString &Input, int32 &OutIndex, FString &OutEscapeChar)
{
	OutIndex = INDEX_NONE;
	OutEscapeChar = TEXT("");

	TArray<FString> Chars;

	static const uint8 ESCAPE_COUNT = 3;
	static const uint8 EOL = 0;
	static const uint8 CR = 1;
	static const uint8 LF = 2;

	Chars.SetNum(ESCAPE_COUNT);
	Chars[EOL] = NCsStringEscapeCharacter::EOL;
	Chars[CR] = NCsStringEscapeCharacter::CR;
	Chars[LF] = NCsStringEscapeCharacter::LF;

	const int32 Count = Chars.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutIndex = Input.Find(Chars[I]);

		if (OutIndex != INDEX_NONE)
		{
			OutEscapeChar = Chars[I];
			break;
		}
	}
}

#pragma endregion FCsStringHelper