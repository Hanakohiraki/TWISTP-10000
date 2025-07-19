import React, { useEffect, useState } from 'react';
import Menu from './menu';

export default function Boot() {
  const [booted, setBooted] = useState(false);

  useEffect(() => {
    const timeout = setTimeout(() => setBooted(true), 2000); // แสดง Boot 2 วิ
    return () => clearTimeout(timeout);
  }, []);

  return (
    <div className="w-screen h-screen bg-black text-white flex items-center justify-center text-3xl">
      {booted ? <Menu /> : <span>TWISTP BOOT SYSTEM</span>}
    </div>
  );
}
