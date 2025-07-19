import { useEffect, useState } from "react";
import { motion, AnimatePresence } from "framer-motion";

export default function BootScreen({ onFinish }: { onFinish: () => void }) {
  const [showLogo, setShowLogo] = useState(true);

  useEffect(() => {
    const timer = setTimeout(() => {
      setShowLogo(false);
      setTimeout(onFinish, 1000); // หน่วงก่อนเข้าหน้าเมนู
    }, 3000); // แสดงบูต 3 วินาที

    return () => clearTimeout(timer);
  }, []);

  return (
    <div className="w-screen h-screen bg-black flex items-center justify-center">
      <AnimatePresence>
        {showLogo && (
          <motion.div
            key="boot-logo"
            initial={{ opacity: 0, scale: 0.6 }}
            animate={{ opacity: 1, scale: 1 }}
            exit={{ opacity: 0, scale: 1.2 }}
            transition={{ duration: 1.2 }}
            className="text-white text-4xl font-bold font-mono tracking-widest"
          >
            TWISTP-10000
          </motion.div>
        )}
      </AnimatePresence>
    </div>
  );
}
