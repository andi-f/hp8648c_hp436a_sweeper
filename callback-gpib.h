extern int set_mode_hp436a(char *mode);
extern int set_mode_hp8648c(int mode, int mod, int output);
extern int set_frequency_hp8648c(gdouble frequency);
extern int set_level_hp8648c(gdouble level);


extern double strip_answer(char *answer, char *para);
extern int init_gpib_devices(sweeper_data *wdg_data);

extern uint16_t swap_uint16( uint16_t val );

extern hp436a_record hp436a_data;
extern hp8648c_record hp8648c_data;
extern sample_record sample_data;


