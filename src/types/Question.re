type t = {
  title: string,
  description: string,
  answerOptions: array(AnswerOption.t),
  hint: option(string),
  imageUrl: option(string),
  mode: string,
  userAnswer: UserAnswer.t,
  nextQues: int,
};
let make =
    (
      ~title,
      ~description,
      ~imageUrl=None,
      ~answerOptions=[||],
      ~hint,
      ~mode,
      ~userAnswer,
      ~nextQues,
    ) => {
  {
    title,
    description,
    imageUrl,
    answerOptions,
    hint,
    mode,
    userAnswer,
    nextQues,
  };
};

let title = t => t.title;
let description = t => t.description;
let answerOptions = t => t.answerOptions;
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
         ~answerOptions=a##answers |> AnswerOption.makeArray,
         ~hint=a##hint,
         ~mode=a##mode,
         ~userAnswer=UserAnswer.makeDefault(),
         ~nextQues=a##nextQues,
       )
     );
};

let updateAnswer = (userAnswer, t) => {...t, userAnswer};

let replace = (index, q, questions) => {
  questions |> Array.mapi((i, question) => {i == index ? q : question});
};
