/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsDelegate1 = require("Cs/Types/Delegate/Delegate.js")
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;

module.exports = class NJsDelegate
{
    static FSinglecastBase = class SinglecastBase
    {
        /**
         * @param {{ArgTypeInfos: {Type: any}[]}} params 
         */
        constructor(params)
        {
            check(IsValidObjectChecked(context, params));
            check(CommonLibrary.DoesKeyExistChecked(context, params, "ArgTypeInfos"));

            checkf(Array.isArray(params.ArgTypeInfos), context + ": params.ArgTypeInfos is NOT an array.");

            this.ArgTypeInfos = [];

            for (const info of params.ArgTypeInfos)
            {
                check(CommonLibbrary.DoesKeyExistChecked(context, info, "Type"));

                this.ArgTypeInfos.push({Type: info.Type});
            }

            this.ArgCount = this.ArgTypeInfos.length;

            this.Delegate = null; // NJsDelegate.FDelegateBases 
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         * @returns {NJsDelegate.FDelegate}
         */
        // NJsDelegate.FDelegate CreateDelegate(object: params)

        /**
         * @param {function}    fn 
         * @param {object}      caller
         */
        Bind(fn /*function*/, caller /*object*/)
        {
            let context = "NJsDelegate.FSinglecastBase.Add";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));
            check(IsValidObjectChecked(context, caller));

            checkf(this.Delegate.Fn !== fn && this.Delegate.Caller !== caller, context + ": fn and caller have ALREADY been bound.");

            let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: -1};

            this.Delegate.Set(params);
        }

        /**
         * @param {function} fn
         */
        BindStatic(fn /*function*/)
        {
            let context = "NJsDelegate.FSinglecastBase.AddStatic";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

             checkf(this.Delegate.Fn !== fn, context + ": fn has ALREADY been added.");

            let params = {Fn: fn, Caller: caller, bStatic: true, TerminationCount: -1};

            this.Delegate.Set(params);
        }

        Unbind()
        {
           this.Delegate.Reset();
        }

        /*bool*/ IsBound() { return this.Delegate.IsSet(); }
    }

    static FSinglecast = class Singlecast extends NJsDelegate.FSinglecastBase
    {
        constructor()
        {
            super({ArgTypeInfos: []});

            this.Delegate = new FJsDelegate1.FDelegate();
        }

        /**
         * @returns {any}
         */
        /*any*/ Execute()
        {
            let context = "NJsDelegate.FSinglecastBase.Execute";

            checkf(this.Delegate.IsSet(), context + ": delegate is NOT bound.");
            return this.Delegate.Execute();
        }

        /**
         * @returns {any} 
         */
        /*any*/ ExecuteIfBound()
        {
            if (this.Delegate.IsSet())
                return this.Delegate.Execute();
            return undefined;
        }
    }

    static FSinglecast_OneParam = class Singlecast_OneParam extends NJsDelegate.FSinglecastBase
    {
        /**
         * @param {{ArgTypeInfos: {Type: any}[]}} params 
         */
        constructor(params)
        {
            super(params);

            this.Delegate = new FJsDelegate1.FDelegate_OneParam();
        }

        /**
         * @param {any} param1
         * @returns {boolean}
         */
        /*bool*/ IsArgsValidChecked(param1 /*any*/)
        {
            let context = "NJsDelegate.FSinglecastBase.IsArgsValidChecked";

            let args = [];

            for (const info of this.ArgTypeInfos)
            {
                args.push({type: info.Type, value: param1});
            }

            check(FunctionLibrary.IsArgsValidChecked(context, args));
            return true;
        }
        
        /**
         * @param {any} param1
         * @returns {any} 
         */
        /*any*/ Execute(param1 /*any*/)
        {
            let context = "NJsDelegate.FSinglecastBase.Execute";

            checkf(this.Delegate.IsSet(), context + ": delegate is NOT bound.");
            return this.Delegate.Execute(param1);
        }

        /**
         * @param {any} param1
         * @returns {any} 
         */
        /*any*/ ExecuteIfBound(param1 /*any*/)
        {
            if (this.Delegate.IsSet())
                return this.Delegate.Execute();
            return undefined;
        }
    }
};