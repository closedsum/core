namespace CgCore
{
    public class CgEthereumAccount : CgBlockchainAccount
    {
        public static readonly int ADDRESS = 0;
        public static readonly int PASSPHRASE = 1;
        public static readonly int DURATION = 2;
        public static readonly int ARGUMENT_COUNT = 3;

        #region "Data Members"

        #region "Interface"

        public string Address;
        public string PassPhrase;

        #endregion // Interface

        #endregion // Data Members

        public CgEthereumAccount(string nickname) : base(nickname){}

        public CgEthereumAccount(string nickname, string address, string passphrase) : base(nickname)
        {
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
    }
}
