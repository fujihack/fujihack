// this is a bunch of old code
unsigned char grid[5][5][2] =
{
    {{13, 4},{14, 7},{13, 5},{14, 8},{13, 6}},
    {{15, 7},{15, 8},{15, 9},{15,10},{15,11}},
    {{14, 5},{13,12},{14, 6},{15,12},{14, 4}},
    {{13,11},{13,10},{13, 9},{13, 8},{13, 7}},
    {{15, 6},{14,10},{15, 4},{14, 9},{15, 5}}
};

unsigned char image[5][5] =
{
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}
};

void delay()
{
    for (unsigned int ra = 0; ra < 20; ra++);
}

void pixel(unsigned int x, unsigned int y)
{
    PUT32(GPIO_OUTSET, 1 << grid[x][y][0]);
    PUT32(GPIO_OUTCLR, 1 << grid[x][y][1]);
    delay();
    PUT32(GPIO_OUTCLR, 1 << grid[x][y][0]);
    PUT32(GPIO_OUTSET, 1 << grid[x][y][1]);
}

void notmain()
{
    PUT32(GPIO_DIRSET, 0xFFF0);
    PUT32(GPIO_OUTCLR, 0xE000);
    PUT32(GPIO_OUTSET, 0x1FF0);

    while (1)
    {
        for (unsigned int x = 0; x < 5; x++)
        {
            for (unsigned int y = 0; y < 5; y++)
            {
                if (image[x][y])
                {
                    pixel(x, y);
                }
            }
        }
    }
}
