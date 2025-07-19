import { app, BrowserWindow } from 'electron';
import * as path from 'path';
import * as url from 'url';

const isDev = !app.isPackaged;

function createWindow() {
  const win = new BrowserWindow({
    width: 1280,
    height: 720,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'), // ใส่ถ้ามี preload
      nodeIntegration: true,
      contextIsolation: false,
    },
  });

  if (isDev) {
    // เปิดเว็บเซิร์ฟเวอร์ตอน dev
    win.loadURL('http://localhost:5173');
    win.webContents.openDevTools(); // เปิด DevTools ให้อัตโนมัติ
  } else {
    // โหลดไฟล์จาก dist ตอน production
    win.loadURL(
      url.format({
        pathname: path.join(__dirname, 'dist/index.html'),
        protocol: 'file:',
        slashes: true,
      })
    );
  }
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
