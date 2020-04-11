  [@react.component]
  let make = (~href="#", ~onClick, ~className, ~children) => {
    <a
      className
      href
      onClick={e => {
        ReactEvent.Mouse.preventDefault(e);
        ReasonReactRouter.push(href);
        onClick(e);
      }}>
      children
    </a>;
  };
