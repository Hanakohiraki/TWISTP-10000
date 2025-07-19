import { useState } from "react";
import ReactDOM from "react-dom/client";
import BootScreen from "./ui/boot";
import Menu from "./ui/menu";
import "./index.css"; // ถ้าใช้ Tailwind CSS

function App() {
  const [bootDone, setBootDone] = useState(false);

  return bootDone ? <Menu /> : <BootScreen onFinish={() => setBootDone(true)} />;
}

ReactDOM.createRoot(document.getElementById("root")!).render(<App />);
