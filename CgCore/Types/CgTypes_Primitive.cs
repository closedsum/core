namespace CgCore
{
    public abstract class ECgEnum<T>
    {
        public T Value;
        public string Name;

        public ECgEnum()
        {
            Value = default(T);
            Name = "";
        }

        public ECgEnum(T value, string name)
        {
            Value = value;
            Name = name;
        }
    }
}
