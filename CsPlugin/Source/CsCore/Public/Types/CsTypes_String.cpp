// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_String.h"

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
		CSCORE_API const Type Int = EMCsStringEscapeType::Get().Add(Type::Int, TEXT("Int"));
		CSCORE_API const Type Float = EMCsStringEscapeType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type String = EMCsStringEscapeType::Get().Add(Type::String, TEXT("String"));
		CSCORE_API const Type CR = EMCsStringEscapeType::Get().Add(Type::CR, TEXT("CR"), TEXT("Carriage Return"));
		CSCORE_API const Type LF = EMCsStringEscapeType::Get().Add(Type::LF, TEXT("LF"), TEXT("Line Feed"));
		CSCORE_API const Type EOL = EMCsStringEscapeType::Get().Add(Type::EOL, TEXT("End of Line"));
		CSCORE_API const Type ECsStringEscapeType_MAX = EMCsStringEscapeType::Get().Add(Type::ECsStringEscapeType_MAX, TEXT("ECsStringEscapeType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion StringEscapeType

// StringCompare
#pragma region

namespace NCsStringCompare
{
	namespace Ref
	{
		CSCORE_API const Type Equals = EMCsStringCompare::Get().Add(Type::Equals, TEXT("Equals"));
		CSCORE_API const Type StartsWith = EMCsStringCompare::Get().Add(Type::StartsWith, TEXT("Starts With"));
		CSCORE_API const Type EndsWith = EMCsStringCompare::Get().Add(Type::EndsWith, TEXT("Ends With"));
		CSCORE_API const Type Contains = EMCsStringCompare::Get().Add(Type::Contains, TEXT("Contains"));
		CSCORE_API const Type ECsStringCompare_MAX = EMCsStringCompare::Get().Add(Type::ECsStringCompare_MAX, TEXT("ECsStringCompare_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsStringCompare_MAX;
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
		CSCORE_API const Type MatchCase = EMCsStringWordRule::Get().Add(Type::MatchCase, TEXT("MatchCase"), TEXT("Match Case"));
		CSCORE_API const Type Lower = EMCsStringWordRule::Get().Add(Type::Lower, TEXT("Lower"));
		CSCORE_API const Type ECsStringWordRule_MAX = EMCsStringWordRule::Get().Add(Type::ECsStringWordRule_MAX, TEXT("ECsStringWordRule_MAX"), TEXT("MAX"));
	}
}

namespace NCsStringEscapeCharacter
{
	CSCORE_API const FString Int = TEXT("%d");
	CSCORE_API const FString Float = TEXT("%f");
	CSCORE_API const FString String = TEXT("%s");
	CSCORE_API const FString CR = TEXT("\r");
	CSCORE_API const FString LF = TEXT("\n");
	CSCORE_API const FString EOL = TEXT("\r\n");
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
	FString EscapeChar = NCsCached::Str::Empty;

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
	OutEscapeChar = NCsCached::Str::Empty;

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