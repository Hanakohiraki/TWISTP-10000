import React from 'react';

export default function Menu() {
  return (
    <div className="w-screen h-screen bg-gradient-to-r from-black to-zinc-900 text-white flex items-center px-10 space-x-10 text-xl">
      <div className="hover:scale-110 transition">🕹️ เกม</div>
      <div className="hover:scale-110 transition">🎵 เพลง</div>
      <div className="hover:scale-110 transition">🎬 วิดีโอ</div>
      <div className="hover:scale-110 transition">⚙️ ตั้งค่า</div>
    </div>
  );
}
