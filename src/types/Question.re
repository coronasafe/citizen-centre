type t = {
  title: string,
  description: string,
  answers: array(Answer.t),
  hint: option(string),
  imageUrl: option(string),
  mode: string,
  userAnswer: string,
  nextQues: int,
};
let make = (~title, ~description, ~imageUrl=None, ~answers, ~hint, ~mode, ~userAnswer, ~nextQues) => {
  {title, description, imageUrl, answers, hint, mode, userAnswer, nextQues};
};

let title = t => t.title;
let description = t => t.description;
let answers = t => t.answers;
let hint = t => t.hint;
let imageUrl = t => t.imageUrl;
let mode = t => t.mode;
let userAnswer = t => t.userAnswer;
let nextQues = t => t.nextQues;

let makeArray = questions => {
  questions
  |> Array.map(a =>
       make(
         ~title=a##title,
         ~description=a##description,
         ~imageUrl=a##imageUrl |> Js.Nullable.toOption,
         ~answers=a##answers |> Answer.makeArray,
         ~hint=a##hint,
         ~mode=a##mode,
         ~userAnswer=a##userAnswer,
         ~nextQues=a##nextQues,
       )
     );
};

let updateAnswer = (userAnswer, t) => {
  ...t,
  userAnswer
};

let replace = (index, q, questions) => {
  questions |> Array.mapi((i,question) => {
    i==index ?  q : question
  })
}
