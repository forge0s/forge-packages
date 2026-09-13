/* fastfetch for ForgeOS
 * A tiny system-info splash tool, in the spirit of the real fastfetch/neofetch.
 * Prints the Rivet mascot as ASCII art next to basic system info.
 *
 * This is written against the ForgeOS kernel's freestanding environment:
 * no libc, uses the same vga_print-style approach as the kernel shell.
 * It's shipped as source + a prebuilt object, to be linked into the shell
 * as a builtin command until ForgeOS has a real userspace/ELF loader.
 */
#include "vga.h"
#include "kstring.h"

/* Rivet the anvil-bot, tiny ASCII rendition */
static const char* rivet_art[] = {
    "   ______   ",
    "  /|_||_\\`.__",
    " (   _    _ _\\",
    " =`-(_)--(_)-'",
    "   F O R G E ",
    0
};

static void print_kv(const char* key, const char* val) {
    vga_setcolor(VGA_LCYAN, VGA_BLACK);
    vga_print(key);
    vga_setcolor(VGA_LGREY, VGA_BLACK);
    vga_print(val);
    vga_print("\n");
}

void fastfetch_run(void) {
    vga_setcolor(VGA_LGREEN, VGA_BLACK);
    for (int i = 0; rivet_art[i]; i++) {
        vga_print(rivet_art[i]);
        vga_print("\n");
    }
    vga_print("\n");
    vga_setcolor(VGA_WHITE, VGA_BLACK);

    print_kv("OS:       ", "ForgeOS x86_64");
    print_kv("Kernel:   ", "forge-kernel (custom, C + asm)");
    print_kv("Shell:    ", "forge-sh (builtin)");
    print_kv("Mascot:   ", "Rivet the anvil-bot");
    print_kv("Arch:     ", "x86_64 (long mode)");
    print_kv("Filesys:  ", "ramfs (volatile)");
    print_kv("Pkg Mgr:  ", "fpkg");

    vga_setcolor(VGA_WHITE, VGA_BLACK);
}
