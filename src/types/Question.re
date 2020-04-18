type t = {
  title: string,
  description: string,
  answerOptions: array(AnswerOption.t),
  hint: option(string),
  imageUrl: option(string),
  mode: string,
  nextQues: int,
  userAnswer: UserAnswer.t,
};
let make =
    (
      ~title,
      ~description,
      ~imageUrl=None,
      ~answerOptions=[||],
      ~hint,
      ~mode,
      ~nextQues,
      ~userAnswer,
    ) => {
  {
    title,
    description,
    imageUrl,
    answerOptions,
    hint,
    mode,
    nextQues,
    userAnswer,
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
         ~nextQues=a##nextQues,
         ~userAnswer=UserAnswer.makeDefault(),
       )
     );
};

let makeError = () => {
    title: "There seems to be some problem",
    description: "",
    imageUrl: None,
    answerOptions: [||],
    hint: None,
    mode: "error",
    nextQues: -1,
    userAnswer: UserAnswer.makeDefault(),
  };

let updateAnswer = (userAnswer, t) => {...t, userAnswer};

let replace = (index, q, questions) => {
  questions |> Array.mapi((i, question) => {i == index ? q : question});
};
