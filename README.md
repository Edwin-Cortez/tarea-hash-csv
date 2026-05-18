# Tarea: Implementación de Tablas Hash (C++ y Java)

# ​Estudiante: Edwin Oswaldo Cortez Tista

# Carné: 9941 24 7386

# ​Este proyecto consiste en el desarrollo y análisis de estructuras de datos para el almacenamiento óptimo de registros de estudiantes mediante Tablas Hash. Se implementaron dos soluciones: una estructura manual y desde cero en C++ (utilizando encadenamiento para resolver colisiones) y una solución nativa utilizando la API estándar HashMap en Java. Ambos programas son capaces de procesar una carga masiva de datos desde un archivo separado por comas (.csv).

# ​📁 Estructura del Repositorio

# ​El repositorio está organizado de la siguiente manera para cumplir con los requisitos de la guía:

# ​cpp-hash/: Contiene el código fuente en C++ (main.cpp) y el archivo de datos de prueba (estudiantes.csv).

# ​java-hashmap/: Contiene el código de la solución en Java (Main.java, Estudiante.java) junto a su respectivo archivo .csv.

# ​evidencias/: Incluye el documento evidencia.pdf con las capturas de pantalla de la ejecución e interacción con los menús de consola.

# ​💻 Instrucciones de Ejecución

# ​1. Solución en C++

# ​Navegar a la carpeta cpp-hash/.

# ​Compilar el archivo utilizando cualquier compilador estándar de C++11 o superior (o abrir el directorio directamente en CLion).

# ​Asegurarse de que el archivo estudiantes.csv se encuentre en la misma carpeta de ejecución o de compilación (cmake-build-debug).

# ​Correr el ejecutable e interactuar con el menú en consola.

# ​2. Solución en Java

# ​Navegar a la carpeta java-hashmap/.

# ​Abrir el proyecto en un IDE como IntelliJ IDEA (o compilar desde terminal usando javac Main.java Estudiante.java).

# ​Verificar que estudiantes.csv esté ubicado en la raíz del proyecto.

# ​Ejecutar la clase Main.java para desplegar el menú interactivo.

# ​📊 Breve Comparación Técnica

# ​A nivel de desarrollo, trabajar este proyecto en los dos lenguajes me permitió analizar los dos enfoques principales de las estructuras de datos:

# ​C++ (Implementación Manual): Me obligó a diseñar toda la arquitectura lógica desde cero. Tuve que programar la función hash matemática, el arreglo estático de buckets y la gestión manual de colisiones por medio de listas enlazadas dinámicas (Nodo\*). Aunque requiere más líneas de código y un control estricto de la memoria (para evitar fugas mediante destructores), ofrece un entendimiento profundo del rendimiento a bajo nivel.

# ​Java (Uso de HashMap): Es un enfoque mucho más ágil y enfocado a la productividad. Al reutilizar la clase nativa java.util.HashMap, la lógica de las colisiones, punteros y el redimensionamiento de la tabla queda completamente oculta y optimizada por el lenguaje. Métodos directos como .put(), .get() y .remove() simplifican el desarrollo drásticamente, delegando la limpieza de memoria al Garbage Collector.

# ​En conclusión, Java es ideal para entornos de producción rápidos y seguros, mientras que C++ es fundamental para entender de raíz el comportamiento algorítmico y el uso eficiente de los recursos del sistema.

