int strlen(char *str) {
    int i = 0;
    char *p = str;
    while (*p != '\0') {
        i++;
        p++;
    }
    return i;
}
