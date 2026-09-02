# Scalextrix

Simulación en tiempo real de un circuito de Scalextric desarrollada en **C++ con OpenGL moderno**. Dos coches recorren un circuito construido a partir de piezas modulares (rectas, curvas, curvas de cierre...), con iluminación dinámica, mapeo de sombras (*shadow mapping*), skybox y un sistema de cámaras conmutable.

## Características

- Circuito modular compuesto por piezas reutilizables (`RectaEstandar`, `CuartoRecta`, `MediaRecta`, `CurvaEstandar`, `CurvaInterior`, `CurvaExterior`, `CurvaCierre`).
- Dos coches controlados de forma independiente, cada uno en su propio carril.
- Renderizado con *shadow mapping* (mapa de profundidad de 2048x2048) y skybox cúbico.
- Modelos con texturas difusas, normal maps y specular/occlusion maps (carrocería, ruedas, interior del coche).
- Tres modos de cámara con transición suave (*lerp*): vista aérea y vista subjetiva de cada coche.
- Soporte de pantalla completa.

## Controles

| Tecla         | Acción                                   |
|---------------|-------------------------------------------|
| `Q`           | Acelerar coche 1                          |
| `A`           | Frenar / reducir velocidad coche 1        |
| `O`           | Acelerar coche 2                          |
| `L`           | Frenar / reducir velocidad coche 2        |
| `F1`          | Cámara aérea                              |
| `F2`          | Cámara subjetiva del coche 1              |
| `F3`          | Cámara subjetiva del coche 2               |
| `F12`         | Alternar pantalla completa                |

## Requisitos

- Windows con **Visual Studio 2019** (o superior compatible con el toolset `v142`) y soporte para C++17.
- Compilación en **x64**.
- Librerías (deben instalarse en `C:\ComputerGraphics\Tools\`, según la configuración del proyecto):
  - [GLFW](https://www.glfw.org/) (`lib-vc2019`)
  - [GLEW](http://glew.sourceforge.net/)
  - [GLM](https://github.com/g-truc/glm)
  - [FreeImage](https://freeimage.sourceforge.io/)

> Si prefieres usar otras rutas, actualiza los directorios de inclusión y librerías en las propiedades del proyecto (`Project8.vcxproj`).

## Compilación y ejecución

1. Instala las librerías indicadas arriba en `C:\ComputerGraphics\Tools\` (o ajusta las rutas del proyecto).
2. Abre `Scalextrix.sln` con Visual Studio.
3. Selecciona la configuración `Debug` o `Release` con la plataforma `x64`.
4. Compila y ejecuta (`F5` o `Ctrl+F5`).

El ejecutable generado (junto con `FreeImage.dll`) queda en `x64/Debug/` o `x64/Release/`, según la configuración elegida.

## Estructura del proyecto

```
Project8/
├── main.cpp                  # Punto de entrada
├── CGApplication.*           # Ventana (GLFW), bucle principal y eventos de entrada
├── CGModel.*                 # Lógica de la escena: física de los coches, cámaras y render
├── CGScene.*                 # Composición de la escena (circuito, coches, luces)
├── CGCamera.*                # Cámara y su matriz de vista
├── CGLight.*                 # Iluminación de la escena
├── CGMaterial.*               # Materiales de los modelos
├── CGShaderProgram.*         # Carga y gestión de shaders GLSL
├── CGSkybox.*                # Skybox cúbico
├── CGObject.* / CGModel.*    # Modelos base y geometría
├── CGPiece.*                 # Piezas base del circuito
├── Circuito.*                # Definición del circuito y ruta (waypoints)
├── Car.* / Car_pieces.*      # Modelo del coche y sus piezas
├── Piezas_pista.cpp          # Piezas de pista disponibles
├── RectaEstandar, MediaRecta, CuartoRecta,
│   CurvaEstandar, CurvaInterior, CurvaExterior, CurvaCierre  # Piezas modulares del circuito
├── shaders/                  # Shaders GLSL (escena y skybox)
└── textures/                 # Texturas del circuito, coches y skybox
```

## Tecnologías

- C++17
- OpenGL 4.x (vía GLEW)
- GLFW (gestión de ventana y entrada)
- GLM (álgebra lineal para gráficos)
- FreeImage (carga de texturas)
- GLSL (shaders de vértices y fragmentos)

## Autor

Rubén Conde Quintero
