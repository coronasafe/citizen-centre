let str = React.string;
[%bs.raw {|require("./QuizComponent.css")|}];

type page =
  | Quiz
  | Complete;

type state = {
  page,
  quizQuestions: array(Question.t),
  selectedAnswer: option(AnswerOption.t),
  answerInput: string,
  selectedQuestion: int,
};

let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;

let updateAnswer = (setState, answer, _event) => {
  setState(state => {...state, selectedAnswer: Some(answer)});
};

let updateInput = (setState, answerInput) => {
  setState(state => {...state, answerInput});
};

let updateDateInput = (setState, dateInput) => {
  switch(dateInput){
    | Some(date) => updateInput(setState, date |> Js.Date.toISOString)
    | _ => updateInput(setState, "")
  }
};

let updateUserAnswer = (setState, state) => {
  let question =
    state.quizQuestions |> ArrayUtils.getOpt(state.selectedQuestion);
  switch (question) {
  | Some(question) =>
    let newQuestion =
      switch (state.selectedAnswer) {
      | Some(answer) =>
        question
        |> Question.updateAnswer(
             answer |> AnswerOption.title |> UserAnswer.makeShortAnswer,
           )
      | None =>
        question
        |> Question.updateAnswer(
             state.answerInput |> UserAnswer.makeShortAnswer,
           )
      };
    setState(state =>
      {
        ...state,
        quizQuestions:
          state.quizQuestions
          |> Question.replace(state.selectedQuestion, newQuestion),
      }
    );
  | _ => print_endline("Unhandled Exception")
  };
};

let showSelectedAnswer = state => {
  switch (state.selectedAnswer) {
  | Some(answer) =>
    <div className="pt-8 md:pt-12">
      <h2 className="font-bold mb-2 leading-tight ">
        {answer |> AnswerOption.title |> str}
      </h2>
    </div>
  | None => React.null
  };
};

let showQuestion = (quiz, question, setState, state, totalQuestions) => {
  <div className="pt-4 pb-6 pl-3 pr-4 md:px-0">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <div
        className="inline-flex leading-tight text-sm text-orange-800 font-semibold bg-orange-200 py-1 px-1 rounded">
        <p className="mr-1">
          {(state.selectedQuestion + 1 |> string_of_int)
           ++ " of "
           ++ (totalQuestions |> string_of_int)
           ++ " -"
           |> str}
        </p>
        <p> {quiz |> Quiz.title |> str} </p>
      </div>
      <h1 className="font-bold pt-1 pb-2 leading-tight break-words">
        {question |> Question.title |> str}
      </h1>
      <div>
        {switch (question |> Question.mode) {
         | "text" =>
           <input
             className="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
             value={state.answerInput}
             onChange={evt => valueFromEvent(evt) |> updateInput(setState)}
           />
         | _ =>
           question
           |> Question.answerOptions
           |> Array.map(answer => {
                <div key={answer |> AnswerOption.title}>
                  <button
                    className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3 w-full"
                    onClick={updateAnswer(setState, answer)}>
                    {answer |> AnswerOption.title |> str}
                  </button>
                </div>
              })
           |> React.array
         }}
      </div>
    </div>
    <div> {showSelectedAnswer(state)} </div>
  </div>;
};

