[%%debugger.chrome];

let str = ReasonReact.string;

module Button = {
  let component = ReasonReact.statelessComponent("Button");

  let make = (~label, ~onClick, _children) => {
    ...component,
    render: _self => <button onClick> (str(label)) </button>,
  };
};

module Text = {
  let component = ReasonReact.statelessComponent("Text");

  let make = (~label, _children) => {
    ...component,
    render: _self => <div> (str(label)) </div>,
  };
};