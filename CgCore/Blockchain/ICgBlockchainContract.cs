namespace CgCore
{
    using System;
    using System.Collections.Generic;

    public class CgBlockchainContractKey
    {
        public string Key;
    }

    public sealed class CgBlockchainContractKeyEqualityComparer : IEqualityComparer<CgBlockchainContractKey>
    {
        public bool Equals(CgBlockchainContractKey lhs, CgBlockchainContractKey rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(CgBlockchainContractKey x)
        {
            return x.GetHashCode();
        }
    }

    public sealed class ECgBlockchainContract : ECgEnum_byte
    {
        public ECgBlockchainContract(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgBlockchainContractEqualityComparer : IEqualityComparer<ECgBlockchainContract>
    {
        public bool Equals(ECgBlockchainContract lhs, ECgBlockchainContract rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgBlockchainContract x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgBlockchainContract : ECgEnumMap<ECgBlockchainContract, byte>
    {
        private static EMCgBlockchainContract _Instance;
        public static EMCgBlockchainContract Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgBlockchainContract();
                }
                return _Instance;
            }
        }

        public static EMCgBlockchainContract Get()
        {
            return Instance;
        }
    }

    public enum ECgBlockchainContractArgumentType : byte
    {
        Number,
        String,
        StringString,
        MAX
    }

    public struct CgBlockchainContractArgument
    {
        public string Name;
        public ECgBlockchainContractArgumentType ValueType;
        public object Value;

        public CgBlockchainContractArgument(string name, ECgBlockchainContractArgumentType valueType, object value)
        {
            Name = name;
            ValueType = valueType;
            Value = value;
        }

        public string ToStr()
        {
            // Number
            if (ValueType == ECgBlockchainContractArgumentType.Number)
                return CgCommon.NumericTypeToString(Value);
            // String
            if (ValueType == ECgBlockchainContractArgumentType.String)
                return (string)Value;
            // StringString
            if (ValueType == ECgBlockchainContractArgumentType.StringString)
                return "\"" + (string)Value + "\"";
            return "";
        }
    }

    public interface ICgBlockchainContract
    {
        string Name { get; set; }

        bool IsValid();
        string ToStr();
        void Parse(string str);
        void ParseFromFilePath(string path);
    }

    [Serializable]
    public abstract class CgBlockchainContract : ICgBlockchainContract
    {
        private string _Name;
        public string Name
        {
            get { return _Name; }
            set { _Name = value; }
        }

        public CgBlockchainContract(){}
        public CgBlockchainContract(string name)
        {
            Name = name;
        }

        public abstract bool IsValid();
        public abstract string ToStr();
        public abstract void Parse(string str);
        public abstract void ParseFromFilePath(string path);
    }
}
