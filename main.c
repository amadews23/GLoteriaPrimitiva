/*
* AUTOR: Tolo Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Septiembre del 2017
*
* Programa que muestra todos los resultados de la Loteria primitiva 
* 	Que se encuentran en la BD gold, tabla historico
*	Usando un "TreeView" de GTK
* 
*/

#include <gtk/gtk.h>
#include <stdlib.h>
#include "model.h"

enum
{
  COL_NUM = 0,
  COL_FECHA,
  COL_ONE,
  COL_TWO,
  COL_THREE,
  COL_FOUR,
  COL_FIVE,
  COL_SIX,
  COL_CO,
  COL_RE,
  NUM_COLS
};
static GtkTreeModel *
create_and_fill_model (void)
{
  GtkListStore *store;
  GtkTreeIter iter;
  int max_rows = 0;
  max_rows = cuantos_rows ("historico");
  tiposorteo *vectorsorteos;
  vectorsorteos = malloc (max_rows * sizeof (tiposorteo));

  store =
    gtk_list_store_new (NUM_COLS, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT,
			G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT,
			G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT);

  moverse_en_tabla ("historico", vectorsorteos);

  for (int a = 0; a < max_rows; a++)
    {
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, COL_NUM, vectorsorteos[a].id,
			  COL_FECHA, vectorsorteos[a].fecha, COL_ONE,
			  vectorsorteos[a].a1, COL_TWO, vectorsorteos[a].a2,
			  COL_THREE, vectorsorteos[a].a3, COL_FOUR,
			  vectorsorteos[a].a4, COL_FIVE, vectorsorteos[a].a5,
			  COL_SIX, vectorsorteos[a].a6, COL_CO,
			  vectorsorteos[a].co, COL_RE, vectorsorteos[a].re,
			  -1);
    }

  free (vectorsorteos);
  return GTK_TREE_MODEL (store);
}


static GtkWidget *
create_view_and_model (void)
{
  GtkCellRenderer *renderer;
  GtkTreeModel *model;
  GtkWidget *view;
  view = gtk_tree_view_new ();

/* --- Column #numero de sorteo --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "Sorteo",
					       renderer,
					       "text", COL_NUM, NULL);
/* --- Column #fecha de sorteo --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "Fecha",
					       renderer,
					       "text", COL_FECHA, NULL);

/* --- Column #primera cifra --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "1",
					       renderer,
					       "text", COL_ONE, NULL);


/* --- Column #segunda cifra --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "2",
					       renderer,
					       "text", COL_TWO, NULL);

/* --- Column #tercera --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "3",
					       renderer,
					       "text", COL_THREE, NULL);


/* --- Column #cuarta --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "4",
					       renderer,
					       "text", COL_FOUR, NULL);
/* --- Column #quinta --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "5",
					       renderer,
					       "text", COL_FIVE, NULL);
/* --- Column #sexta --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "6",
					       renderer,
					       "text", COL_SIX, NULL);

/* --- Column #complementario --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "CO",
					       renderer,
					       "text", COL_CO, NULL);
/* --- Column #reintegro --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
					       -1,
					       "RE",
					       renderer,
					       "text", COL_RE, NULL);



  model = create_and_fill_model ();
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  g_object_unref (model);
  return view;
}

int
main (int argc, char **argv)
{
  GtkWidget *window;
  GtkWidget *view;

  GtkWidget *vbox;
  GtkWidget *sw;

  gtk_init (&argc, &argv);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);


  gtk_container_set_border_width (GTK_CONTAINER (window), 15);

  g_signal_connect (window, "delete_event", gtk_main_quit, NULL);	
  view = create_view_and_model ();

   vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 15);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  gtk_box_pack_start (GTK_BOX (vbox),
		      gtk_label_new ("Resultados de la Primitiva"),
		      FALSE, FALSE, 0);


  sw = gtk_scrolled_window_new (NULL, NULL);

  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
				       GTK_SHADOW_ETCHED_IN);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 0);


  gtk_container_add (GTK_CONTAINER (sw), view);


  //anch x alt
  gtk_window_set_default_size (GTK_WINDOW (window), 480, 620);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
