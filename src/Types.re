[%%debugger.chrome];

type comment =
  | Text(string);
/* | Audio(string); */

type feedbackLocation =
  | Exact(float);
/* | Interval(float, float); */

/* let checkFeedback = (Text(s): comment, Exact(t): feedbackLocation) => {
     (s, t);
   }; */

type feedback = {
  location: feedbackLocation,
  comment,
};

type song = {
  title: string,
  artist: string,
  url: string,
  mutable comments: list(feedback),
};

type songList = list(song);
type secs = int;

type playingSong = {
  song,
  progress: secs,
};