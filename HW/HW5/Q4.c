// Bug buster question

record = 0;
int main(){
    while(record < 100)
    {
        printf("\nRecord %d", record);
        printf("\nGetting next number...");
    }
    return 0;
}

// The problem with the code above
// is that the record variable isnt characterized
// and the while loop will run indefinitely
// it is also missing the #include statement