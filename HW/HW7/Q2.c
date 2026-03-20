// bug buster
// 


/*
char *string1;
char *string2 = "Second";
string1 = string2;
*/

// it doesnt actually copy the string, 
// it just points to the same memory location as string2. 
// So if you change string2, string1 will also change because they are pointing to the same location in memory.