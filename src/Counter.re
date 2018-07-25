type state = int;

type action =
  | Add
  | Sub;

let comp = ReasonReact.reducerComponent("counter");

let make = (~i: int, _children) => {
  ...comp,
  initialState: () => i,
  reducer: (a: action, s: state) =>
    switch (a) {
    | Add => ReasonReact.Update(s + 1)
    | Sub => ReasonReact.Update(s - 1)
    },
  render: self =>
    <div>
      <h2> (Util.str("Counter")) </h2>
      <h2> (Util.str(string_of_int(self.state))) </h2>
      <span>
        <button onClick=(_ => self.send(Add))> (Util.str("+")) </button>
        <button onClick=(_ => self.send(Sub))> (Util.str("-")) </button>
      </span>
    </div>,
};