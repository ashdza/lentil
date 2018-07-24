let str = ReasonReact.string;

module Counter = {
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
        <h2> (str("Counter")) </h2>
        <h2> (str(string_of_int(self.state))) </h2>
        <span>
          <button onClick=(_ => self.send(Add))> (str("+")) </button>
          <button onClick=(_ => self.send(Sub))> (str("-")) </button>
        </span>
      </div>,
  };
};

module Top = {
  let comp = ReasonReact.statelessComponent("top");

  let make = (~initCounts: list(int), _children) => {
    ...comp,
    render: _self => {
      let counters =
        List.map(init => <Counter i=init />, initCounts)
        |> Array.of_list
        |> ReasonReact.array;
      <div> counters </div>;
    },
  };
};

ReactDOMRe.renderToElementWithId(<Top initCounts=[0, 5, 25] />, "body");