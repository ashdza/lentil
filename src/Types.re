[%%debugger.chrome];

/* These types WILL be reflected in the backend database */

type commentLocation = float;

type comment = {
  location: commentLocation,
  content: string,
};

type song = {
  id: int,
  title: string,
  artist: string,
  url: string,
  feedback: list(comment),
};

/* These types will NOT be reflected in the backend database,
   and are only for the front-end user interaction */

type songInProgress = {
  song,
  position: float,
  enteredText: string,
};

/* App-level state */
type state = {
  songList: list(song),
  playing: option(songInProgress),
};

/* App-level actions */
type action =
  | Select(song)
  | UpdatePosition(float)
  | LeaveComment
  | CommentTextChange(string);