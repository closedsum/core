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
    static FMulticastBase = class MulticastBase
    {
        /**
         * @param {{ArgTypeInfos: {Type: any}[]}} params 
         */
        constructor(params)
        {
            let context = "NJsDelegate.FMulticastBase.ctor";

            check(IsValidObjectChecked(context, params));
            check(CommonLibrary.DoesKeyExistChecked(context, params, "ArgTypeInfos"));

            checkf(Array.isArray(params.ArgTypeInfos), context + ": params.ArgTypeInfos is NOT an array.");

            this.ArgTypeInfos = [];

            for (const info of params.ArgTypeInfos)
            {
                check(CommonLibrary.DoesKeyExistChecked(context, info, "Type"));

                this.ArgTypeInfos.push({Type: info.Type});
            }

            this.ArgCount = this.ArgTypeInfos.length;

            this.InvocationMap = new Map(); // [Guid as string][Delegate]
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         * @returns {NJsDelegate.FDelegate}
         */
        // NJsDelegate.FDelegate CreateDelegate(object: params)

        /**
         * @param {function}    fn 
         * @param {object}      caller
         * @returns {string}    Guid as string 
         */
        /*string*/ Add(fn /*function*/, caller /*object*/)
        {
            let context = "NJsDelegate.FMulticastBase.Add";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));
            check(IsValidObjectChecked(context, caller));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn && value.Caller !== caller, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();
            let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: -1}
            let d = this.CreateDelegate(params);

            this.InvocationMap.set(id, d);

            return id;
        }

        /**
         * @param {function} fn
         * @returns {string} Guid as string
         */
        /*string*/ AddStatic(fn /*function*/)
        {
            let context = "NJsDelegate.FMulticastBase.AddStatic";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn, context + ": fn has ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();
            let params = {Fn: fn, Caller: null, bStatic: true, TerminationCount: -1}
            let d = this.CreateDelegate(params);

            this.InvocationMap.set(id, d);

            return id;
        }
  
        /*string*/ AddOneShot(fn /*function*/, caller /*object*/)
        {
            let context = "NJsDelegate.FMulticastBase.AddOneShot";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn && value.Caller !== caller, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();
            let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: 1}
            let d = this.CreateDelegate(params);

            this.InvocationMap.set(id, d);

            return id;
        }

        /*bool*/ Remove(id /*string*/)
        {
            if (this.InvocationMap.has(id))
            {
                this.InvocationMap.delete(id);
                return true;
            }
            return false;
        }

        /*bool*/ RemoveByCaller(caller /*object*/)
        {
            let ids = [];

            for (const [key, value] of this.InvocationMap.entries())
            {
                if (value.Caller === caller)
                    ids.push(key);
            }

            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
            return ids.length > 0;
        }

        /*bool*/ IsBound() { return this.InvocationMap.size > 0; }
    }

    static FMulticast = class Multicast extends NJsDelegate.FMulticastBase
    {
        constructor()
        {
            super({ArgTypeInfos: []});
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        /*NJsDelegate.FDelegate*/ CreateDelegate(params /*object*/)
        {
            return new NJsDelegate1.FDelegate(params);
        }

        Broadcast()
        {
            let ids = [];

            for (let [key, value] of this.InvocationMap.entries())
            {
                value.Execute();

                // Check if the delegate should be removed after execution.
                if (value.HasExpired())
                    ids.push(key);
            }

            // Remove any delegates that have "expired"
            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
        }
    }

    static FMulticast_OneParam = class Multicast_OneParam extends NJsDelegate.FMulticastBase
    {
        /**
         * @param {{ArgTypeInfos: {Type: any}[]}} params 
         */
        constructor(params)
        {
            super(params);
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        /*NJsDelegate.FDelegate*/ CreateDelegate(params /*object*/)
        {
            return new NJsDelegate1.FDelegate_OneParam(params);
        }

        /**
         * @param {any} param1
         * @returns {boolean}
         */
        /*bool*/ IsArgsValidChecked(param1 /*any*/)
        {
            let context = "NJsDelegate.FMulticastBase.IsArgsValidChecked";

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
         */
        Broadcast(param1 /*any*/)
        {
            check(IsArgsValidChecked(param1));

            let ids = [];

            for (let [key, value] of this.InvocationMap.entries())
            {
                value.Execute(param1);

                // Check if the delegate should be removed after execution.
                if (value.HasExpired())
                    ids.push(key);
            }

            // Remove any delegates that have "expired"
            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
        }
    }
};