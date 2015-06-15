/*
 * ConnMan GTK GUI
 *
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 * Author: Jaakko Hannikainen <jaakko.hannikainen@intel.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <locale.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "connection_item.h"

GtkWidget *list;

static void add_connection_item_list(GtkWidget *box) {
	GtkWidget *inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

	list = gtk_list_box_new();
	gtk_widget_set_size_request(list, 200, -1);
	gtk_container_add_with_properties(GTK_CONTAINER(inner_box), list,
			"expand", TRUE, "fill", TRUE, NULL);

	GtkWidget *buttons = gtk_toolbar_new();
	gtk_style_context_add_class(gtk_widget_get_style_context(buttons),
			"inline-toolbar");
	GtkToolItem *add_button = gtk_tool_button_new(NULL, NULL);
	gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(add_button),
			"list-add-symbolic");
	GtkToolItem *remove_button = gtk_tool_button_new(NULL, NULL);
	gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(remove_button),
			"list-remove-symbolic");
	gtk_toolbar_insert(GTK_TOOLBAR(buttons), add_button, -1);
	gtk_toolbar_insert(GTK_TOOLBAR(buttons), remove_button, -1);
	gtk_container_add(GTK_CONTAINER(inner_box), buttons);
	gtk_container_add(GTK_CONTAINER(box), inner_box);
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window, *box;
	struct connection_item item;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), _("Network Settings"));
	gtk_window_set_default_size(GTK_WINDOW(window), 524, 324);

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	item = create_connection_item();

	add_connection_item_list(box);
	gtk_list_box_insert(GTK_LIST_BOX(list), item.list_item->item, 0);
	gtk_container_add(GTK_CONTAINER(box), item.settings->box);
	gtk_container_add(GTK_CONTAINER(window), box);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int status;

	setlocale(LC_ALL, "");
	bindtextdomain(GETTEXT_PACKAGE, CONNMAN_GTK_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
