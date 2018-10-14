[%%debugger.chrome];

let str = ReasonReact.string;

let tap = x => {
  Js.log(x);
  x;
};
let tap2 = (x, y) => {
  Js.log2(x, y);
  y;
};
let tap3 = (x, y, z) => {
  Js.log3(x, y, z);
  z;
};

let ignoreRender = _ => ReasonReact.null;

module Button = {
  let component = ReasonReact.statelessComponent("Button");

  let make = (~label, ~onClick, ~disabled=false, _children) => {
    ...component,
    render: _self => <button onClick disabled> (str(label)) </button>,
  };
};

module Text = {
  let component = ReasonReact.statelessComponent("Text");

  let make = (~label, _children) => {
    ...component,
    render: _self => <div> (str(label)) </div>,
  };
};