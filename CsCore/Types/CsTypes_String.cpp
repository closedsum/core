// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_String.h"

// StringEscapeType

EMCsStringEscapeType* EMCsStringEscapeType::Instance;

EMCsStringEscapeType& EMCsStringEscapeType::Get()
{
	if (!Instance)
		Instance = new EMCsStringEscapeType();
	return *Instance;
}

namespace ECsStringEscapeType
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

// StringWordRule

EMCsStringWordRule* EMCsStringWordRule::Instance;

EMCsStringWordRule& EMCsStringWordRule::Get()
{
	if (!Instance)
		Instance = new EMCsStringWordRule();
	return *Instance;
}

namespace ECsStringWordRule
{
	namespace Ref
	{
		CSCORE_API const Type MatchCase = EMCsStringWordRule::Get().Add(Type::MatchCase, TEXT("MatchCase"), TEXT("Match Case"));
		CSCORE_API const Type Lower = EMCsStringWordRule::Get().Add(Type::Lower, TEXT("Lower"));
		CSCORE_API const Type ECsStringWordRule_MAX = EMCsStringWordRule::Get().Add(Type::ECsStringWordRule_MAX, TEXT("ECsStringWordRule_MAX"), TEXT("MAX"));
	}
}

namespace ECsStringEscapeCharacter
{
	CSCORE_API const FString Int = TEXT("%d");
	CSCORE_API const FString Float = TEXT("%f");
	CSCORE_API const FString String = TEXT("%s");
	CSCORE_API const FString CR = TEXT("\r");
	CSCORE_API const FString LF = TEXT("\n");
	CSCORE_API const FString EOL = TEXT("\r\n");
}

// Word / Phrase / Sentence / Paragraph
#pragma region

FCsStringSentence CsStringParagraphHelper::CreateOneWordSentence(const FString &Word, const TCsStringWordRule &Rule)
{
	FCsStringSentence Sentence;
	FCsStringPhrase Phrase;
	Phrase.AddAndToWord(0, Word, Rule);
	Sentence.AddPhrase(Phrase);

	return Sentence;
}

FCsStringParagraph CsStringParagraphHelper::CreateOneWordParagraph(const FString &Word, const TCsStringWordRule &Rule)
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
	FString EscapeChar = ECsCached::Str::Empty;

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
	OutEscapeChar = ECsCached::Str::Empty;

	TArray<FString> Chars;

	const uint8 ESCAPE_COUNT = 3;
	const uint8 EOL = 0;
	const uint8 CR = 1;
	const uint8 LF = 2;

	Chars.SetNum(ESCAPE_COUNT);
	Chars[EOL] = ECsStringEscapeCharacter::EOL;
	Chars[CR] = ECsStringEscapeCharacter::CR;
	Chars[LF] = ECsStringEscapeCharacter::LF;

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