// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_String.generated.h"
#pragma once

// Escape
#pragma region

UENUM(BlueprintType)
namespace ECsStringEscapeType
{
	enum Type
	{
		Int						UMETA(DisplayName = "Int"),
		Float					UMETA(DisplayName = "Float"),
		String					UMETA(DisplayName = "String"),
		CR						UMETA(DisplayName = "Carriage Return"),
		LF						UMETA(DisplayName = "Line Feed"),
		EOL						UMETA(DisplayName = "End of Line"),
		ECsStringEscapeType_MAX	UMETA(Hidden),
	};
}

#define ECS_STRING_ESCAPE_TYPE_MAX (uint8)ECsStringEscapeType::ECsStringEscapeType_MAX
typedef ECsStringEscapeType::Type TCsStringEscapeType;

namespace ECsStringEscapeType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString Int;
		extern const TCsString Float;
		extern const TCsString String;
		extern const TCsString CR;
		extern const TCsString LF;
		extern const TCsString EOL;
	}

	namespace Ref
	{
		extern const Type Int;
		extern const Type Float;
		extern const Type String;
		extern const Type CR;
		extern const Type LF;
		extern const Type EOL;
		extern const Type ECsStringEscapeType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Int) { return Str::Int.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::String) { return Str::String.Value; }
		if (EType == Type::CR) { return Str::CR.Value; }
		if (EType == Type::LF) { return Str::LF.Value; }
		if (EType == Type::EOL) { return Str::EOL.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::Int) { return Ref::Int; }
		if (InString == Str::Float) { return Ref::Float; }
		if (InString == Str::String) { return Ref::String; }
		if (InString == Str::CR) { return Ref::CR; }
		if (InString == Str::LF) { return Ref::LF; }
		if (InString == Str::EOL) { return Ref::EOL; }
		return Ref::ECsStringEscapeType_MAX;
	}
}

namespace ECsStringEscapeCharacter
{
	extern const FString Int;
	extern const FString Float;
	extern const FString String;
	extern const FString CR;
	extern const FString LF;
	extern const FString EOL;
}

#pragma endregion Escape

// World / Phrase / Sentence / Paragraph
#pragma region

UENUM(BlueprintType)
namespace ECsStringWordRule
{
	enum Type
	{
		MatchCase				UMETA(DisplayName = "MatchCase"),
		Lower					UMETA(DisplayName = "Lower"),
		ECsStringWordRule_MAX	UMETA(Hidden),
	};
}

#define ECS_STRING_WORD_RULE_MAX (uint8)ECsStringWordRule::ECsStringWordRule_MAX
typedef ECsStringWordRule::Type TCsStringWordRule;

namespace ECsStringWordRule
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString MatchCase;
		extern const TCsString Lower;
	}

	namespace Ref
	{
		extern const Type MatchCase;
		extern const Type Lower;
		extern const Type ECsStringWordRule_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::MatchCase) { return Str::MatchCase.Value; }
		if (EType == Type::Lower) { return Str::Lower.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::MatchCase) { return Ref::MatchCase; }
		if (InString == Str::Lower) { return Ref::Lower; }
		return Ref::ECsStringWordRule_MAX;
	}
}


USTRUCT(BlueprintType)
struct FCsStringWordInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	FString Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TEnumAsByte<ECsStringWordRule::Type> Rule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	FString Altered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TEnumAsByte<ECsStringEscapeType::Type> EscapeType;

	FCsStringWordInfo(){}
	FCsStringWordInfo(const FString &InValue, const TCsStringWordRule &InRule)
	{
		Value		= InValue;
		Rule		= InRule;
		Altered		= Rule == ECsStringWordRule::Lower ? Value.ToLower() : Value;
		EscapeType	= ECsStringEscapeType::ECsStringEscapeType_MAX;

		if (Value == ECsStringEscapeCharacter::Int)
			EscapeType = ECsStringEscapeType::Int;
		else
		if (Value == ECsStringEscapeCharacter::Float)
			EscapeType = ECsStringEscapeType::Float;
	}

	~FCsStringWordInfo(){}

	FCsStringWordInfo& operator=(const FCsStringWordInfo& B)
	{
		Value = B.Value;
		Rule = B.Rule;
		Altered = B.Altered;
		EscapeType = B.EscapeType;
		return *this;
	}

	bool operator==(const FCsStringWordInfo& B) const
	{
		return Value == B.Value && Rule == B.Rule && Altered == B.Altered && EscapeType == B.EscapeType;
	}

	bool operator!=(const FCsStringWordInfo& B) const
	{
		return !(*this == B);
	}

	operator FString() const
	{
		return Altered;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const FCsStringWordInfo &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsStringWordInfo &Lhs, const FString &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const FCsStringWordInfo &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsStringWordInfo &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}

	bool IsContainedBy(const FString &S)
	{
		if (EscapeType == ECsStringEscapeType::Int)
		{
			const int32 Int = FCString::Atoi(*S);
			const FString IntAsString = FString::FromInt(Int);
			return S.ToLower() == IntAsString.ToLower();
		}
		if (EscapeType == ECsStringEscapeType::Float)
		{
			const float Float = FCString::Atof(*S);
			const FString FloatAsString = FString::SanitizeFloat(Float);
			return S.ToLower() == FloatAsString.ToLower();
		}
		if (Rule == ECsStringWordRule::MatchCase)
			return S.Contains(Value);
		if (Rule == ECsStringWordRule::Lower)
			return S.ToLower().Contains(Value);
		return S.Contains(Value);
	}
};

