[%%debugger.chrome];

type status =
  | Playing
  | Paused;

type state = {
  song: Types.song,
  time: Types.secs,
  status,
};

type action =
  | Play
  | Pause
  | SetTime(Types.secs);

let component = ReasonReact.reducerComponent("Player");

let make = (~song: Types.song, ~time: Types.secs, _children) => {
  ...component,
  initialState: () => {time, song, status: Paused},
  reducer: (action: action, state: state) =>
    switch (action) {
    | Play => ReasonReact.Update({...state, status: Playing})
    | Pause => ReasonReact.Update({...state, status: Paused})
    | SetTime(t) => ReasonReact.Update({...state, time: state.time + t})
    },
  render: self =>
    <div>
      <Util.Button label="Play" onClick=(_event => self.send(Play)) />
      <Util.Button label="Pause" onClick=(_event => self.send(Pause)) />
      <Util.Button
        label="Plus 10"
        onClick=(_event => self.send(SetTime(10)))
      />
      <Util.Button
        label="Minus 10"
        onClick=(_event => self.send(SetTime(-10)))
      />
      <Util.Text label=(string_of_int(self.state.time)) />
    </div>,
};