// Generated by BUCKLESCRIPT VERSION 4.0.6, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ListLabels = require("bs-platform/lib/js/listLabels.js");
var ArrayLabels = require("bs-platform/lib/js/arrayLabels.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Search$ReactTemplate = require("../components/Search.bs.js");
var StockCard$ReactTemplate = require("../components/StockCard.bs.js");

var component = ReasonReact.reducerComponent("Main");

function company(json) {
  return /* record */[
          /* symbol */Json_decode.field("symbol", Json_decode.string, json),
          /* name */Json_decode.field("companyName", Json_decode.string, json)
        ];
}

function stockJson(json) {
  return /* record */[
          /* company */Json_decode.field("company", company, json),
          /* initalPrice */Json_decode.field("price", Json_decode.$$float, json),
          /* currentPrice */Json_decode.field("price", Json_decode.$$float, json)
        ];
}

var Decode = /* module */[
  /* company */company,
  /* stockJson */stockJson
];

function buildUrl(text) {
  return "https://api.iextrading.com/1.0/stock/" + (text + "/batch?types=price,company");
}

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", {
                          className: "mw5 center"
                        }, ReasonReact.element(undefined, undefined, Search$ReactTemplate.make((function (searchStr) {
                                    return Curry._1(self[/* send */3], /* Search */Block.__(0, [searchStr]));
                                  }), /* array */[])), Belt_Array.map(self[/* state */1][/* stocks */0], (function (x) {
                                return ReasonReact.element(undefined, undefined, StockCard$ReactTemplate.make(x[/* initalPrice */1], x[/* company */0], (function (s) {
                                                  return Curry._1(self[/* send */3], /* RemoveStock */Block.__(2, [s]));
                                                }), /* array */[]));
                              })));
            }),
          /* initialState */(function () {
              return /* record */[/* stocks : array */[]];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              switch (action.tag | 0) {
                case 0 : 
                    var text = action[0];
                    return /* SideEffects */Block.__(1, [(function (self) {
                                  fetch(buildUrl(text)).then((function (prim) {
                                            return prim.json();
                                          })).then((function (json) {
                                          var stock = stockJson(json);
                                          return Promise.resolve(Curry._1(self[/* send */3], /* AddStock */Block.__(1, [stock])));
                                        }));
                                  return /* () */0;
                                })]);
                case 1 : 
                    return /* Update */Block.__(0, [/* record */[/* stocks */Belt_Array.concat(state[/* stocks */0], /* array */[action[0]])]]);
                case 2 : 
                    var symbol = action[0];
                    var arg = ArrayLabels.to_list(state[/* stocks */0]);
                    var s = ArrayLabels.of_list((function (param) {
                              return ListLabels.filter(param)(arg);
                            })((function (s) {
                                return s[/* company */0][/* symbol */0] !== symbol;
                              })));
                    return /* Update */Block.__(0, [/* record */[/* stocks */s]]);
                
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.Decode = Decode;
exports.buildUrl = buildUrl;
exports.make = make;
/* component Not a pure module */
