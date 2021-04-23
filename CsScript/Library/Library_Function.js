/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - classes
var CommonLibrary = NJsCommon.FLibrary;

module.exports = class NJsFunction
{
    static FLibrary = class Library
    {
        static NCached = class Cached
        {
            static NStr = class Str
            {
                static IsArgFormatValidChecked = "NJsFunction::FLibrary::IsFormateValidChecked";
            }
        }

        static IsArgFormatValidChecked(context, param, index)
        {
            let Str = NJsFunction.FLibrary.NCached.NStr;

            console.assert(typeof context === 'string', Str.IsArgFormatValidChecked + ": context is NOT a string.");

            CommonLibrary.IsValidObjectChecked(context, param);

            CommonLibrary.IsIntChecked(context, index);

            // Check 'key'.type exists
            if (param['type'] === undefined)
            {
                console.assert(false, context + ": params[" + index + "].type is NOT defined.");
                return false;
            }
            // check 'key'.value exists
            if (param['value'] === undefined)
            {
                console.assert(false, context + ": params[" + index + "].value is NOT defined.");
                return false;
            }
            return true;
        }

        static IsArgsValidChecked(context, args)
        {
            for (let i = 0; i < args.length; ++i)
            {
                const arg = args[i];

                CommonLibrary.IsValidObjectChecked(context, arg);

                this.IsArgFormatValidChecked(context, arg, i);
            }
            return true;
        }
    };
};