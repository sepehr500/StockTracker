type state = {inputText: string};

type action =
  | Change(string);

let component = ReasonReact.reducerComponent("Search");

let make = (~onSubmit, _children) => {
  ...component,
  initialState: () => {inputText: ""},
  reducer: action =>
    switch (action) {
    | Change(text) => (_ => ReasonReact.Update({inputText: text}))
    },
  render: self =>
    <div>
      <button onClick={_ => onSubmit(self.state.inputText) }>
        {ReasonReact.string("Search")}
      </button>
      <input
        value={self.state.inputText}
        onChange={
          event => self.send(Change(ReactEvent.Form.target(event)##value))
        }
      />
    </div>,
};