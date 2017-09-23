/*
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "widget_structure.h"
#include "widget.h"


#include <gtk/gtk.h>
extern int init_gpib_devices(sweeper_data *wdg_data);

int main(int argc, char *argv[]) {
	
	sweeper_data wdg_data;
    if (gtk_init_check(&argc, &argv) != TRUE)
    {
		fprintf(stderr,"Some errors occcured \n\r");
	}

	wdg_main(&wdg_data);
	gtk_widget_show_all(wdg_data.window_main);
	init_gpib_devices(&wdg_data);
    gtk_main();

    return 0;  	
}
