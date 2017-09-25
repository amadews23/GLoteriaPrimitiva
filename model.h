/*
* AUTOR: Tolo Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Septiembre del 2017
*
* Programa que muestra todos los resultados de la Loteria primitiva 
* 	Que se encuentran en la BD gold, tabla historico
*	Usando un "TreeView" de GTK
*
* Prototipos y tipos de datos para conectar a la base de datos
*
*/

#pragma once
typedef char tipofecha[15];
/*Estructura de tiposorteo */
typedef struct
{
  int id;
  tipofecha fecha;
  int a1;
  int a2;
  int a3;
  int a4;
  int a5;
  int a6;
  int co;
  int re;

} tiposorteo;
//
typedef tiposorteo tipovectorsorteos[];

/*Funcion para comprobar que todo estA bien, si es Ok devuelve 0 */
int is_sql_ok (int resultado_consulta);

/*Funcion que devuelve el numero de lineas de la tabla */
int cuantos_rows (char *tabla);

/*Funcion- Procedimiento? para desplazarse por la tabla*/
				   //Usando estructura como vector,?¿Es correcto?
int moverse_en_tabla (char *tabla, tipovectorsorteos vectorsorteos);
