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

    public sealed class FECgBlockchainContract : FECgEnum_byte
    {
        public FECgBlockchainContract(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgBlockchainContractEqualityComparer : IEqualityComparer<FECgBlockchainContract>
    {
        public bool Equals(FECgBlockchainContract lhs, FECgBlockchainContract rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgBlockchainContract x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgBlockchainContract : TCgEnumMap<FECgBlockchainContract, byte>
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
            // HACKY: For now add ',' to distinguish between the same input arguments in the ABI
            Name = name + ",";
            ValueType = valueType;
            Value = value;
        }

        public string ToStr()
        {
            // HACKY: For now add ',' to distinguish between the same input arguments in the ABI

            // Number
            if (ValueType == ECgBlockchainContractArgumentType.Number)
                return FCgCommon.NumericTypeToString(Value) + ",";
            // String
            if (ValueType == ECgBlockchainContractArgumentType.String)
                return (string)Value + ",";
            // StringString
            if (ValueType == ECgBlockchainContractArgumentType.StringString)
                return "'" + (string)Value + "'" + ",";
            return "";
        }
    }

    #region "Function"

    public sealed class ECgBlockchainContractFunction : FECgEnum_byte
    {
        public ECgBlockchainContractFunction(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgBlockchainContractFunctionEqualityComparer : IEqualityComparer<ECgBlockchainContractFunction>
    {
        public bool Equals(ECgBlockchainContractFunction lhs, ECgBlockchainContractFunction rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgBlockchainContractFunction x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgBlockchainContractFunction : TCgEnumMap<ECgBlockchainContractFunction, byte>
    {
        private static EMCgBlockchainContractFunction _Instance;
        public static EMCgBlockchainContractFunction Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgBlockchainContractFunction();
                }
                return _Instance;
            }
        }

        public static EMCgBlockchainContractFunction Get()
        {
            return Instance;
        }
    }

    public enum ECgBlockchainContractFunctionArgumentType : byte
    {
        Number,
        String,
        MAX
    }

    public struct FCgBlockchainContractFunctionArgument
    {
        public ECgBlockchainContractFunctionArgumentType ValueType;
        public object Value;

        public FCgBlockchainContractFunctionArgument(ECgBlockchainContractFunctionArgumentType valueType, object value)
        {
            ValueType = valueType;
            Value = value;
        }

        public string ToStr()
        {
            // Number
            if (ValueType == ECgBlockchainContractFunctionArgumentType.Number)
                return FCgCommon.NumericTypeToString(Value);
            // String
            if (ValueType == ECgBlockchainContractFunctionArgumentType.String)
                return "'" + (string)Value + "'";
            return "";
        }

        public void Clear()
        {
            Value = null;
        }
    }

    public enum ECgBlockchainContractFunctionReturnType : byte
    {
        Number,
        String,
        MAX
    }

    public struct FCgBlockchainContractFunctionReturn
    {
        public static readonly FCgBlockchainContractFunctionReturn Void = new FCgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType.MAX, null);
        public static readonly FCgBlockchainContractFunctionReturn Number = new FCgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType.Number, 0);
        public static readonly FCgBlockchainContractFunctionReturn String = new FCgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType.String, "");

        public ECgBlockchainContractFunctionReturnType ValueType;
        public object Value;

        public FCgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType valueType, object value)
        {
            ValueType = valueType;
            Value = value;
        }

        public string ToStr()
        {
            // Number
            if (ValueType == ECgBlockchainContractFunctionReturnType.Number)
                return FCgCommon.NumericTypeToString(Value);
            // String
            if (ValueType == ECgBlockchainContractFunctionReturnType.String)
                return (string)Value;
            return "";
        }

        public void Clear()
        {
            Value = null;
        }
    }

    public sealed class FCgBlockchainContractFunction
    {
        private static readonly int EMPTY = 0;

        public string Signature;
        public FCgBlockchainContractFunctionArgument[] Arguments;
        public FCgBlockchainContractFunctionReturn Return;

        public FCgBlockchainContractFunction(string signature, FCgBlockchainContractFunctionArgument[] args, FCgBlockchainContractFunctionReturn ret)
        {
            Signature = signature;
            Arguments = args;
            Return = ret;
        }

        public void SetArgument(int index, object value)
        {
            Arguments[index].Value = value;
        }

        public string BuildConstantFunction()
        {
            string output = Signature + "(";

            if (Arguments != null && Arguments.Length > EMPTY)
            {
                int argumentLength = Arguments.Length;

                for (int i = 0; i < argumentLength; ++i)
                {
                    output += Arguments[i].ToStr();

                    if (i < argumentLength - 1)
                        output += ",";
                }
            }

            output += ");";

            return output;
        }

        public string BuildEstimateFunction(string address)
        {
            string output = Signature;

            output += ".estimateGas(";

            if (Arguments != null && Arguments.Length > EMPTY)
            {
                int argumentLength = Arguments.Length;

                for (int i = 0; i < argumentLength; ++i)
                {
                    output += Arguments[i].ToStr();
                    output += ",";
                }
            }

            output += " { from: " + address + " });";

            return output;
        }

        public string BuildStateChangeFunction(string address, int gas)
        {
            string output = Signature;

            output += "(";

            if (Arguments != null && Arguments.Length > EMPTY)
            {
                int argumentLength = Arguments.Length;

                for (int i = 0; i < argumentLength; ++i)
                {
                    output += Arguments[i].ToStr();
                    output += ",";
                }
            }

            output += " { from: " + address + ", gas: " + gas + " });";

            return output;
        }

        public void Clear()
        {
            if (Arguments != null)
            {
                for (int i = 0; i < Arguments.Length; ++i)
                {
                    Arguments[i].Clear();
                }
            }

            Return.Clear();
        }
    }

    public struct FCgBlockchainContractFunctionPayload
    {
        public FECgBlockchainContract Contract;
        public ECgBlockchainContractFunction Function;
        //object Payload;

        public FCgBlockchainContractFunctionPayload(FECgBlockchainContract econtract, ECgBlockchainContractFunction efn)
        {
            Contract = econtract;
            Function = efn;
            //Payload = payload;
        }
    }

    #endregion // Function

    public interface ICgBlockchainContract
    {
        string Name { get; set; }

        bool IsValid();
        string ToStr();
        void Parse(string str);
        void ParseFromFilePath(string path);
    }

    [Serializable]
    public abstract class FCgBlockchainContract : ICgBlockchainContract
    {
        private string _Name;
        public string Name
        {
            get { return _Name; }
            set { _Name = value; }
        }

        public FCgBlockchainContract(){}
        public FCgBlockchainContract(string name)
        {
            Name = name;
        }

        public abstract bool IsValid();
        public abstract string ToStr();
        public abstract void Parse(string str);
        public abstract void ParseFromFilePath(string path);
    }
}
