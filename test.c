/* mouse test by takuya matsubara */
#include "huc.h"
#incbin(pattern,"sp_pattern.bin");
#incbin(palette,"sp_palette.bin");
#incbin(bg_pattern,"bg_pattern.bin");
#incbin(bg_palette,"bg_palette.bin");
#incbin(bg_bat    ,"bg_bat.bin");

#define VRAM_SPRITE   0x6F00

main()
{
	char button,i;
	char ms_flag;
	char ms_x;
	char ms_y;
	char exist,state;
	char spx,spy;

	disp_on();
	cls();
	load_background(bg_pattern, bg_palette, bg_bat, 32, 28);
	set_font_color(15, 0);
	set_font_pal(1);
	load_default_font();
	load_vram(VRAM_SPRITE,pattern,64*64);
	init_satb();
	spr_set(0);
	spr_pattern(VRAM_SPRITE);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pal(0);
	spr_pri(1);
	set_sprpal(0, palette);
	mouse_enable();
	vsync();

	put_string("MOUSE TEST",1,1);
	put_string("EXIST  :", 1, 4);
	put_string("MOUSE X:", 1, 6);
	put_string("MOUSE Y:", 1, 8);
	put_string("BTN1(R):", 1,10);
	put_string("BTN2(L):", 1,12);
	put_string("SELECT :", 1,14);
	put_string("RUN    :", 1,16);

	spx = 256/2;
	spy = 224/2;
	while(1){
		vsync();
		exist = mouse_exists();
		button = joy(0);
		ms_x = mouse_x();
		ms_y = mouse_y();
		put_hex(exist	, 1, 10,4);	
		put_hex(ms_x	, 2, 10,6);	
		put_hex(ms_y	, 2, 10,8);	
		for(i=0; i<4; i++){
			state = button & 1;
			put_hex(state, 1, 10,(i*2)+10);
			button >>= 1;
		}
		spx -= ms_x;
		spy -= ms_y;
		spr_set(0);
		spr_x(spx);
		spr_y(spy);

		satb_update();
	}
}

