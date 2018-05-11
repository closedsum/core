namespace CgCore
{
    using System.Collections.Generic;

    public sealed class ECgBlockchainCommand : ECgEnum_byte
    {
        public ECgBlockchainCommand(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgBlockchainCommandEqualityComparer : IEqualityComparer<ECgBlockchainCommand>
    {
        public bool Equals(ECgBlockchainCommand lhs, ECgBlockchainCommand rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgBlockchainCommand x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgBlockchainCommand : ECgEnumMap<ECgBlockchainCommand, byte>
    {
        private static EMCgBlockchainCommand _Instance;
        public static EMCgBlockchainCommand Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgBlockchainCommand();
                }
                return _Instance;
            }
        }

        public static EMCgBlockchainCommand Get()
        {
            return Instance;
        }
    }

    public enum ECgBlockchainCommandArgumentType : byte
    {
        Number,
        String,
        StringString,
        MAX
    }

    public struct CgBlockchainCommandArgument
    {
        public ECgBlockchainCommandArgumentType ValueType;
        public object Value;

        public CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType valueType, object value)
        {
            ValueType = valueType;
            Value = value;
        }

        public string ToStr()
        {
            // Number
            if (ValueType == ECgBlockchainCommandArgumentType.Number)
                return CgCommon.NumericTypeToString(Value);
            // String
            if (ValueType == ECgBlockchainCommandArgumentType.String)
                return (string)Value;
            // StringString
            if (ValueType == ECgBlockchainCommandArgumentType.StringString)
                return "\"" + (string)Value + "\"";
            return "";
        }
    }

    public struct CgBlockchainCommandInfo
    {
        public ECgBlockchainCommand Command;
        public CgBlockchainCommandArgument[] Arguments;
        public object Payload;

        public CgBlockchainCommandInfo(ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }

        public void Set(ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }
    }
}