import React, { useState } from 'react';

// &quot; is an escape code we use to render ". Your linter will greet you with an error if you use regular quotes
function MyGreeting() {
    return (<h1>&quot;Pan Pan says hi!!&quot;</h1>)
}

// Create an Image export
function TubbyCheering() {
    // Access the base URL of the public directory using import.meta.env
    const publicBaseUrl = import.meta.env.BASE_URL;

    // Specify the path to your asset relative to the public directory
    const imagePath = 'tubby.jpg';

    // Construct the full URL of the asset
    const imageUrl = `${publicBaseUrl}${imagePath}`;

    return (<img src={imageUrl} alt="Tubby Cheering for You!!"/>)
}

// Test Component to Practice
function Tester() {
    return(
        <div>
            <h1>Test Title</h1>
            <ol className="test-list">
                <li>List Item 1</li>
                <li>List Item 2</li>
                <li>List Item 3</li>
            </ol>
            <svg >
                <circle cx="25" cy="75" r="20" stroke="green" strokeWidth="2" />
            </svg>
            <form><input type="text"/></form>
        </div>
    )
}

function CustomInput({ value, onChange }) {
    return (
      <input
        type="text"
        value={value}
        onChange={(event) => onChange(event.target.value)}
      />
    );
  }
  
  function Person() {
    const [person, setPerson] = useState({ name: 'John', age: 100 });
  
    const handleIncreaseAge = () => {
      setPerson({ ...person, age: person.age + 1 });
    };
  
    const changeName = (newName) => {
      setPerson({ ...person, name: newName });
    };
  
    // this console.log runs every time the component renders 
    // what do you think this will print?
    console.log("during render: ", person);
  
    return (
      <>
        <h1>{person.name}</h1>
        <h2>{person.age}</h2>
        <button onClick={handleIncreaseAge}>Increase age</button>
        <CustomInput value={person.name} onChange={changeName}>Name</CustomInput>
      </>
    );
  }
  



// Named Exports allows me to export multiple components at one go, but must use their names
export { TubbyCheering, MyGreeting, Tester, Person };