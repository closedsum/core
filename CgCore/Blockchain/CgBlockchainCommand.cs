namespace CgCore
{
    using System.Collections.Generic;

    public sealed class ECgBlockchainCommand : FECgEnum_byte
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

    public class EMCgBlockchainCommand : TCgEnumMap<ECgBlockchainCommand, byte>
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

    public struct FCgBlockchainCommandArgument
    {
        public ECgBlockchainCommandArgumentType ValueType;
        public object Value;

        public FCgBlockchainCommandArgument(ECgBlockchainCommandArgumentType valueType, object value)
        {
            ValueType = valueType;
            Value = value;
        }

        public string ToStr()
        {
            // Number
            if (ValueType == ECgBlockchainCommandArgumentType.Number)
                return FCgCommon.NumericTypeToString(Value);
            // String
            if (ValueType == ECgBlockchainCommandArgumentType.String)
                return (string)Value;
            // StringString
            if (ValueType == ECgBlockchainCommandArgumentType.StringString)
                return "\"" + (string)Value + "\"";
            return "";
        }
    }

    public struct FCgBlockchainCommandInfo
    {
        public ECgBlockchainCommand Command;
        public FCgBlockchainCommandArgument[] Arguments;
        public object Payload;

        public FCgBlockchainCommandInfo(ECgBlockchainCommand command, FCgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }

        public void Set(ECgBlockchainCommand command, FCgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }
    }
}