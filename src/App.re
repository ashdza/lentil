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

let addFeedbackToSong = (comment, loc, song: Types.song) => {
  let c: Types.feedback = {location: loc, comment};
  {...song, comments: Belt.List.add(song.comments, c)};
};

let make = (~initialSongs: Types.songList, _children) => {
  ...component,
  initialState: () => {songList: initialSongs, current: None},
  reducer: (action: action, state: state) =>
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: newSong, prog: 0.0, text: ""}),
      })
    | (
        UpdateProgress(playedSec),
        {songList: _sl, current: Some({song: s, prog: _p, text: t})},
      ) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec, text: t}),
      })
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        LeaveComment,
        {songList: sl, current: Some({song: s, prog: p, text: txt})},
      ) =>
      let updatedSong = addFeedbackToSong(txt, p, s);
      let updatedState = {
        songList: List.map(s' => s'.Types.id == s.id ? updatedSong : s', sl),
        current: Some({song: updatedSong, prog: p, text: ""}),
      };
      Js.log2("Updated State: ", updatedState);
      ReasonReact.Update(updatedState);
    | (LeaveComment, _state) =>
      Js.log("ERROR: LEAVE COMMENT WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        TextChange(txt),
        {songList: _sl, current: Some({song: s, prog: p, text: _t})},
      ) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: p, text: txt}),
      })
    | (TextChange(_), _) =>
      Js.log("ERROR: ENTER TEXT WHEN NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self => {
    Js.log("App:render");
    <div>
      <div className="title is-3"> (Util.str("Lentil")) </div>
      <SongList
        songList=self.state.songList
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
    </div>;
  },
};