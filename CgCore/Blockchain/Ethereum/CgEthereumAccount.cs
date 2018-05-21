namespace CgCore
{
    using System;
    using System.IO;

    using Newtonsoft.Json;

    [Serializable]
    public class CgEthereumAccount : CgBlockchainAccount
    {
        public static readonly int ADDRESS = 0;
        public static readonly int PASSPHRASE = 1;
        public static readonly int DURATION = 2;
        public static readonly int ARGUMENT_COUNT = 3;

        #region "Data Members"

        public string Address;
        public string PassPhrase;

        #endregion // Data Members

        public CgEthereumAccount() : base(){}

        public CgEthereumAccount(string nickname, string address, string passphrase) : base()
        {
            Nickname   = nickname;
            Address    = address;
            PassPhrase = passphrase;
        }

        public void CreateUnlockArguments(out CgBlockchainCommandArgument[] args)
        {
            args = new CgBlockchainCommandArgument[ARGUMENT_COUNT];

            args[ADDRESS]    = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, Address);
            args[PASSPHRASE] = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, PassPhrase);
            args[DURATION]   = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.Number, 0);
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

        public string AddressAsArg()
        {
            return "'0x" + Address + "'";
        }
    }
}
