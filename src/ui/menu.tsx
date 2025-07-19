import { useState } from "react";

const menuItems = ["Game", "Media", "Network", "Settings", "User"];

export default function Menu() {
  const [selected, setSelected] = useState(0);

  const next = () => setSelected((selected + 1) % menuItems.length);
  const prev = () => setSelected((selected - 1 + menuItems.length) % menuItems.length);

  return (
    <div className="w-screen h-screen bg-gradient-to-br from-zinc-900 to-black text-white p-6">
      <h1 className="text-3xl font-bold mb-4">XMB Menu</h1>
      <div className="flex space-x-6 items-center justify-center mt-20">
        {menuItems.map((item, index) => (
          <div
            key={item}
            className={`text-xl px-4 py-2 rounded transition-all ${
              index === selected
                ? "bg-white text-black scale-110 font-semibold"
                : "opacity-50"
            }`}
          >
            {item}
          </div>
        ))}
      </div>
      <div className="flex justify-center mt-10 space-x-4">
        <button onClick={prev} className="bg-white text-black px-4 py-2 rounded">←</button>
        <button onClick={next} className="bg-white text-black px-4 py-2 rounded">→</button>
      </div>
    </div>
  );
}
