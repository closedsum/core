/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

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
    static FDelegateBase = class DelegateBase
    {
        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, Id: string, Order: int, TerminationCount: int} 
         */
        constructor(params /*object*/)
        {
            // Reference to a function.
            this.Fn = params.Fn;
            // Caller of function, this should be set (NOT null) if bStatic is true.
            this.Caller = params.Caller;
            // Whether the function is static or not (needs a caller).
            this.bStatic = params.bStatic;
            // Current Handle 'id', Guid as string, associated with the delegate.
            this.Id = params.Id;
            // The order, index in an InvocationList (relevant for Mulitcast), the function is called.
            this.Order = params.Order;
            // if > 0, the count before the delegate is removed from an InvocationList (relevant for Multicast).
            this.TerminationCount = params.TerminationCount;
            // The current number of times Execute() has been called.
            this.ExecutionCount = 0;
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, Id: string, Order: int, TerminationCount: int} 
         */
        Set(params /*object*/)
        {
            this.Fn = params.Fn;
            this.Caller = params.Caller;
            this.bStatic = params.bStatic;
            this.Id = params.Id;
            this.Order = params.Order;
            this.TerminationCount = params.TerminationCount;
            this.ExecutionCount = 0;
        }

        /**
         * @returns {boolean}
         */
        /*bool*/ IsSet() { return this.Fn !== null; }

        /**
         * @returns {string} 
         */
        /*string*/ GetId() { return this.Id; }

        /**
         * @param {number} order 
         */
        SetOrder(order /*int*/)
        {
            this.Order = order;
        }

        /**
         * @returns {number} int 
         */
        /*int*/ GetOrder(){ return this.Order; }

        /**
         * @returns {boolean}
         */
        /*bool*/ HasExpired(){ return this.TerminationCount > 0 && this.ExecutionCount >= this.TerminationCount; }

        Reset()
        {
            this.Fn = null;
            this.Caller = null;
            this.bStatic = false;
            this.Id = "";
            this.Order = -1;
            this.TerminationCount = -1;
            this.ExecutionCount = 0;
        }
    }
    
    static FDelegate = class Delegate extends NJsDelegate.FDelegateBase
    {
        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        constructor(params /*object*/)
        {
            super(params);
        }

        Execute()
        {
            ++this.ExecutionCount;

            if (this.bStatic)
                return this.Fn();
            return this.Fn.call(this.Caller);
        }
    }

    static FDelegate_OneParam = class Delegate_OneParam extends NJsDelegate.FDelegateBase
    {
        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        constructor(params /*object*/)
        {
            super(params);
        }

        /**
         * @param {any} param1
         * @returns {any}
         */
        /*any*/ Execute(param1 /*any*/)
        {
            ++this.ExecutionCount;

            if (this.bStatics)
                return this.Fn(param1);
            return this.Fn.call(this.Caller, param1);
        }
    }
};