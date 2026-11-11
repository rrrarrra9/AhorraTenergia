
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// Configuración del servidor de desarrollo de React.
export default defineConfig({
  plugins: [react()],

  server: {
    proxy: {
      // Todas las peticiones que comiencen por /api
      // se enviarán al backend ASP.NET Core de Raúl.
      '/api': {
        target: 'http://localhost:5052',
        changeOrigin: true,
      },
    },
  },
})
