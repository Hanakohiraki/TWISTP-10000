import React from 'react'
import ReactDOM from 'react-dom/client'

const App = () => {
  return (
    <div style={{ textAlign: 'center', marginTop: '50px' }}>
      <h1>Hello from TWISTP-10000!</h1>
      <p>Electron + React + Vite</p>
    </div>
  )
}

ReactDOM.createRoot(document.getElementById('root')!).render(<App />)
