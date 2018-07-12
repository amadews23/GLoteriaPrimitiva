/*
* AUTOR: Tolo Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Septiembre del 2017
*
* Programa que muestra todos los resultados de la Loteria Primitiva 
* 	Que se encuentran en la BD gold, tabla historico
*	Usando un "TreeView" de GTK
*/

#include <stdio.h>
#include <sqlite3.h>
#include "model.h"
#include <string.h>
#include <stdlib.h>

int es_sql_ok (int resultado_consulta) {

  char *err_msg = 0;
  if (resultado_consulta != SQLITE_OK)  {
      fprintf (stderr, "SQL error: %s\n", err_msg);
      return -1;
  } else {
      return 0;
  }
}

int cuantos_rows (char *tabla) {
 
  char *sql2;
  int n_rows = -1;
  sqlite3 *db;
  sqlite3_stmt *res;
  const char *tail;
  int tamanyonombre;
  tamanyonombre = strlen (tabla);

  sql2 = (char *) malloc ((tamanyonombre + 22) * sizeof (char));

  int rc = sqlite3_open ("gold.db", &db);
  sprintf (sql2, "SELECT count(*) FROM %s", tabla);

  if (es_sql_ok (rc) == 0) {
      rc = sqlite3_prepare_v2 (db, sql2, 1000, &res, &tail);
  }
  else {
      printf ("No se encuentra bd\n");
  }
  if (es_sql_ok (rc) == 0) {
      sqlite3_step (res);
      n_rows = sqlite3_column_int (res, 0);
  }
  else {
      printf ("No se pudo ejecutar la consulta\n");
  }

  sqlite3_close (db);
  free (sql2);
  return n_rows;
}
			       //Usando estructura como vector,?¿Es correcto?
int moverse_en_tabla (char *tabla, tipovectorsorteos vectorsorteos) {
  char *sql;
  sqlite3 *db;
  sqlite3_stmt *res;
  const char *tail;
  int a = 0;

//TODO Pendiente revisar tamnyo
  sql = (char *) malloc ((42) * sizeof (char));
  sprintf (sql, "SELECT * FROM %s ;", tabla);

  int rc = sqlite3_open ("gold.db", &db);

  if (es_sql_ok (rc) == 0) {

    rc = sqlite3_prepare_v2 (db, sql, 1000, &res, &tail);

 } else {

      printf ("No fue posible mostrar resultados\n");
 }
 /* if rc=.... */

 if (es_sql_ok (rc) == 0)  {
      while (sqlite3_step (res) == SQLITE_ROW) {

	  printf ("Numero de Sorteo: %i | ", sqlite3_column_int (res, 0));
	  printf ("Fecha: %s \n", sqlite3_column_text (res, 1));
	  printf (" %i |", sqlite3_column_int (res, 2));
	  printf (" %i |", sqlite3_column_int (res, 3));
	  printf (" %i |", sqlite3_column_int (res, 4));
	  printf (" %i |", sqlite3_column_int (res, 5));
	  printf (" %i |", sqlite3_column_int (res, 6));
	  printf (" %i |", sqlite3_column_int (res, 7));
	  printf (" C: %i |", sqlite3_column_int (res, 8));
	  printf (" R: %i |\n", sqlite3_column_int (res, 9));


	  vectorsorteos[a].id = sqlite3_column_int (res, 0);
	  strcpy (vectorsorteos[a].fecha, sqlite3_column_text (res, 1));
	  vectorsorteos[a].a1 = sqlite3_column_int (res, 2);
	  vectorsorteos[a].a2 = sqlite3_column_int (res, 3);
	  vectorsorteos[a].a3 = sqlite3_column_int (res, 4);
	  vectorsorteos[a].a4 = sqlite3_column_int (res, 5);
	  vectorsorteos[a].a5 = sqlite3_column_int (res, 6);
	  vectorsorteos[a].a6 = sqlite3_column_int (res, 7);
	  vectorsorteos[a].co = sqlite3_column_int (res, 8);
	  vectorsorteos[a].re = sqlite3_column_int (res, 9);

	  a++;
	}
    } else {
      printf ("No fue posible mostrar resultados\n");
    }
  sqlite3_close (db);
  free (sql);
}
