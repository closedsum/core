namespace CgCore
{
    using System;
    using System.Collections.Generic;

    public enum ECgStringEscapeType : byte
    {
        Int,
        Float,
        String,
        MAX
    }

    public enum ECgStringWordRule : byte
    {
        MatchCase,
        Lower,
        MAX
    }

    public struct FCgStringWordInfo
    {
        private static readonly string ESCAPE_INT = "%d";
        private static readonly string ESCAPE_FLOAT = "%f";

        private string Value;
        private ECgStringWordRule Rule;
        private string Altered;
        private ECgStringEscapeType EscapeType;

        public FCgStringWordInfo(string val, ECgStringWordRule rule)
        {
            Value = val;
            Rule = rule;
            Altered = Rule == ECgStringWordRule.Lower ? Value.ToLower() : Value;
            EscapeType = ECgStringEscapeType.MAX;

            if (Value == ESCAPE_INT)
                EscapeType = ECgStringEscapeType.Int;
            else
            if (Value == ESCAPE_FLOAT)
                EscapeType = ECgStringEscapeType.Float;
        }

        public static implicit operator string(FCgStringWordInfo w)
        {
            return w.Altered;
        }

        public static bool operator ==(FCgStringWordInfo lhs, FCgStringWordInfo rhs)
        {
            return lhs.Value == rhs.Value && lhs.Rule == rhs.Rule && lhs.Altered == rhs.Altered;
        }

        public static bool operator !=(FCgStringWordInfo lhs, FCgStringWordInfo rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(FCgStringWordInfo lhs, string rhs)
        {
            return lhs.Value == rhs;
        }

        public static bool operator !=(FCgStringWordInfo lhs, string rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(string lhs, FCgStringWordInfo rhs)
        {
            return lhs == rhs.Value;
        }

        public static bool operator !=(string lhs, FCgStringWordInfo rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgStringWordInfo))
                return false;

            FCgStringWordInfo rhs = (FCgStringWordInfo)obj;

            if (Value != rhs.Value) return false;
            if (Rule != rhs.Rule) return false;
            if (Altered != rhs.Altered) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Rule.GetHashCode() ^ Altered.GetHashCode();
        }

        public bool IsContainedBy(string s)
        {
            if (EscapeType == ECgStringEscapeType.Int)
            {
                int result;
                return Int32.TryParse(s, out result);
            }
            if (EscapeType == ECgStringEscapeType.Float)
            {
                decimal result;
                return Decimal.TryParse(s, out result);
            }
            if (Rule == ECgStringWordRule.MatchCase)
                return s.Contains(Value);
            if (Rule == ECgStringWordRule.Lower)
                return s.ToLower().Contains(Value);
            return s.Contains(Value);
        }
    }

    public sealed class FCgStringWord
    {
        private bool Completed;

        private List<FCgStringWordInfo> Ands;
        private List<FCgStringWordInfo> Ors;

        public FCgStringWord()
        {
            Completed = false;

            Ands = new List<FCgStringWordInfo>();
            Ors = new List<FCgStringWordInfo>();
        }

        public void AddAnd(string s, ECgStringWordRule rule = ECgStringWordRule.MatchCase)
        {
            Ands.Add(new FCgStringWordInfo(s, rule));
        }

        public void AddOr(string s, ECgStringWordRule rule = ECgStringWordRule.MatchCase)
        {
            Ors.Add(new FCgStringWordInfo(s, rule));
        }

        public void Clear()
        {
            Completed = false;
        }

        public void ProcessInput(string input)
        {
            int and = 0;
            bool or = false;

            // Check And
            int andCount = Ands.Count;

            for (int i = and; i < andCount; ++i)
            {
                if (Ands[i] == "" || Ands[i].IsContainedBy(input))
                {
                    ++and;
                }
            }
            // Check Or
            int orCount = Ors.Count;

            for (int i = 0; i < orCount; ++i)
            {
                or |= (Ors[i] == "" || Ors[i].IsContainedBy(input));

                if (or)
                    break;
            }
            Completed = (and > 0 && and == andCount) || or;
        }

        public bool HasCompleted()
        {
            return Completed;
        }
    }

    public sealed class FCgStringPhrase
    {
        private bool Completed;

        private List<FCgStringWord> Words;

        public FCgStringPhrase()
        {
            Completed = false;

            Words = new List<FCgStringWord>();
        }

        public void AddAndToWord(int index, string word, ECgStringWordRule rule = ECgStringWordRule.MatchCase)
        {
            int count = Words.Count;

            if (index >= count)
            {
                for (int i = 0; i < index - count + 1; ++i)
                {
                    Words.Add(new FCgStringWord());
                }
            }
            Words[index].AddAnd(word, rule);
        }

        public void AddOrToWord(int index, string word, ECgStringWordRule rule = ECgStringWordRule.MatchCase)
        {
            int count = Words.Count;

            if (index >= count)
            {
                for (int i = 0; i < index - count + 1; ++i)
                {
                    Words.Add(new FCgStringWord());
                }
            }
            Words[index].AddOr(word, rule);
        }

        public void Clear()
        {
            int count = Words.Count;

            for (int i = 0; i < count; ++i)
            {
                Words[i].Clear();
            }
            Completed = false;
        }

        public void ProcessInput(string input)
        {
            // Check if ALL Words are Completed
            int count = Words.Count;
            int index = 0;

            for (index = 0; index < count; ++index)
            {
                if (Words[index].HasCompleted())
                    continue;

                Words[index].ProcessInput(input);

                if (index < count - 1 || !Words[index].HasCompleted())
                    break;
            }

            if (index != count)
                Clear();

            // Check if Completed
            if (index > 0 && index == count)
            {
                Completed = true;
            }
        }

        public bool HasCompleted()
        {
            return Completed;
        }
    }

    public sealed class FCgStringSentence
    {
        private bool Completed;

        private List<FCgStringPhrase> Phrases;

        public FCgStringSentence()
        {
            Completed = false;

            Phrases = new List<FCgStringPhrase>();
        }

        public void AddPhrase(FCgStringPhrase phrase)
        {
            Phrases.Add(phrase);
        }

        public void Clear()
        {
            int count = Phrases.Count;

            for (int i = 0; i < count; ++i)
            {
                Phrases[i].Clear();
            }
            Completed = false;
        }

        public void ProcessInput(string input)
        {
            if (Completed)
                return;

            // Check if ALL Phrases are Completed
            int count = Phrases.Count;
            int index = 0;

            for (index = 0; index < count; ++index)
            {
                if (Phrases[index].HasCompleted())
                    continue;

                Phrases[index].ProcessInput(input);

                if (index < count - 1 || !Phrases[index].HasCompleted())
                    break;
            }

            if (index != count)
                Clear();

            // Check if Completed
            if (index == count)
                Completed = true;
        }

        public bool HasCompleted()
        {
            return Completed;
        }
    }

    public sealed class FCgStringParagraph
    {
        public sealed class FCompletedEvent : FCgMulticastDelegate { }

        private bool Completed;

        private List<FCgStringSentence> Sentences;

        private FCompletedEvent Event;

        public FCgStringParagraph()
        {
            Completed = false;

            Sentences = new List<FCgStringSentence>();

            Event = new FCompletedEvent();
        }

        public void AddSentence(FCgStringSentence sentence)
        {
            Sentences.Add(sentence);
        }

        public void AddEvent(FCompletedEvent.Event e)
        {
            Event.Add(e);
        }

        public void Clear()
        {
            int count = Sentences.Count;

            for (int i = 0; i < count; ++i)
            {
                Sentences[i].Clear();
            }
            Completed = false;
        }

        public void ProcessInput(string input)
        {
            if (Completed)
                return;

            // Check if ALL Setences are Completed
            int count = Sentences.Count;
            int index = 0;

            for (index = 0; index < count; ++index)
            {
                if (Sentences[index].HasCompleted())
                    continue;

                Sentences[index].ProcessInput(input);

                if (index < count - 1 || !Sentences[index].HasCompleted())
                    break;
            }

            // Check if Completed
            if (index == count)
            {
                Completed = true;

                Event.Broadcast();
            }
        }

        public bool HasCompleted()
        {
            return Completed;
        }
    }

    public static class FCgStringParagraphHelper
    {
        public static FCgStringSentence CreateOneWordSentence(string word, ECgStringWordRule rule = ECgStringWordRule.MatchCase)
        {
            FCgStringSentence sentence = new FCgStringSentence();
                FCgStringPhrase phrase = new FCgStringPhrase();
                phrase.AddAndToWord(0, word, rule);
            sentence.AddPhrase(phrase);

            return sentence;
        }

        public static FCgStringParagraph CreateOneWordParagraph(string word, ECgStringWordRule rule = ECgStringWordRule.MatchCase)
        {
            FCgStringParagraph paragraph = new FCgStringParagraph();
                FCgStringSentence sentence = new FCgStringSentence();
                    FCgStringPhrase phrase = new FCgStringPhrase();
                    phrase.AddAndToWord(0, word, rule);
                sentence.AddPhrase(phrase);
            paragraph.AddSentence(sentence);

            return paragraph;
        }
    }
}