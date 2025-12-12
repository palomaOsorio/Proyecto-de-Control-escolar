#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"methods.h"

int main(void)
{
    //Arreglo dinamico para gestionar cursos
    Curso *cursos = NULL;
    int total_cursos = 0;
   // Alumno *alumnos = NULL;
    int total_alumnos = 0;
    int opcion, clave,pos;
    char matricula[15];

    int tam = 10; //

    //Leer archivo de alumnos
    Alumno * alumnos = NULL;
    alumnos = cargar_archivo(&total_alumnos, &tam, "Instituto.dat");
    if(alumnos == NULL){
        printf("Creando arreglo nuevo\n");
        tam = 10;
        alumnos = (Alumno *) malloc(tam * sizeof(Alumno));
        if(alumnos == NULL){
            printf("No hay memoria\n");
            return -1;
        }
    }

    //Leer archivo de cursos
    cursos = cargar_archivo_cursos(&total_cursos, &tam, "Cursos.dat");
    if(cursos == NULL){
        printf("Creando arreglo nuevo para cursos.\n");
        tam = 10;
        cursos = (Curso *) malloc(tam * sizeof(Curso));
        if(cursos == NULL){
            printf("No hay memoria para cursos.\n");
            return -1;
        }
    }

    printf("******************Instituo Ficticio Centarl*******************\n");
    do
    {
        printf("\nMENU DE OPCIONES\n");
        printf("1.Alta de cursos\n"
                   "2.Registar estudiante\n"
                   "3.Inscribir estudiante a un curso\n"
                   "4.Lista de estudiantes por curso\n"
                   "5.Promedio de curso\n"
                   "6.Boleta del estudiante\n"
                   "7.Lista de todos los estudiantes\n"
                   "8.Curso con mayor numero de aprobados\n"
                   "9.Guardar archivo\n"
                   "10.Salir del programa\n");

        opcion = leer_entero("Selecciona una opcion:");

        switch (opcion)
        {
        case 1:
            agregar_curso(&cursos, &total_cursos);
            break;
        case 2:
            agregar_estudiante(&alumnos, &total_alumnos);
            break;
        case 3:
            clave = leer_entero("Clave del curso");
            pos = buscar_curso(cursos, total_cursos, clave);

            if (pos == -1) {
                printf("Curso no encontrado\n");
                break;
            }

            leer_cadena("Matricula del alumno: ", matricula,15);
            int posAlumno = buscar_alumno_matricula(alumnos, total_alumnos, matricula);

            if (posAlumno == -1) {
                printf("Alumno no registrado\n");
                break;
            }

            inscribir_alumno(&cursos[pos], &alumnos[posAlumno]);
            printf("Alumno inscrito correctamente\n");
            break;
        case 4:
            clave = leer_entero("Clave del curso:");
            pos = buscar_curso(cursos, total_cursos, clave);
            if (pos == -1)
            {
                printf("Curso no encontrado\n");
            }else
            {
                lista_alumnos_curso(cursos[pos]);
            }
            break;
        case 5:
            clave = leer_entero("Clave del curso:");
            pos = buscar_curso(cursos,total_cursos,clave);
            if (pos == -1)
            {
                printf("Curso no encontrado\n");
            }else
                printf("Promedio del curso:%.2f\n", promedio_curso(cursos[pos]));
            break;
        case 6:
            leer_cadena("Matricula del alumno:", matricula,15);
            pos = buscar_alumno_matricula(alumnos, total_alumnos, matricula);
            if (pos == -1)
            {
                printf("Alumno no registrado\n");
            }else
            {
                printf("Boleta de estudiante******************\n");
                boleta_alumno(&alumnos[pos]);
            }
            break;
        case 7:
            lista_todos_alumnos(alumnos,total_alumnos);
            break;
        case 8:
            pos= curso_mas_aprobados(cursos, total_cursos);
            if (pos == -1)
            {
                printf("No hay cursos");
            }else
            {mostrar_curso(cursos[pos]);
            }
            break;
        case 9:
            guardar_archivo(alumnos, total_alumnos, "Instituto.dat");
            guardar_archivo_cursos(cursos,total_cursos, "Cursos.dat");

            break;
        case 10:
            printf("Saliendo del programa\n");

            break;
        default:
            printf("Opcion invalida:\n");
        }
    }while (opcion != 10);

        free(cursos);
        free(alumnos);
        return 0;
    }