USTRUCT(BlueprintType)
struct FCsStringWord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	bool Completed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TArray<FCsStringWordInfo> Ands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TArray<FCsStringWordInfo> Ors;

	FCsStringWord()
	{
		Completed = false;
	}
	~FCsStringWord(){}

	FCsStringWord& operator=(const FCsStringWord& B)
	{
		Completed = B.Completed;

		Ands.Reset();

		const int32 AndCount = B.Ands.Num();

		for (int32 I = 0; I < AndCount; ++I)
		{
			Ands.Add(B.Ands[I]);
		}

		Ors.Reset();

		const int32 OrCount = B.Ors.Num();

		for (int32 I = 0; I < OrCount; ++I)
		{
			Ors.Add(B.Ors[I]);
		}
		return *this;
	}

	bool operator==(const FCsStringWord& B) const
	{
		if (Completed != B.Completed)
			return false;

		if (Ands.Num() != B.Ands.Num())
			return false;

		const int32 AndCount = B.Ands.Num();

		for (int32 I = 0; I < AndCount; ++I)
		{
			if (Ands[I] != B.Ands[I])
				return false;
		}

		if (Ors.Num() != B.Ors.Num())
			return false;

		const int32 OrCount = B.Ors.Num();

		for (int32 I = 0; I < OrCount; ++I)
		{
			if (Ors[I] != B.Ors[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsStringWord& B) const
	{
		return !(*this == B);
	}

	void AddAnd(const FString &S, const TCsStringWordRule &Rule = ECsStringWordRule::MatchCase)
	{
		Ands.Add(FCsStringWordInfo(S, Rule));
	}

	void AddOr(const FString &S, const TCsStringWordRule &Rule = ECsStringWordRule::MatchCase)
	{
		Ors.Add(FCsStringWordInfo(S, Rule));
	}

	void Clear()
	{
		Completed = false;
	}

	void ProcessInput(const FString &Input)
	{
		int32 And = 0;
		bool Or = false;

		// Check And
		int32 AndCount = Ands.Num();

		for (int32 I = And; I < AndCount; ++I)
		{
			if (Ands[I] == ECsCachedString::Str::Empty || Ands[I].IsContainedBy(Input))
			{
				++And;
			}
		}
		// Check Or
		int32 OrCount = Ors.Num();

		for (int32 I = 0; I < OrCount; ++I)
		{
			Or |= (Ors[I] == ECsCachedString::Str::Empty || Ors[I].IsContainedBy(Input));

			if (Or )
				break;
		}
		Completed = (And > 0 && And == AndCount) || Or;
	}

	bool HasCompleted()
	{
		return Completed;
	}
};

USTRUCT(BlueprintType)
struct FCsStringPhrase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	bool Completed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TArray<FCsStringWord> Words;

	FCsStringPhrase()
	{
		Completed = false;
	}
	~FCsStringPhrase(){}

	FCsStringPhrase& operator=(const FCsStringPhrase& B)
	{
		Completed = B.Completed;

		Words.Reset();

		const int32 Count = B.Words.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Words.Add(B.Words[I]);
		}
		return *this;
	}

	bool operator==(const FCsStringPhrase& B) const
	{
		if (Completed != B.Completed)
			return false;

		if (Words.Num() != B.Words.Num())
			return false;

		const int32 Count = B.Words.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Words[I] != B.Words[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsStringPhrase& B) const
	{
		return !(*this == B);
	}

	void AddAndToWord(const int32 &Index, const FString &Word, const TCsStringWordRule &Rule = ECsStringWordRule::MatchCase)
	{
		const int32 Count = Words.Num();

		if (Index >= Count)
		{
			for (int32 I = 0; I < Index - Count + 1; ++I)
			{
				Words.Add(FCsStringWord());
			}
		}
		Words[Index].AddAnd(Word, Rule);
	}

	void AddOrToWord(const int32 &Index, const FString &Word, const TCsStringWordRule &Rule = ECsStringWordRule::MatchCase)
	{
		const int32 Count = Words.Num();

		if (Index >= Count)
		{
			for (int32 I = 0; I < Index - Count + 1; ++I)
			{
				Words.Add(FCsStringWord());
			}
		}
		Words[Index].AddOr(Word, Rule);
	}

	void Clear()
	{
		int32 Count = Words.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Words[I].Clear();
		}
		Completed = false;
	}

	void ProcessInput(const FString &Input)
	{
		// Check if ALL Words are Completed
		int32 Count = Words.Num();
		int32 Index = 0;

		for (Index = 0; Index < Count; ++Index)
		{
			if (Words[Index].HasCompleted())
				continue;

			Words[Index].ProcessInput(Input);

			if (Index < Count - 1 || !Words[Index].HasCompleted())
				break;
		}

		if (Index != Count)
			Clear();

		// Check if Completed
		if (Index > 0 && Index == Count)
		{
			Completed = true;
		}
	}

	bool HasCompleted()
	{
		return Completed;
	}
};

