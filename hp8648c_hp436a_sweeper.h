#include <stdint.h>
#include <gtk/gtk.h>

typedef struct {
	uint controller;		//GPIB controller 0-
	uint device;			//GPIB address 0-31
	char eot;
	int ud;
}
hp436a_record;

typedef struct {
	uint controller;		//GPIB controller 0-
	uint device;			//GPIB address 0-31
	int ud;
	char eot;
	uint8_t  run_f;					//0 power 1 frequency
	uint8_t run;
	uint record_counter;	//
	gdouble f;				// frequency
	gdouble f_start;
	gdouble f_stop;
	gdouble f_step;	
	
	gdouble rl;				// level
	gdouble rl_start;
	gdouble rl_stop;
	gdouble rl_step;
}
hp8648c_record;

typedef struct	{
	gdouble level;
	gdouble avg_value;
	gdouble diff_level;
	gdouble rmsd;
	gdouble delta_value;
	gdouble sample;
	gdouble avg_count;
}sample_record;

#define GPIB_INTERFACE 0
#define HP8648C_GPIB_ADR 7
#define HP436A_GPIB_ADR 10

#define GPIB_LENGTH 16348
#define SAMPLE 100

enum{MOD_OFF, FM_INT, AM_INT, AM_EXT, Fm_EXT};
enum{RF_OFF,RF_ON};
