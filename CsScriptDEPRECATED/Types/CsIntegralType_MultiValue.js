/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsPrimitiveType_MultiValue = require('CsScript/Types/CsPrimitiveType_MultiValue.js');

const CS_EMTPY = 0;

module.exports = class JsCsIntegralType_MultiValue extends JsCsPrimitiveType_MultiValue
{
    constructor()
    {
        super();
    }

    Max()
    {
        const len = this.Values.length;

        if (len == CS_EMPTY)
            return 0;

        let max = this.Values[0];

        for (let i = 0; i < len; i++)
        {
            Math.max(max, this.Values[i]);
        }
        return max;
    }

    Min()
    {
        const len = this.Values.length;

        if (len == CS_EMPTY)
            return 0;

        let min = this.Values[0];

        for (let i = 0; i < len; i++)
        {
            Math.min(min, this.Values[i]);
        }
        return min;
    }
};