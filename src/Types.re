[%%debugger.chrome];

type comment = string;

type feedbackLocation = float;

/* let checkFeedback = (Text(s): comment, Exact(t): feedbackLocation) => {
     (s, t);
   }; */

type feedback = {
  location: feedbackLocation,
  comment,
};

type song = {
  id: int,
  title: string,
  artist: string,
  url: string,
  comments: list(feedback),
};

type songList = list(song);
type secs = int;