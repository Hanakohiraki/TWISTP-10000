import React from 'react'

export default function MenuScreen() {
  return (
    <div className="w-screen h-screen bg-gradient-to-br from-black via-gray-800 to-black text-white flex flex-col items-center justify-center space-y-4">
      <h1 className="text-5xl font-bold">Main Menu</h1>
      <ul className="text-2xl space-y-2">
        <li className="hover:text-blue-400 cursor-pointer">Start Game</li>
        <li className="hover:text-green-400 cursor-pointer">Settings</li>
        <li className="hover:text-red-400 cursor-pointer">Power Off</li>
      </ul>
    </div>
  )
}
