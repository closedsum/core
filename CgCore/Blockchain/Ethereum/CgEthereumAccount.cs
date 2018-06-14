namespace CgCore
{
    using System;
    using System.IO;

    using Newtonsoft.Json;

    [Serializable]
    public class FCgEthereumAccount : FCgBlockchainAccount
    {
        public static readonly int ADDRESS = 0;
        public static readonly int PASSPHRASE = 1;
        public static readonly int DURATION = 2;
        public static readonly int ARGUMENT_COUNT = 3;

        #region "Data Members"

        public string Address;
        public string PassPhrase;

        private string AddressAsHex;
        private string AddressAsArg;

        #endregion // Data Members

        public FCgEthereumAccount() : base(){}

        public FCgEthereumAccount(string nickname, string address, string passphrase) : base()
        {
            Nickname   = nickname;
            Address    = address;
            PassPhrase = passphrase;

            AddressAsHex = "0x" + Address;
            AddressAsArg = "'" + AddressAsHex + "'";
        }

        public void CreateUnlockArguments(out FCgBlockchainCommandArgument[] args)
        {
            args = new FCgBlockchainCommandArgument[ARGUMENT_COUNT];

            args[ADDRESS]    = new FCgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, Address);
            args[PASSPHRASE] = new FCgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, PassPhrase);
            args[DURATION]   = new FCgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.Number, 0);
        }

        public override string ToStr()
        {
            return JsonConvert.SerializeObject(this);
        }

        public override void Parse(string str)
        {
            JsonConvert.PopulateObject(str, (object)this);
        }

        public override void ParseFromFilePath(string path)
        {
            if (File.Exists(path))
                Parse(File.ReadAllText(path));
        }

        public string GetAddressAsHex()
        {
            return AddressAsHex;
        }

        public string GetAddressAsArg()
        {
            return AddressAsArg;
        }
    }
}
