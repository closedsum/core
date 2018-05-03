namespace CgCore
{
    using System.Collections.Generic;

    public enum ECgStringWordRule : byte
    {
        None,
        MatchCase,
        MAX
    }

    public struct CgStringWordInfo
    {
        private string Value;
        private ECgStringWordRule Rule;
        private string Altered;

        public CgStringWordInfo(string val, ECgStringWordRule rule)
        {
            Value = val;
            Rule = rule;
            Altered = Rule == ECgStringWordRule.None ? Value.ToLower() : Value;
        }

        public static implicit operator string(CgStringWordInfo w)
        {
            return w.Altered;
        }

        public static bool operator ==(CgStringWordInfo lhs, CgStringWordInfo rhs)
        {
            return lhs.Value == rhs.Value && lhs.Rule == rhs.Rule && lhs.Altered == rhs.Altered;
        }

        public static bool operator !=(CgStringWordInfo lhs, CgStringWordInfo rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(CgStringWordInfo lhs, string rhs)
        {
            return lhs.Value == rhs;
        }

        public static bool operator !=(CgStringWordInfo lhs, string rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(string lhs, CgStringWordInfo rhs)
        {
            return lhs == rhs.Value;
        }

        public static bool operator !=(string lhs, CgStringWordInfo rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgStringWordInfo))
                return false;

            CgStringWordInfo rhs = (CgStringWordInfo)obj;

            if (Value != rhs.Value) return false;
            if (Rule != rhs.Rule) return false;
            if (Altered != rhs.Altered) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Rule.GetHashCode() ^ Altered.GetHashCode();
        }
    }

    public sealed class CgStringWord
    {
        private bool Completed;

        private List<CgStringWordInfo> Ands;
        private List<CgStringWordInfo> Ors;

        public CgStringWord()
        {
            Completed = false;

            Ands = new List<CgStringWordInfo>();
            Ors = new List<CgStringWordInfo>();
        }

        public void AddAnd(string s, ECgStringWordRule rule = ECgStringWordRule.None)
        {
            Ands.Add(new CgStringWordInfo(s, rule));
        }

        public void AddOr(string s, ECgStringWordRule rule = ECgStringWordRule.None)
        {
            Ors.Add(new CgStringWordInfo(s, rule));
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
                if (Ands[i] == "" || input.Contains(Ands[i]))
                {
                    ++and;
                }
            }
            // Check Or
            int orCount = Ors.Count;

            for (int i = 0; i < orCount; ++i)
            {
                or |= (Ands[i] == "" || input.Contains(Ands[i]));

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

    public sealed class CgStringPhrase
    {
        private bool Completed;

        private List<CgStringWord> Words;

        public CgStringPhrase()
        {
            Completed = false;

            Words = new List<CgStringWord>();
        }

        public void AddAndToWord(int index, string s, ECgStringWordRule rule = ECgStringWordRule.None)
        {
            int count = Words.Count;

            if (index >= count)
            {
                for (int i = 0; i < index - count + 1; ++i)
                {
                    Words.Add(new CgStringWord());
                }
            }
            Words[index].AddAnd(s, rule);
        }

        public void AddOrToWord(int index, string s, ECgStringWordRule rule = ECgStringWordRule.None)
        {
            int count = Words.Count;

            if (index >= count)
            {
                for (int i = 0; i < index - count + 1; ++i)
                {
                    Words.Add(new CgStringWord());
                }
            }
            Words[index].AddOr(s, rule);
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

    public sealed class CgStringSentence
    {
        public sealed class CompletedEvent : CgMulticastDelegate { }

        private bool Completed;

        private List<CgStringPhrase> Phrases;

        private CompletedEvent Event;

        public CgStringSentence()
        {
            Completed = false;

            Phrases = new List<CgStringPhrase>();

            Event = new CompletedEvent();
        }

        public void AddPhrase(CgStringPhrase phrase)
        {
            Phrases.Add(phrase);
        }

        public void AddEvent(CompletedEvent.Event e)
        {
            Event.Add(e);
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
}