let showSuccess = (quiz, state) => {
  <div className="px-3 md:px-0 py-4 ">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <h2 className="text-green-600 leading-tight">
        {quiz |> Quiz.successMessage |> str}
      </h2>
      <p>
        {"Your Response:" |> str}
        {state.quizQuestions
         |> Array.map(question =>
              <p>
                {(
                   switch (question |> Question.userAnswer |> UserAnswer.value) {
                   | Some(answer) =>
                     switch (answer) {
                     | UserAnswer.ShortText(text) => text
                     | Number(num) => num |> string_of_int
                     | Date(d) => d |> Js.Date.toDateString
                     | MultiChoice(choices) =>
                       choices
                       |> Array.map(a => a |> AnswerOption.title)
                       |> Js.Array.joinWith(",")
                     }
                   | None => ""
                   }
                 )
                 |> str}
              </p>
            )
         |> React.array}
      </p>
      <a
        href={quiz |> Quiz.readMore}
        target="_blank"
        className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3">
        {"Read More" |> str}
      </a>
    </div>
    <button
      onClick={_ => ReasonReactRouter.push("/")}
      className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-10">
      <span className="mr-1">
        <svg
          className="w-4"
          xmlns="http://www.w3.org/2000/svg"
          viewBox="0 0 24 24">
          <path
            fill="currentColor"
            d="M23.6 10.12L20.9 8l-8.27-6.46a1 1 0 0 0-1.24 0L3.14 8 .4 10.12a1 1 0 0 0-.18 1.41 1 1 0 0 0 .8.39 1 1 0 0 0 .61-.22l1.13-.88v9a2.84 2.84 0 0 0 2.84 2.84h4.67V12.5h3.48v10.16h4.67a2.84 2.84 0 0 0 2.84-2.84v-9l1.13.88a1 1 0 0 0 .61.22 1 1 0 0 0 .8-.39 1 1 0 0 0-.18-1.42zm-4.37 9.7a.83.83 0 0 1-.83.83h-2.66V11.5a1 1 0 0 0-1-1h-5.5a1 1 0 0 0-1 1v9.16H5.6a.83.83 0 0 1-.83-.83V9.25l3.5-2.74L12 3.6l3.6 2.8 3.63 2.83z"
          />
        </svg>
      </span>
      {"Home" |> str}
    </button>
  </div>;
};

let showQuiz = (quiz, setState, state) => {
  let totalQuestions = state.quizQuestions |> Array.length;
  let currentQuestion =
    state.quizQuestions |> ArrayUtils.getOpt(state.selectedQuestion);
  let isLastQuestion = !(state.selectedQuestion < totalQuestions - 1);

  <div>
    <div>
      {switch (currentQuestion) {
       | Some(question) =>
         showQuestion(quiz, question, setState, state, totalQuestions)
       | None => React.null
       }}
    </div>
    <div className="max-w-screen-sm mx-auto">
      <div className="px-3 md:px-0 pb-4">
        {switch (state.selectedAnswer, state.answerInput != "") {
         | (_, true)
         | (Some(_), _) =>
           isLastQuestion
             ? <button
                 onClick={_ => {
                   updateUserAnswer(setState, state);
                   setState(state => {...state, page: Complete});
                 }}
                 className="btn border-2 border-green-600 bg-green-500 text-white hover:bg-green-600 hover:text-white focus:text-white focus:bg-green-600 button-xl w-full">
                 {"Complete" |> str}
               </button>
             : <Link
                 onClick={_ => {
                   updateUserAnswer(setState, state);
                   setState(state =>
                     {
                       ...state,
                       selectedAnswer: None,
                       answerInput: "",
                       selectedQuestion:
                         switch (
                           state.selectedAnswer,
                           state.quizQuestions
                           |> ArrayUtils.getOpt(state.selectedQuestion),
                         ) {
                         | (Some(answer), _) =>
                           answer |> AnswerOption.nextQues
                         | (_, Some(question)) =>
                           question |> Question.nextQues
                         | _ => 0
                         },
                     }
                   );
                 }}
                 className="btn border-2 border-gray-800 bg-orange-100 hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl w-full">
                 {"Next Question" |> str}
                 <span className="ml-2">
                   <svg
                     className="w-5"
                     xmlns="http://www.w3.org/2000/svg"
                     viewBox="0 0 24 24">
                     <path
                       fill="currentColor"
                       d="M19.92 12.38a1 1 0 0 0 0-.76 1 1 0 0 0-.21-.33l-7-7a1 1 0 0 0-1.42 1.42l5.3 5.3H5a1 1 0 0 0 0 2h11.6l-5.3 5.3a1 1 0 1 0 1.42 1.42l7-7a1 1 0 0 0 .21-.33z"
                     />
                   </svg>
                 </span>
               </Link>
         | (_, _) => React.null
         }}
      </div>
    </div>
  </div>;
};

[@react.component]
let make = (~quiz) => {
  let questions = quiz |> Quiz.questions;
  let (state, setState) =
    React.useState(() =>
      {
        selectedAnswer: None,
        page: Quiz,
        quizQuestions: questions,
        selectedQuestion: 0,
        answerInput: "",
      }
    );

  <div>
    {switch (state.page) {
     | Quiz => showQuiz(quiz, setState, state)
     | Complete => showSuccess(quiz, state)
     }}
  </div>;
};
