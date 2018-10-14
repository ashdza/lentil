[%%debugger.chrome];

module Player = ReReactPlayer.Player;

type songInProgress = {
  song: Types.song,
  prog: float,
  text: string,
};

type state = {
  songList: Types.songList,
  current: option(songInProgress),
};

type action =
  | Select(Types.song)
  | UpdateProgress(float)
  | LeaveComment
  | TextChange(string);

let string_of_action = a =>
  switch (a) {
  | Select(s) => "Select: " ++ s.title
  | UpdateProgress(t) => "UpdateProgress: " ++ string_of_float(t)
  | LeaveComment => "LeaveComment"
  | TextChange(s) => "TextChange: " ++ s
  };

let component = ReasonReact.reducerComponent("App");

let addFeedbackToSong = (comment, loc, song: Types.song) => {
  let c: Types.feedback = {location: loc, comment};
  let compareComments = (c1: Types.feedback, c2: Types.feedback) =>
    Pervasives.compare(c1.location, c2.location);
  {
    ...song,
    comments: Belt.List.add(song.comments, c) |> List.sort(compareComments),
  };
};

let renderPlayerIfCurrentSong = (current, send, song: Types.song) =>
  switch (current) {
  | Some({song: s, prog: p, text: t}) when s.id == song.id =>
    <div className=Styles.playerEditor>
      <Player
        url=s.url
        onProgress=(
          (progress: Player.secs) => send(UpdateProgress(progress))
        )
        progressInterval=100
      />
      <Util.Text label=("Position: " ++ string_of_float(p)) />
      <textarea
        cols=80
        rows=5
        value=t
        onChange=(
          ev => {
            let newText = ReactEvent.Form.target(ev)##value;
            send(TextChange(newText));
          }
        )
      />
      <Util.Button
        label="Comment"
        onClick=(_event => send(LeaveComment))
        disabled=(t == "")
      />
    </div>
  | _ => ReasonReact.null
  };

let make = (~initialSongs: Types.songList, _children) => {
  ...component,
  initialState: () => {songList: initialSongs, current: None},
  reducer: (action: action, state: state) => {
    Js.log(string_of_action(action));
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
      Js.log2("UpdateProgress: ", playedSec);
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec, text: t}),
      });
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        LeaveComment,
        {songList: sl, current: Some({song: s, prog: p, text: txt})},
      ) =>
      Js.log4("LeaveComment: ", s.title, txt, p);
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
    };
  },
  render: self =>
    <div>
      <div className=Styles.appTitle> (Util.str("Lentil")) </div>
      <SongList
        songList=self.state.songList
        onSongSelect=((s: Types.song) => self.send(Select(s)))
        customRender=(
          renderPlayerIfCurrentSong(self.state.current, self.send)
        )
      />
    </div>,
};