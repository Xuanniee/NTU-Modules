import React, { useState } from "react";
import "./App.css";

const COLORS = ["pink", "green", "blue", "yellow", "purple"];

function App() {
  const [backgroundColor, setBackgroundColor] = useState(COLORS[0]);
  // State Variable to keep track of the number of types bg has been changed
  const [numBgChanges, setNumBgChanges] = useState(0)

  const onButtonClick = (color) => () => {
    setBackgroundColor(color);
    setNumBgChanges(numBgChanges + 1)
  };

  return (
    <div
      className="App"
      style={{
        backgroundColor,
      }}
    >
      {COLORS.map((color) => (
        <button
          type="button"
          key={color}
          onClick={onButtonClick(color)}
          className={backgroundColor === color ? "selected" : ""}
        >
          {color}
        </button>
      ))}

      <h1>Number of Changes: {numBgChanges}</h1>
    </div>
  );
}

export default App;