USTRUCT(BlueprintType)
struct FCsStringSentence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	bool Completed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TArray<FCsStringPhrase> Phrases;

	FCsStringSentence()
	{
		Completed = false;
	}
	~FCsStringSentence(){}

	FCsStringSentence& operator=(const FCsStringSentence& B)
	{
		Completed = B.Completed;

		Phrases.Reset();

		const int32 Count = B.Phrases.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Phrases.Add(B.Phrases[I]);
		}
		return *this;
	}

	bool operator==(const FCsStringSentence& B) const
	{
		if (Completed != B.Completed)
			return false;

		if (Phrases.Num() != B.Phrases.Num())
			return false;

		const int32 Count = B.Phrases.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Phrases[I] != B.Phrases[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsStringSentence& B) const
	{
		return !(*this == B);
	}

	void AddPhrase(const FCsStringPhrase &Phrase)
	{
		Phrases.Add(Phrase);
	}

	void Clear()
	{
		int32 Count = Phrases.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Phrases[I].Clear();
		}
		Completed = false;
	}

	void ProcessInput(const FString &Input)
	{
		if (Completed)
			return;

		// Check if ALL Phrases are Completed
		int32 Count = Phrases.Num();
		int32 Index = 0;

		for (Index = 0; Index < Count; ++Index)
		{
			if (Phrases[Index].HasCompleted())
				continue;

			Phrases[Index].ProcessInput(Input);

			if (Index < Count - 1 || !Phrases[Index].HasCompleted())
				break;
		}

		if (Index != Count)
			Clear();

		// Check if Completed
		if (Index == Count)
			Completed = true;
	}

	bool HasCompleted()
	{
		return Completed;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CgStringParagraph_CompletedEvent);

USTRUCT(BlueprintType)
struct FCsStringParagraph
{
	GENERATED_USTRUCT_BODY()

	DECLARE_MULTICAST_DELEGATE(FCompletedEvent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	bool Completed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TArray<FCsStringSentence> Sentences;

	FCompletedEvent Event;
	UPROPERTY(BlueprintAssignable, Category = "String")
	FBindableDynEvent_CgStringParagraph_CompletedEvent ScriptEvent;

	FCsStringParagraph()
	{
		Completed = false;
	}
	~FCsStringParagraph(){}

	FCsStringParagraph& operator=(const FCsStringParagraph& B)
	{
		Completed = B.Completed;

		Sentences.Reset();

		const int32 Count = B.Sentences.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Sentences.Add(B.Sentences[I]);
		}
		return *this;
	}

	bool operator==(const FCsStringParagraph& B) const
	{
		if (Completed != B.Completed)
			return false;

		if (Sentences.Num() != B.Sentences.Num())
			return false;

		const int32 Count = B.Sentences.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Sentences[I] != B.Sentences[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsStringParagraph& B) const
	{
		return !(*this == B);
	}

	void AddSentence(const FCsStringSentence &Sentence)
	{
		Sentences.Add(Sentence);
	}

	void Clear()
	{
		int32 Count = Sentences.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Sentences[I].Clear();
		}
		Completed = false;
	}

	void ProcessInput(const FString &Input)
	{
		if (Completed)
			return;

		// Check if ALL Sentences are Completed
		int32 Count = Sentences.Num();
		int32 Index = 0;

		for (Index = 0; Index < Count; ++Index)
		{
			if (Sentences[Index].HasCompleted())
				continue;

			Sentences[Index].ProcessInput(Input);

			if (Index < Count - 1 || !Sentences[Index].HasCompleted())
				break;
		}

		// Check if Completed
		if (Index == Count)
		{
			Completed = true;

			Event.Broadcast();
		}
	}

	bool HasCompleted()
	{
		return Completed;
	}
};

namespace CsStringParagraphHelper
{
	FCsStringSentence CreateOneWordSentence(const FString &Word, const TCsStringWordRule &Rule = ECsStringWordRule::MatchCase);
	FCsStringParagraph CreateOneWordParagraph(const FString &Word, const TCsStringWordRule &Rule = ECsStringWordRule::MatchCase);
}

#pragma endregion Word / Phrase / Sentence / Paragraph

struct CSCORE_API FCsStringHelper
{
public:
	static void GetLines(const FString& Input, TArray<FString> &OutLines);
	static void GetLineTerminatingIndexAndCharacter(const FString &Input, int32 &OutIndex, FString &OutEscapeChar);
};