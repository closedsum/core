namespace CgCore
{
    using System;
    using System.IO;

    using Newtonsoft.Json;

    [Serializable]
    public struct FCgEthereumKeystoreKdfParams
    {
        public int dklen;
        public int n;
        public int p;
        public int r;
        public string salt;
    }

    [Serializable]
    public struct FCgEthereumKeystoreCipherParams
    {
        public string iv;
    }

    [Serializable]
    public struct FCgEthereumKeystoreCrypto
    {
        public string cipher;
        public string ciphertext;
        public FCgEthereumKeystoreCipherParams cipherparams;
        public string kdf;
        public FCgEthereumKeystoreKdfParams kdfparams;
        public string mac;
    }

    [Serializable]
    public sealed class FCgEthereumKeystore
    {
        public string address;
        public FCgEthereumKeystoreCrypto crypto;
        public string id;
        public int version;

        public void Parse(string str)
        {
            JsonConvert.PopulateObject(str, (object)this);
        }

        public void ParseFromFilePath(string path)
        {
            if (File.Exists(path))
                Parse(File.ReadAllText(path));
        }
    }
}

/*
{
    "address":"6f6445e26ec0b8a978c726ef0b13c7ba2f7fcc7d",
    "crypto":
        {
            "cipher":"aes-128-ctr",
            "ciphertext":"72aba15de0a294dc5b38b2502a43b9b03b149c7c7a668f32adc484a67a364a0f",
            "cipherparams":
                {
                    "iv":"f0c05b13716f2e2a2ccbc5b61afac5f7"
                },
             "kdf":"scrypt",
             "kdfparams":
             {
                "dklen":32,
                "n":262144,
                "p":1,
                "r":8,
                "salt":"7a94d238420851945da88f1898fb46a766e04d4b8729a31d6e29adb62b0d880d"
             },
             "mac":"b4aecf86c2090ba3ebf8d5e9df7eaf0ebe0b09ebbd671a3f8133bad52c58a620"
       },
       "id":"085ebc5d-c6e3-40e8-90fc-df82722b9bdc",
       "version":3
    }
*/
