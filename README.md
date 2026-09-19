# Mochi Moods / A*

Pequeño juego de mascota virtual inspirado en Tamagotchi. Mochi cuenta con siete estados y decide cómo moverse por su jardín usando el algoritmo de búsqueda A*.

## Ejecutar
python3 -m http.server 5173
Abre `index.html` directamente en el navegador o inicia un servidor estático desde esta carpeta:

```bash
python3 -m http.server 5173
```

Después visita `http://localhost:5173`.

## Estados

Explorando, Hambriento, Feliz, Cansado, Curioso, Aburrido y Dormido tienen descripciones, destinos, efectos sobre las lecturas vitales y rutas distintas. El temporizador cambia el estado automáticamente cada seis segundos; también puedes elegir un estado desde la interfaz.