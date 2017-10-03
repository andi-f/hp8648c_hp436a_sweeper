extern int set_mode_hp436a(int ud,char *mode);
extern int set_mode_hp8648c(int ud,int mode, int mod, int output);
extern int set_frequency_hp8648c(int ud,gdouble frequency);
extern int set_level_hp8648c(int ud,gdouble level);


extern double strip_answer(char *answer, char *para);

extern uint16_t swap_uint16( uint16_t val );
