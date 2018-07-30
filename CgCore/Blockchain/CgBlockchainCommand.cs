namespace CgCore
{
    using System.Collections.Generic;

    public sealed class FECgBlockchainCommand : FECgEnum_byte
    {
        public FECgBlockchainCommand(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgBlockchainCommandEqualityComparer : IEqualityComparer<FECgBlockchainCommand>
    {
        public bool Equals(FECgBlockchainCommand lhs, FECgBlockchainCommand rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgBlockchainCommand x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgBlockchainCommand : TCgEnumMap<FECgBlockchainCommand, byte>
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
        public FECgBlockchainCommand Command;
        public FCgBlockchainCommandArgument[] Arguments;
        public object Payload;

        public FCgBlockchainCommandInfo(FECgBlockchainCommand command, FCgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }

        public void Set(FECgBlockchainCommand command, FCgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }
    }
}