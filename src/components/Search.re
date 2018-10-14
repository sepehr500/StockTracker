type state = {
  inputText: string
};

type action = Change(string);

let component = ReasonReact.reducerComponent("Search");


let make = (_children) => {
  ...component,
  initialState: () => {inputText: ""},
  reducer: (_action: action, state: state) => ReasonReact.Update(state),
  render: self => {
    <div>
        <input 
        value=self.state.inputText 
        onChange=(
          event => self.send(Change(ReactEvent.Form.target(event)##value))
        )
        />
    </div>;
  },
}


  
