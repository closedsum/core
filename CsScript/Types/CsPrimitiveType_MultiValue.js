/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class JsCsPrimitiveType_MultiValue
{
    constructor()
    {
        this.Owner       = null;
        this.MemberName  = "";
        this.Type        = ECsMemberType.Bool;
        this.SIZE        = 1;

        this.Value = null;
        this.Last_Value = null;

        this.Values = [];
        this.Last_Values = [];

        this.IsDirty = false;
        this.IsDirtys = []
    }
    
    Init(inOwner, inMemberName, inType, inSIZE)
    {
        this.Owner      = inOwner;
        this.MemberName = inMemberName;
        this.Type       = inType;
        this.SIZE       = inSIZE;

        let defaultValue = null;

        if (this.Type == ECsMemberType.Bool)
            defaultValue = false;
        if (this.Type == ECsMemberType.Int32)
            defaultValue = 0;
        if (this.Type == ECsMemberType.Float)
            defaultValue = 0.0;

        this.Value      = defaultValue;
        this.Last_Value = this.Value;

        for (let i = 0; i < this.SIZE; i++)
        {
            this.Values.push(defaultValue);
            this.Last_Values.push(this.Values[i]);

            this.IsDirtys.push(false);

            this.Get(i);
        }
    }

    Set(index, value)
    {
        // bool
        if (this.Type == ECsMemberType.Bool)
            this.Owner.SetMemberValue_bool(index, this.MemberName, value);
        // uint8
        if (this.Type == ECsMemberType.Uint8)
            this.Owner.SetMemberValue_uint8(index, this.MemberName, value);
        // int32
        if (this.Type == ECsMemberType.Int32)
            this.Owner.SetMemberValue_int32(index, this.MemberName, value);
        // float
        if (this.Type == ECsMemberType.Float)
            this.Owner.SetMemberValue_float(index, this.MemberName, value);

        this.Values[index]   = value;
        this.IsDirtys[index] = this.Values[index] != this.Last_Values[index];
    }

    Get(index)
    {
        // bool
        if (this.Type == ECsMemberType.Bool)
            this.Values[index] = this.Owner.GetMemberValue_bool(index, this.MemberName);
        // uint8
        if (this.Type == ECsMemberType.Uint8)
            this.Values[index] = this.Owner.GetMemberValue_uint8(index, this.MemberName);
        // int32
        if (this.Type == ECsMemberType.Int32)
            this.Values[index] = this.Owner.GetMemberValue_int32(index, this.MemberName);
        // float
        if (this.Type == ECsMemberType.Float)
            this.Values[index] = this.Owner.GetMemberValue_float(index, this.MemberName);

        this.Last_Values[Index] = this.Values[index];
        this.IsDirtys[index]    = this.Values[index] != this.Last_Values[index];
        return this.Values[index];
    }

    Add(index, value)
    {
        this.Values[index]  += value;
        this.IsDirtys[index] = this.Values[index] != this.Last_Values[index];
    }
};