'use strict';

var AppDemo = require("./AppDemo.bs.js");
var Belt_Debug = require("bs-platform/lib/js/belt_Debug.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

Belt_Debug.setupChromeDebugger(/* () */0);

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, AppDemo.make(/* array */[])), "target");

/*  Not a pure module */
