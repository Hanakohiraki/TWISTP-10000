// main.ts (สำหรับ Electron)
import { app, BrowserWindow } from 'electron';
import path from 'path';
import { fileURLToPath } from 'url';

// กรณีใช้ ESM
const __dirname = path.dirname(fileURLToPath(import.meta.url));

function createWindow() {
  const win = new BrowserWindow({
    width: 1280,
    height: 720,
    fullscreen: true,
    autoHideMenuBar: true,
    webPreferences: {
      // preload: path.join(__dirname, 'preload.js') // ถ้ามี preload
    }
  });

  // ❌ อย่าใช้ Dev server แล้ว
  // win.loadURL('http://localhost:5173');

  // ✅ โหลดไฟล์ index.html ที่ build แล้ว
  win.loadFile(path.join(__dirname, 'dist', 'index.html'));
}

app.whenReady().then(() => {
  createWindow();
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit();
});
