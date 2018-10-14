type stock = {
  stockSymbol: string,
  initalPrice: float,
  currentPrice: float
};

type state = {
  stocks: array(stock)
};

type action = None


let component = ReasonReact.reducerComponent("Main");


let make = (_children) => {
  ...component,

  initialState: () => {stocks: [||]},

  reducer: (_action: action, state: state) => ReasonReact.Update(state),


  render: _self => {
    <div>
        <Search />
    </div>;
  },
};