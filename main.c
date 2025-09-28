#include <lpc17xx.h>

#define RS_CTRL 0x08000000 // P0.27, 1<<27
#define EN_CTRL 0x10000000 // P0.28, 1<<28
#define DT_CTRL 0x07800000 // P0.23 to P0.26 data lines, F<<23
#define BUZZER_PIN (1 << 15)

unsigned long int temp1 = 0, temp2 = 0, i, j, r, k, clkw[4] = {0x6, 0xc, 0x9, 0x3}, anticlkw[4] = {0x3, 0x9, 0xc, 0x6}, timeout = 10000000;
unsigned char flag1 = 0, flag2 = 0, key;
int pass[4] = {7, 4, 6, 2};
unsigned char msg[] = {"authenticated successfully"};
unsigned char msg2[] = {"incorrect password"};
unsigned char msg3[] = {"incorrect password"};
unsigned int row, col, flag, x;
int a, b, c, d, count = 0, iflag = 0, ans, idx = 1;
char op;

unsigned long int var1,var2;

void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
void clockwise(void);
void delay(unsigned long int);
void anticlockwise(void);
void initBuzzer(void);
void turnOnBuzzer(void);
void turnOffBuzzer(void);

unsigned long int init_command[10];
unsigned char ascii[4][4] = {{'0', '1', '2', '3'}, {'4', '5', '6', '7'}, {'8', '9', '+', '-'}, {'!', '@', '#', '$'}};

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= ~(0x3F << 12);
    LPC_PINCON->PINSEL0 &= ~(0x3 << 30);//added p0.15 as gpio pin
    LPC_PINCON->PINSEL0 &= ~(0xF << 8);//added 0.4 to 0.7 as motor 
    LPC_PINCON->PINSEL1 &= ~((0x3 << 18) | (0x3 << 22));
    LPC_GPIO0->FIODIR |= DT_CTRL | RS_CTRL | EN_CTRL; // 0xf<<23 | 1<<27 | 1<<28;
    LPC_GPIO2->FIODIR |= 0XF << 10;
    LPC_GPIO1->FIODIR &= ~0xF << 23;
    LPC_GPIO0->FIODIR |= 0xF;
LPC_GPIO0->FIODIR |= 0xF << 4;

    initBuzzer();
    flag1 = 0;

    init_command[0] = 0x30;
    init_command[1] = 0x30;
    init_command[2] = 0x30;
    init_command[3] = 0x20;
    init_command[4] = 0x28;
    init_command[5] = 0x01;
    init_command[6] = 0x06;
    init_command[7] = 0x0c;
    init_command[8] = 0x80;

    for (i = 0; i < 9; i++)
    {
        temp1 = init_command[i];
        lcd_write();
    }
    flag1 = 1; // DATA MODE
    while (1)
    {
        if (iflag == 4)
        {
            temp1 = 0x01;
            flag1 = 0;
            lcd_write();
            temp1 = 0x80;
            lcd_write();
            flag1 = 1;
            i = 0;
            while (msg3[i] != '\0')
            {
                temp1 = msg3[i];
                lcd_write();
                i += 1;
                if (i == 16) // check for 1 characters in first line
                {
                    flag1 = 0;    // if yes
                    temp1 = 0xc0; // configure second line in command register
                    lcd_write();
                    flag1 = 1;
                }
            }
            turnOnBuzzer();
            delay(timeout);
            turnOffBuzzer();
            timeout = timeout * 2;
            iflag = 0;
						temp1 = 0x01;
						flag1 = 0;
						lcd_write();
						temp1 = 0x80;
						lcd_write();
						flag1 = 1;
        }

        while (count < 4)
        {

            for (row = 0; row < 4; row++)
            {
                flag = 0;
                LPC_GPIO2->FIOPIN = 1 << (10 + row); // sending high on ith row
                for (j = 0; j < 100; j++)
                    ;

                x = ((LPC_GPIO1->FIOPIN >> 23) & 0xf); // CHECK IF ANY COLUMN LINE IS HIGH

                if (x)
                {
										
                    // some key is pressed
                    if (x == 1) // finding col no.
                        col = 0;
                    else if (x == 2)
                        col = 1;
                    else if (x == 4)
                        col = 2;
                    else if (x == 8)
                        col = 3;
                    count++;
                    key = ascii[row][col];
                    temp1 = key;
                    lcd_write();
                    if (count == 1)
                    {
                        a = key - 0x30;
                    }
                    else if (count == 2)
                    {
                        b = key - 0x30;
                    }
                    else if (count == 3)
                    {
                        c = key - 0x30;
                    }
                    else if (count == 4)
                    {
                        d = key - 0x30;
                    }
                }
                for (i = 0; i < 500000; i++)
                    ;
            }
        }
        temp1 = 0x01;
        flag1 = 0;
        lcd_write();
        temp1 = 0x80;
        lcd_write();
        flag1 = 1;
        if (a == pass[0] && b == pass[1] && c == pass[2] && d == pass[3])
        {
						iflag=0;
            i = 0;
            while (msg[i] != '\0')
            {
                temp1 = msg[i];
                lcd_write();
                i += 1;
                if (i == 16) // check for 1 characters in first line
                {
                    flag1 = 0;    // if yes
                    temp1 = 0xc0; // configure second line in command register
                    lcd_write();
                    flag1 = 1;
                }
            }
            for (j = 0; j < 70 	; j++)
            {
                clockwise(); // Rotate the motor clockwise to open the door
            }
            delay(650000);
            for (j = 0; j < 70; j++)
            {
                anticlockwise();
            }
						LPC_GPIO0 -> FIOCLR = 0xF << 4;
        }
        else
        {
						a=0;
						b=0;
						c=0;
						d=0;
						count=0;
            iflag++;
					
        }
    }
}

