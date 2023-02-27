// enter to hazelnut kernel

extern void uart_init(void);
extern void uart_puts(char *s);
extern void uart_getchar(void);

void enter(void){
    uart_init();
    uart_puts("Hello, hazelnut!\n");
    while(1) {
        uart_getchar();
    }
}
