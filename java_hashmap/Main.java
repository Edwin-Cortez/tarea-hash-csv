import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        // Mostrar datos en consola
        System.out.println("===========================================");
        System.out.println("Estudiante: Edwin Oswaldo Cortez Tista");
        System.out.println("Carne: 9921 24 7626");
        System.out.println("===========================================");

        // HashMap<Clave, Valor> - Base de clase
        HashMap<Integer, Estudiante> estudiantes = new HashMap<>();
        Scanner scanner = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n========== MENU HASHMAP (JAVA) ==========");
            System.out.println("1. Carga masiva desde CSV (estudiantes.csv)");
            System.out.println("2. Buscar estudiante por ID");
            System.out.println("3. Eliminar estudiante por ID");
            System.out.println("4. Mostrar estudiantes actuales (Evidencia HashMap)");
            System.out.println("5. Mostrar estadisticas");
            System.out.println("6. Salir");
            System.out.print("Seleccione una opcion: ");
            opcion = scanner.nextInt();

            if (opcion == 1) {
                String archivoCsv = "estudiantes.csv";
                int cargadosExito = 0;

                // Lectura del archivo usando bloques try-with-resources nativos de Java
                try (BufferedReader br = new BufferedReader(new FileReader(archivoCsv))) {
                    String linea;
                    boolean primeraLinea = true;

                    while ((linea = br.readLine()) != null) {
                        if (linea.trim().isEmpty()) continue;
                        if (primeraLinea) {
                            primeraLinea = false; // Ignoramos la linea de encabezado del CSV
                            continue;
                        }

                        // Separamos los datos por comas
                        String[] datos = linea.split(",");
                        if (datos.length == 6) {
                            int id = Integer.parseInt(datos[0].trim());
                            String nombre = datos[1].trim();
                            String carrera = datos[2].trim();
                            int semestre = Integer.parseInt(datos[3].trim());
                            double gpa = Double.parseDouble(datos[4].trim());
                            int skillScore = Integer.parseInt(datos[5].trim());

                            // VALIDAR DUPLICADOS
                            if (estudiantes.containsKey(id)) {
                                System.out.println("Error: ya existe un estudiante con el ID " + id + " (Omitido).");
                            } else {
                                // INSERTAR en el HashMap nativo
                                estudiantes.put(id, new Estudiante(id, nombre, carrera, semestre, gpa, skillScore));
                                cargadosExito++;
                            }
                        }
                    }
                    System.out.println("\n>>> Carga masiva finalizada. Se cargaron " + cargadosExito + " estudiantes exitosamente.");

                } catch (IOException e) {
                    System.out.println("Error: No se pudo abrir o leer el archivo " + archivoCsv);
                    System.out.println("Nota: Asegurate de colocar el archivo estudiantes.csv en la raiz o carpeta de ejecucion.");
                }
            }
            else if (opcion == 2) {
                // BUSCAR - Basado en el código original
                System.out.print("Ingrese ID a buscar: ");
                int buscarId = scanner.nextInt();

                if (estudiantes.containsKey(buscarId)) {
                    Estudiante estudiante = estudiantes.get(buscarId);
                    System.out.println("\n=== ESTUDIANTE ENCONTRADO ===");
                    System.out.println(estudiante);
                } else {
                    System.out.println("No existe estudiante.");
                }
            }
            else if (opcion == 3) {
                // ELIMINAR - Basado en el código original
                System.out.print("Ingrese ID a eliminar: ");
                int eliminarId = scanner.nextInt();

                if (estudiantes.containsKey(eliminarId)) {
                    estudiantes.remove(eliminarId);
                    System.out.println("\nEstudiante eliminado.");
                } else {
                    System.out.println("No existe estudiante para eliminar.");
                }
            }
            else if (opcion == 4) {
                // MOSTRAR HASHMAP - Código original de la clase
                System.out.println("\n=== ESTUDIANTES ACTUALES ===");
                if (estudiantes.isEmpty()) {
                    System.out.println("El HashMap esta vacio.");
                }
                for (Integer key : estudiantes.keySet()) {
                    System.out.println("-------------------");
                    System.out.println(estudiantes.get(key));
                }
            }
            else if (opcion == 5) {
                // ESTADISTICAS - Código original de la clase
                System.out.println("\n=== ESTADISTICAS ===");
                System.out.println("Total estudiantes: " + estudiantes.size());
            }
            else if (opcion == 6) {
                System.out.println("Saliendo del programa...");
            }
            else {
                System.out.println("Opcion invalida.");
            }

        } while (opcion != 6);

        scanner.close();
    }
}