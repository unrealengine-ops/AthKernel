// drivers/screen.cpp
typedef unsigned int uint32_t;

// We make this non-const so we can adjust it if needed
static uint32_t* framebuffer = (uint32_t*)0x3C000000; 
static int pitch = 1024; 
static int height = 768;

extern "C" void set_framebuffer_base(uint32_t* addr) {
    // If we want to dynamically override it later
    if(addr != 0) framebuffer = addr;
}

extern "C" void draw_pixel(int x, int y, uint32_t color) {
    // A safer pitch calculation using the standard row alignment
    // Many hardware framebuffers pad rows to multiples of 256 or 512 bytes
    framebuffer[y * pitch + x] = color;
}

extern "C" void draw_rect(int x1, int y1, int x2, int y2, uint32_t color) {
    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            draw_pixel(x, y, color);
        }
    }
}