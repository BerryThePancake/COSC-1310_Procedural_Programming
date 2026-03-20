// finding the bug

int array[10];
int x = 1;
int main(void)
{
    for (x=1;x<=10;x++)
        array[x] = 99;
    return 0;
}


// the loop is trying to access array[10] 
//which is out of bounds, 
//since the array only has indices 0-9