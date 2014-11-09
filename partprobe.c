/*
    partprobe - informs the OS kernel of partition layout
    Copyright (C) 2001-2002, 2007-2010 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* it's best to compile this with:
 *
 * 	 CFLAGS=-Os ./configure --disable-nls --disable-shared --disable-debug
 * 	 	    --enable-discover-only
 *
 * And strip(1) afterwards!
 */

//#include <config.h>
//#include <QDebug>
//#undef printf
//#define printf(fmt, args) QDebug("CYUtils,Debug" fmt, ##args)

#include <parted/parted.h>

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <libintl.h>


#include <locale.h>
#if ! ENABLE_NLS
# undef textdomain
# define textdomain(Domainname) /* empty */
# undef bindtextdomain
# define bindtextdomain(Domainname, Dirname) /* empty */
#endif

#undef _
#define _(msgid) gettext (msgid)

#define AUTHORS \
  "<http://git.debian.org/?p=parted/parted.git;a=blob_plain;f=AUTHORS>"

/* The official name of this program (e.g., no `g' prefix).  */
#define PROGRAM_NAME "partprobe"


/* initialized to 0 according to the language lawyers */
static int	opt_no_inform;
static int	opt_summary;

char buf[1024];
void summary (PedDisk* disk)
{
	PedPartition*	walk;

    sprintf (buf,"%s: %s partitions", disk->dev->path, disk->type->name);
	for (walk = disk->part_list; walk; walk = walk->next) {
		if (!ped_partition_is_active (walk))
			continue;

        sprintf (buf, " %d", walk->num);
		if (walk->type & PED_PARTITION_EXTENDED) {
			PedPartition*	log_walk;
			int		is_first = 1;

            sprintf (buf," <");
			for (log_walk = walk->part_list; log_walk;
			     log_walk = log_walk->next) {
				if (!ped_partition_is_active (log_walk))
					continue;
				if (!is_first)
                    sprintf (buf," ");
                sprintf (buf,"%d", log_walk->num);
				is_first = 0;
			}
            sprintf (buf, ">");
		}
	}
    sprintf (buf,"\n");
}

static int
process_dev (PedDevice* dev)
{
	PedDiskType*	disk_type;
	PedDisk*	disk;

	disk_type = ped_disk_probe (dev);
	if (!disk_type || !strcmp (disk_type->name, "loop"))
		return 1;

	disk = ped_disk_new (dev);
	if (!disk)
		goto error;
	if (!opt_no_inform) {
		if (!ped_disk_commit_to_os (disk))
			goto error_destroy_disk;
	}
    //if (opt_summary)
		summary (disk);
	ped_disk_destroy (disk);
	return 1;

error_destroy_disk:
	ped_disk_destroy (disk);
error:
	return 0;
}

//int qparted_main (int argc, char* argv[])
char* qparted_main ()
{
	int		status = 0;

    //int c;
        opt_summary = 1;

        ped_device_probe_all ();
        PedDevice *dev;
        for (dev = ped_device_get_next (NULL); dev;
             dev = ped_device_get_next (dev))
            if (process_dev (dev) == 0)
                status = 1;
    //return status;
    return buf;
}
