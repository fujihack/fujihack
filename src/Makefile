# Makefile for Fujihack + Frontier
TOPL=../
-include ../config.mak
include ../Makefile

FRONTIER=$(TOPL)frontier
FRONTIER_CORE=$(FRONTIER)/src/
FRONTIER_JS=$(FRONTIER)/mjs/

HACK_BIN_DEPS=boot.o stub.o file.o main.o sys.o mem.o io.o screen.o doom.o
#HACK_BIN_DEPS+=$(addprefix $(FRONTIER_CORE),asm.o)
#HACK_BIN_DEPS+=$(addprefix $(FRONTIER_JS),mjs.o)

DOOM=/home/daniel/Documents/fdoom/doomgeneric
FILES1=dummy.o am_map.o doomdef.o doomstat.o dstrings.o d_event.o d_items.o d_iwad.o d_loop.o d_main.o d_mode.o d_net.o f_finale.o f_wipe.o g_game.o hu_lib.o hu_stuff.o info.o i_cdmus.o i_endoom.o i_joystick.o i_scale.o i_sound.o i_system.o i_timer.o memio.o m_argv.o m_bbox.o m_cheat.o m_config.o m_controls.o m_fixed.o m_menu.o m_misc.o m_random.o p_ceilng.o p_doors.o p_enemy.o p_floor.o p_inter.o p_lights.o p_map.o p_maputl.o p_mobj.o p_plats.o p_pspr.o p_saveg.o p_setup.o p_sight.o p_spec.o p_switch.o p_telept.o p_tick.o p_user.o r_bsp.o r_data.o r_draw.o r_main.o r_plane.o r_segs.o r_sky.o r_things.o sha1.o sounds.o statdump.o st_lib.o st_stuff.o s_sound.o tables.o v_video.o wi_stuff.o w_checksum.o w_file.o w_main.o w_wad.o z_zone.o w_file_stdc.o i_input.o i_video.o doomgeneric.o
FILES2=$(patsubst %, $(DOOM)/%, $(FILES1))
HACK_BIN_DEPS+=$(FILES2)

ARMCFLAGS+=-I$(FRONTIER_JS) -I$(DOOM)

#WRAPS=--wrap=_malloc_r

ARMCFLAGS+=-mcpu=cortex-a7 -include ../model/$(model).h -c -marm -O2 -I$(TOPL)/src
ARMLDFLAGS+=-Bstatic -T Linker.ld $(WRAPS) -lc -lgcc -lm

ARMCFLAGS+=-I$(FRONTIER_CORE) -DCS_PLATFORM=0

# Remove unused sections/functions/variables
# This helps cut down on size a LOT
#ARMCFLAGS+=-fdata-sections -ffunction-sections
#ARMLDFLAGS+=--gc-sections

dummy: hack.bin
	$(TOPL)/ptp/fuji -s hack.bin

hack.bin: $(HACK_BIN_DEPS) build-frontier
	$(ARMCC)-ld $(HACK_BIN_DEPS) $(ARMLDFLAGS) -lc -lgcc -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(TOPL)/frontier/emulator/frontier.o -i hack.elf -o hack.bin -s
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

# Compiling rules are defined in ../Makefile
