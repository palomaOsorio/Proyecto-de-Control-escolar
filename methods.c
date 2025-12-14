//
// Created by paloma on 8/12/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "methods.h"

Curso * cargar_archivo_cursos(int * indice, int * tam, char * nombre_archivo)
{
    FILE * archivo = fopen(nombre_archivo, "rb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    }

    int cantidad = 0;
    fread(&cantidad, sizeof(int), 1, archivo);
    *tam = cantidad + cantidad / 2;
    Curso * nuevo_arreglo = (Curso*) malloc((*tam) * sizeof(Curso));

    if(nuevo_arreglo == NULL){
        printf("Error al asignar memoria \n");
        fclose(archivo);
        return NULL;
    }

    fread(nuevo_arreglo, sizeof(Curso), cantidad, archivo);
    *indice = cantidad;
    fclose(archivo);
    printf("Se cargaron los datos correctamente\n");
    return nuevo_arreglo;

}

void guardar_archivo_cursos(Curso* curso, int total_cursos, char * nombre_archivo)
{
    FILE * archivo = fopen(nombre_archivo, "wb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(&total_cursos, sizeof(int), 1, archivo);
    if(total_cursos > 0){
        fwrite(curso, sizeof(Curso), total_cursos, archivo);
    }
    fclose(archivo);
    printf("Se guardaron correctamente los datos\n");
}

Alumno * cargar_archivo(int * indice, int * tam, char * nombre_archivo)
{ FILE * archivo = fopen(nombre_archivo, "rb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    int cantidad = 0;
    fread(&cantidad, sizeof(int), 1, archivo);
    *tam = cantidad + cantidad / 2;
    Alumno * nuevo_arreglo = (Alumno*) malloc((*tam) * sizeof(Alumno));
    if(nuevo_arreglo == NULL){
        printf("Error al asignar memoria \n");
        fclose(archivo);
        return NULL;
    }
    fread(nuevo_arreglo, sizeof(Alumno), cantidad, archivo);
    *indice = cantidad;
    fclose(archivo);
    printf("Se cargaron los datos correctamente\n");
    return nuevo_arreglo;

}


void guardar_archivo(Alumno* alumnos, int total_alumnos, char * nombre_archivo)
{
    FILE * archivo = fopen(nombre_archivo, "wb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(&total_alumnos, sizeof(int), 1, archivo);
    if(total_alumnos > 0){
        fwrite(alumnos, sizeof(Alumno), total_alumnos, archivo);
    }
    fclose(archivo);
    printf("Se guardaron correctamente los datos\n");
}

int leer_entero(char *mensaje) {
    char buffer[50];
    char *endptr;
    long valor;

    while (1) {
        printf("%s", mensaje);
        fgets(buffer, 50, stdin);

        valor = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\n') {
            printf("Entrada invalida. Intenta otra vez.\n");
        } else {
            return (int)valor;
        }
    }
}

void leer_cadena(char *mensaje, char *cadena, int tam) {
    int i;
    while (1) {
        printf("%s", mensaje);
        fgets(cadena, tam, stdin);

        cadena[strcspn(cadena, "\n")] = '\0';

        for (i = 0; cadena[i]; i++) {
            if (!isalpha(cadena[i]) && cadena[i] != ' ') {
                printf("Solo letras.\n");
                break;
            }
        }

        if (cadena[i] == '\0')
            return;
    }
}
float leer_flotante()
{
    float valor;
    int leidos;
    char c;

    do {
        leidos = scanf("%f", &valor);

        if (leidos != 1) {
            printf("Entrada inválida. Intente de nuevo: ");

            // limpiar buffer
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } while (leidos != 1);

    return valor;
}

    Curso crear_curso()
{
    Curso c;
    leer_cadena("Nombre del curso:",c.nombre,30 );
    leer_cadena("Nombre del profesor:",c.profesor,50 );
    c.clave = leer_entero("Clave del curso:");
    c.total_inscritos = 0;


     return c;
}


void agregar_curso(Curso **cursos, int *total_cursos){
     *cursos = (Curso *) realloc( *cursos, sizeof(Curso) * (*total_cursos +1));

    if (*cursos == NULL)
    {
        printf("Erro alocando memoria");
        exit(1);
    }
    (*cursos)[*total_cursos]= crear_curso();
    (*total_cursos)++;
    printf("Curso agregado correctamente\n");

    }

Alumno crear_alumno()
{
    Alumno a;
    leer_cadena("Nombre:",a.nombre,30);
    leer_cadena("Apellido Paterno:",a.apellido_p,30);
    leer_cadena("Apellido materno:",a.apellido_m,30);
    leer_cadena("Matricula:",a.matricula,15);
    a.calificacion = 0;
    return a;
}

void agregar_estudiante(Alumno **alumnos, int *total_alumnos)
{
    *alumnos = realloc( *alumnos, sizeof(Alumno) * (*total_alumnos +1));

    if (*alumnos == NULL)
    {
        printf("Erro alocando memoria");
        exit(1);
    }
    (*alumnos)[*total_alumnos]= crear_alumno();
    (*total_alumnos)++;
    printf("Alumno agregado correctamente");
}

int buscar_alumno_matricula(Alumno *alumnos, int total_alumnos, char *matricula)
{
    for (int i =0; i < total_alumnos; i++)
    {
        if (strcmp(alumnos[i].matricula,matricula)==0)
        {
            return i;
        }
    }
    return -1;
}

int buscar_curso(Curso *cursos, int total_cursos, int clave)
{
    for (int i=0;i< total_cursos; i++)
    {
        if (clave == cursos[i].clave)
        {
            return i;
        }
    }
    return -1;

}
void mostrar_curso(Curso c)
{
    printf("Clave: %d\n",c.clave);
    printf("Curso: %s\n", c.nombre);
    printf("Profesor: %s\n", c.profesor);
    printf("Inscritos: %d\n", c.total_inscritos);
}

void lista_cursos(Curso *cursos, int total_cursos)
{
    for (int i=0; i < total_cursos; i++)
    {
        mostrar_curso(cursos[i]);
        printf("----------------\n");
    }
}

void lista_alumnos_curso(Curso c)
{
    for (int i=0; i < c.total_inscritos; i++)
    printf("%d.Nombre: %s %s %s\n Matricula:%s\n"
        ,i+1,  c.alumnos[i].nombre, c.alumnos[i].apellido_p, c.alumnos[i].apellido_m,
        c.alumnos[i].matricula);
}

float promedio_curso(Curso c, Alumno *alumno, int total_alumnos){

    float suma = 0;


    for (int i=0; i < c.total_inscritos; i++)
    {
        for(int j=0; j<total_alumnos;j++){

            if(strcmp(c.alumnos[i].matricula, alumno[j].matricula) == 0){
                suma += alumno[j].calificacion;
            }
        }

    }

    if (c.total_inscritos == 0)
        return 0;

    return (suma/c.total_inscritos);
}

int contar_aprobados(Curso c)
{   int aprobados = 0;
    for (int i=0; i < c.total_inscritos; i++)
    {
        if (c.alumnos[i].calificacion >= 7)
        {
            aprobados++;
        }
    }
    return aprobados;
}

void inscribir_alumno(Curso *curso, Alumno alumno)
{
    if (curso->total_inscritos >= 15)
    {
        printf("El curso esta lleno");
    }
    curso->alumnos[curso->total_inscritos]= alumno;
    curso->total_inscritos++;
}

void boleta_estudiante(Alumno a)
{
    printf("Nombre:%s %s %s\n", a.nombre,a.apellido_p,a.apellido_m);
    printf("Matricula: %s\n",a.matricula);
    printf("Calificacion: %f\n",a.calificacion);
}

int curso_mas_aprobados(Curso* cursos,int total_cursos)
{
    int max =-1, pos = -1;
    for (int i=0; i < total_cursos; i++)
    {
        int aprobados =0;
        for (int j=0; j < cursos[i].total_inscritos; j++)
            if (cursos[i].alumnos[j].calificacion >= CALIF_MIN)
            {
                aprobados++;
            }
        if (aprobados > max)
        {
            max = aprobados;
            pos = i;
        }
    }
    return pos;
}
void boleta_alumno(Alumno *a)
{
    char respuesta;

    printf("Nombre del alumno:%s %s %s\n",a->nombre,a->apellido_p,a->apellido_m);
    printf("Matricula: %s\n",a->matricula);
    printf("Calificacion: %f\n",a->calificacion);

    printf("¿Desea cambiar calificación S/N: \n?" );
    scanf("%c", &respuesta);

    if (respuesta == 'S')
    {
       printf("Nueva calificacion:");
        a->calificacion = leer_flotante();
    }

}
void lista_todos_alumnos(Alumno *alumnos, int total_alumnos)
{
    if (total_alumnos == 0) {
        printf("No hay alumnos registrados.\n");
        return;
    }

    printf("\n===== LISTA DE ALUMNOS REGISTRADOS =====\n");
    for (int i = 0; i < total_alumnos; i++) {
        printf("%d) Nombre: %s %s %s | Matricula: %s \n",
               i + 1,alumnos[i].nombre,alumnos[i].apellido_p,
               alumnos[i].apellido_m,alumnos[i].matricula);
    }
    printf("========================================\n");
}