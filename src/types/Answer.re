type t = {
  option: string,
  title: string,
  description: array(string),
  imageUrl: option(string),
  youtubeUrl: option(string),
  correctAnswer: bool,
  nextQues: int,
};

let make =
    (
      ~option,
      ~title,
      ~description=[||],
      ~imageUrl=None,
      ~youtubeUrl=None,
      ~correctAnswer,
      ~nextQues,
    ) => {
  {option, title, description, imageUrl, youtubeUrl, correctAnswer, nextQues};
};

let option = t => t.option;
let title = t => t.title;
let description = t => t.description;
let youtubeUrl = t => t.youtubeUrl;
let imageUrl = t => t.imageUrl;
let correctAnswer = t => t.correctAnswer;
let nextQues = t => t.nextQues;

let makeArray = answers => {
  answers
  |> Array.map(a => {
       make(
         ~option=a##option,
         ~title=a##title,
         ~description=a##description |> Array.map(d => d),
         ~imageUrl=a##imageUrl |> Js.Nullable.toOption,
         ~youtubeUrl=a##youtubeUrl |> Js.Nullable.toOption,
         ~correctAnswer=a##correctAnswer,
         ~nextQues=a##nextQues,
       )
     });
};
