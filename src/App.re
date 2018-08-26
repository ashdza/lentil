[%%debugger.chrome];

module Player = ReReactPlayer.Player;

type songInProgress = {
  song: Types.song,
  prog: float,
  text: string,
};

type option('a) =
  | None
  | Some('a);

type state = {
  songList: Types.songList,
  current: option(songInProgress),
};

type action =
  | Select(Types.song)
  | UpdateProgress(float)
  | LeaveComment
  | TextChange(string);

let component = ReasonReact.reducerComponent("App");

let make = (~songList: Types.songList, _children) => {
  ...component,
  initialState: () => {songList, current: None},
  reducer: (action: action, state: state) =>
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: newSong, prog: 0.0, text: ""}),
      })
    | (
        UpdateProgress(playedSec),
        {songList: _sl, current: Some({song: s, prog: p, text: t})},
      ) =>
      Js.log2(playedSec, p);
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec, text: t}),
      });
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        LeaveComment,
        {songList: _sl, current: Some({song: s, prog: p, text: t})},
      ) =>
      let newFeedback: Types.feedback = {
        location: Exact(p),
        comment: Text(t),
      };
      let newComments = Belt.List.add(s.comments, newFeedback);
      Js.log(s);
      ReasonReact.SideEffects((_ => s.comments = newComments));
    | (LeaveComment, _state) =>
      Js.log("ERROR: LEAVE COMMENT WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        TextChange(txt),
        {songList: _sl, current: Some({song: s, prog: p, text: t})},
      ) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: p, text: txt}),
      })
    | (TextChange(_), _) =>
      Js.log("ERROR: ENTER TEXT WHEN NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div>
      <h1 className="title is-1"> (Util.str("Lentil")) </h1>
      <SongList
        songList
        onSongSelect=((s: Types.song) => self.send(Select(s)))
      />
      (
        switch (self.state.current) {
        | Some({song: s, prog: p, text: t}) =>
          <div>
            <Player
              url=s.url
              onProgress=(
                (progress: Player.secs) =>
                  self.send(UpdateProgress(progress))
              )
            />
            <Util.Text label=(string_of_float(p)) />
            <input
              value=t
              onChange=(
                ev => {
                  let newText = ReactDOMRe.domElementToObj(
                                  ReactEventRe.Form.target(ev),
                                )##value;
                  self.send(TextChange(newText));
                }
              )
            />
            <Util.Button
              label="submit"
              onClick=(_event => self.send(LeaveComment))
            />
          </div>
        | None => ReasonReact.null
        }
      )
    </div>,
};