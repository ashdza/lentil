[%%debugger.chrome];

open Types;

module Player = ReReactPlayer.Player;

/* render header with an onSelect function */
let renderSongHeader = (song: song, onSelect, style) =>
  <div className=style>
    <div className="song-title clickable" onClick=(_e => onSelect(song))>
      (Util.str(song.title))
    </div>
    <div className="song-artist"> (Util.str(song.artist)) </div>
    <div className="comments">
      (Util.str("Comments: " ++ string_of_int(List.length(song.feedback))))
    </div>
  </div>;

/* render list of comments for in-progress song, using current position */
let renderCommentsRoll = (songInProgress: songInProgress, style) =>
  <div className=style>
    <Util.Text label="Comments (auto-highlight):" style="bold" />
    (
      songInProgress.song.feedback
      /* |. Util.dropWhile(_c => c.location < songInProgress.prog -. 2.0) */
      |> List.map((c: Types.comment) =>
           <Util.Text
             label=(c.content ++ Format.sprintf(" (at %0.1f)", c.location))
             style=(
               c.location >= songInProgress.position
               -. 2.0
               && c.location <= songInProgress.position
               +. 2.0 ?
                 "comment highlight" : "comment"
             )
           />
         )
      |> Array.of_list
      |> ReasonReact.array
    )
  </div>;

/* render the audio-player + comment-editor on in-progress song.
   Takes a send action for the 3 messages:
   UpdateProgress, TextChange, and LeaveComment */
let renderPlayerOnCurrentSong =
    (currentlyPlaying, send: action => unit, style) => {
  let {song: s, position: p, enteredText: t} = currentlyPlaying;
  <div className=style>
    <Util.Text
      style="italic"
      label="If a SoundCloud Ad blocks Play/Pause, click 'X' to close the Ad."
    />
    <Player
      url=s.url
      onProgress=((progress: Player.secs) => send(UpdatePosition(progress)))
      progressInterval=100
    />
    <Util.Text
      label=("Edit Comment @ Position: " ++ Format.sprintf("%0.1f", p))
      style="bold"
    />
    <textarea
      className="comment-entry"
      cols=60
      rows=5
      value=t
      onChange=(
        ev => send(CommentTextChange(ReactEvent.Form.target(ev)##value))
      )
    />
    <Util.Button
      label="Submit"
      onClick=(_event => send(LeaveComment))
      disabled=(t == "")
    />
  </div>;
};

/* Given song + another in-progress song, render appropriately */
let renderSong = (song: Types.song, currentlyPlaying, send: action => unit) => {
  let header = renderSongHeader(song, s => send(Select(s)), "song-header");
  let (player, scroll) =
    switch (currentlyPlaying) {
    | Some({song: s, position: _p, enteredText: _t} as inProgress)
        when s.id == song.id => (
        renderPlayerOnCurrentSong(inProgress, send, "song-player"),
        renderCommentsRoll(inProgress, "song-comments"),
      )
    | _ => (ReasonReact.null, ReasonReact.null)
    };
  <div className="song-grid"> header player scroll </div>;
};

/* render a list of songs, one (or none) of which is currently playing */
let renderSongList = (songList, currentlyPlaying, send) =>
  List.map(s => renderSong(s, currentlyPlaying, send), songList)
  |> Array.of_list
  |> ReasonReact.array;

/* update a song with new feedback at some location */
let addFeedbackToSong = (content, loc, song: Types.song) => {
  let c: Types.comment = {location: loc, content};
  let compareComments = (c1: Types.comment, c2: Types.comment) =>
    Pervasives.compare(c1.location, c2.location);
  {
    ...song,
    feedback: Belt.List.add(song.feedback, c) |> List.sort(compareComments),
  };
};

/* Demo-able stateless renders. State / reducer React component is at App level */
module Demo = {
  let exampleSong: song = {
    id: 1,
    title: "Young and Beautiful Love",
    artist: "Ashley D'Souza",
    url: "https://soundcloud.com/ashley-dsouza-106423765/young-and-beautiful-love",
    feedback: [
      {location: 6.3, content: "Nice gentle piano intro!"},
      {location: 20.1, content: "Lovely, breathy entrance!"},
      {
        location: 48.0,
        content: "Make that first -- \"I\" told my love -- more clear",
      },
    ],
  };

  let demoSongHeader = renderSongHeader(exampleSong, Util.ignore, "");

  let demoRenderSongNotCurrent = renderSong(exampleSong, None, Util.ignore);

  let songCurrentlyPlaying =
    Some({
      song: exampleSong,
      position: 13.293,
      enteredText: "Editing comment ...",
    });

  let demoRenderSongCurrent =
    renderSong(exampleSong, songCurrentlyPlaying, Util.ignore);

  let initialSongs: list(song) = [
    exampleSong,
    {
      id: 3,
      title: "Sunday Morning",
      artist: "Maroon 5",
      url: "https://soundcloud.com/maroon-5/sunday-morning",
      feedback: [],
    },
    {
      id: 4,
      title: "Payphone",
      artist: "Maroon 5",
      url: "https://soundcloud.com/maroon-5/payphone-clean",
      feedback: [],
    },
  ];

  let demoRenderSongList =
    renderSongList(initialSongs, songCurrentlyPlaying, Util.ignore);
};