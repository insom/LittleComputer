__sfr __at 0x55 fiftyfive;

void main(void) {
	unsigned char ii = 0;
	unsigned char i = 0;
	while(1) {
        i++;
        for(ii = 100; ii < 200; ii++) {
            *(char *)(ii) = ii;
            fiftyfive = ii;
        }
    }
}
