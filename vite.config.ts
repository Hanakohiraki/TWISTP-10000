import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';
import path from 'path';

export default defineConfig({
  root: '.', // root โปรเจกต์หลัก
  publicDir: 'public',
  build: {
    outDir: 'dist', // React Build Output
    emptyOutDir: true,
    rollupOptions: {
      input: path.resolve(__dirname, 'public/index.html'), // HTML Entry ที่ถูกต้อง
    },
  },
  plugins: [react()],
});
