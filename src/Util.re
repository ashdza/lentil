[%%debugger.chrome];

let str = ReasonReact.string;

let tap = x => {
  Js.log({j|Tap: $(x)|j});
  x;
};

let tap2 = (x: string, y) => {
  Js.log2(x, {j|Tap: $(y)|j});
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

  let make = (~label, ~style=Styles.none, _children) => {
    ...component,
    render: _self => <div className=style> (str(label)) </div>,
  };
};

/* Experiments */

/* literal in JSX */
let a = s => <div> (str(s)) </div>;

/* syntactic JSX in JSX */
let a1 = <div> <div /> </div>;

/* syntactic code expressions (mixed with JSX) in JSX */
let b = (s1, s2) => <div> <div /> (a(s1)) (a(s2)) </div>;

/* syntactic array in JSX must be ...spread */
let c = (s1, s2) => <div> ...[|a(s1), a(s2)|] </div>;

/* list must be |> Array.of_list |> ReasonReact.array */
let d = (l: list((string, string))) =>
  l |> List.map(((x, y)) => b(x, y)) |> Array.of_list |> ReasonReact.array;