void initBuzzer(void)
{
    // Set P0.15 as an output for the buzzer
    LPC_GPIO0->FIODIR |= BUZZER_PIN;
}

void turnOnBuzzer(void)
{
    // Turn on the buzzer by setting P0.15 high
    LPC_GPIO0->FIOSET |= BUZZER_PIN;
}

void turnOffBuzzer(void)
{
    // Turn off the buzzer by setting P0.15 low
    LPC_GPIO0->FIOCLR |= BUZZER_PIN;
}

void clockwise(void)
{
    for (i = 0; i < 4; i++)
    {
        LPC_GPIO0->FIOCLR = 0xF << 4;               // Clear previous output on P0.4–P0.7
        LPC_GPIO0->FIOSET = clkw[i] << 4;           // Output step pattern
        for (k = 0; k < 5000; k++);                 // Delay
    }
}


void delay(unsigned long int n)
{
    for (k = 0; k < n; k++)
        ;
}

void anticlockwise(void)
{
    for (i = 0; i < 4; i++)
    {
        LPC_GPIO0->FIOCLR = 0xF << 4;
        LPC_GPIO0->FIOSET = anticlkw[i] << 4;
        for (k = 0; k < 5000; k++);
    }
}


void lcd_write(void)
{
    temp2 = temp1 & 0xf0; // 4 - Bits to get it to least significant digit place
    temp2 = temp2 >> 4;
    port_write();
    if (!((flag1 == 0) && ((temp1 == 0x20) || (temp1 == 0x30)))) // send least significant 4 bits only when it is data/command other than 0x30/0x20
    {
        temp2 = temp1 & 0x0f;
        temp2 = temp2;
        port_write();
    }
}

void port_write(void)
{
    LPC_GPIO0->FIOPIN = temp2 << 23; // sending the ascii code
    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = RS_CTRL; // if command
    else
        LPC_GPIO0->FIOSET = RS_CTRL; // if data

    LPC_GPIO0->FIOSET = EN_CTRL; // sending a low high edge on enable input
    for (r = 0; r < 25; r++)
        ;
    LPC_GPIO0->FIOCLR = EN_CTRL;
    for (r = 0; r < 30000; r++)
        ;
}