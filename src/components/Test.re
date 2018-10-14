let component = ReasonReact.statelessComponent("Test");

/* underscores before names indicate unused variables. We name them for clarity */
let make = (~name, _children) => {
  ...component,
  render: (_self) => <button> {ReasonReact.string("Hello " ++ name ++ "!")} </button>
};