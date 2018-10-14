type stock = {
  stockSymbol: string,
  initalPrice: float,
  currentPrice: float
};


type state = {
  stocks: array(stock)
};

type action = Search(string)


let component = ReasonReact.reducerComponent("Main");


let make = (_children) => {
  ...component,

  initialState: () => {stocks: [||]},

  reducer: (action: action, state: state) => 
    switch(action){
      | Search(text) => ReasonReact.Update(state)
    },
  render: self => {
    <div>
        <Search onSubmit=(
          searchStr => self.send(Search(searchStr))
        )/>
    </div>;
  },
};