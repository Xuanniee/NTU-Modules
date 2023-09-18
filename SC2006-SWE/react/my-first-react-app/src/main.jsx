// Serves as the Entry Point into the App

import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App.jsx'
import './index.css'
import {TubbyCheering, MyGreeting, Tester, Person} from './components.jsx';

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <Person />
  </React.StrictMode>,
)
