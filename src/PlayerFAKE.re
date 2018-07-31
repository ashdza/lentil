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

let make =
    (
      ~song: Types.song,
      ~time: Types.secs,
      ~onPlay: unit => unit,
      ~onPause: unit => unit,
      ~onProgress: Types.secs => unit,
      _children,
    ) => {
  ...component,
  initialState: () => {time, song, status: Paused},
  reducer: (action: action, state: state) =>
    switch (action) {
    | Play =>
      ReasonReact.UpdateWithSideEffects(
        {...state, status: Playing},
        (_self => onPlay()),
      )
    | Pause =>
      ReasonReact.UpdateWithSideEffects(
        {...state, status: Paused},
        (_self => onPause()),
      )
    | SetTime(t) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, time: t},
        (_self => onProgress(t)),
      )
    },
  render: self =>
    <div>
      <Util.Button label="Play" onClick=(_event => self.send(Play)) />
      <Util.Button label="Pause" onClick=(_event => self.send(Pause)) />
      <Util.Button
        label="Plus 10"
        onClick=(_event => self.send(SetTime(self.state.time + 10)))
      />
      <Util.Button
        label="Minus 10"
        onClick=(_event => self.send(SetTime(self.state.time - 10)))
      />
      <Util.Text label=(string_of_int(self.state.time)) />
    </div>,
};