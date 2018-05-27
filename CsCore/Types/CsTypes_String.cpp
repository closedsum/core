// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_String.h"

namespace ECsStringEscapeType
{
	namespace Str
	{
		const TCsString Int = TCsString(TEXT("Int"), TEXT("int"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		const Type Int = Type::Int;
		const Type Float = Type::Float;
		const Type String = Type::String;
		const Type ECsStringEscapeType_MAX = Type::ECsStringEscapeType_MAX;
	}
}

namespace ECsStringWordRule
{
	namespace Str
	{
		const TCsString MatchCase = TCsString(TEXT("MatchCase"), TEXT("matchcase"));
		const TCsString Lower = TCsString(TEXT("Lower"), TEXT("lower"));
	}

	namespace Ref
	{
		const Type MatchCase = Type::MatchCase;
		const Type Lower = Type::Lower;
		const Type ECsStringWordRule_MAX = Type::ECsStringWordRule_MAX;
	}
}

namespace ECsStringEscapeCharacter
{
	const FString Int = TEXT("%d");
	const FString Float = TEXT("%f");
	const FString String = TEXT("%s");
	const FString CR = TEXT("\r");
	const FString LF = TEXT("\n");
	const FString EOL = TEXT("\r\n");
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