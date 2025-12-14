//
// Created by paloma on 8/12/25.
//
#ifndef PROYECTO_FINAL_ISS_METHODS_H
#define PROYECTO_FINAL_ISS_METHODS_H

#define cupo_max 15
#define CALIF_MIN 7

typedef struct {
    char matricula[15];
    char nombre[30] ;
    char apellido_p[30] ;
    char apellido_m[30] ;
    float calificacion ;
} Alumno ;

typedef struct {
    char nombre[30] ;
    char profesor[50] ;
    int clave ;
    int total_inscritos ;
    Alumno alumnos[15];
} Curso ;

void guardar_archivo(Alumno* alumnos, int total_alumnos, char * nombre_archivo);
Alumno * cargar_archivo(int * indice, int * tam, char * nombre_archivo);

void guardar_archivo_cursos(Curso* cursos, int total_cursos, char * nombre_archivo);
Curso * cargar_archivo_cursos(int * indice, int * tam, char * nombre_archivo);

int leer_entero(char* mensaje);
void leer_cadena(char* mensaje, char* cadena, int tamano);
float leer_flotante();
Curso crear_curso();
void agregar_curso(Curso **cursos, int *total_cursos);
Alumno crear_alumno();
void agregar_estudiante(Alumno **alumnos, int *total_alumnos);

int buscar_alumno_matricula(Alumno*, int, char* );
int buscar_curso(Curso *cursos, int total_cursos, int clave);
void mostrar_curso(Curso c);
void lista_cursos(Curso *cursos, int total_cursos);
void lista_alumnos_curso(Curso c);
float promedio_curso(Curso c, Alumno *alumnos,int total_alumnos);
int contar_aprobados(Curso c);
void inscribir_alumno(Curso *curso, Alumno alumno);
int curso_mas_aprobados(Curso *cursos, int total_cursos);
void boleta_alumno(Alumno *a);
void lista_todos_alumnos(Alumno* alumnos, int total_alumnos);

#endif //PROYECTO_FINAL_ISS_METHODS_H