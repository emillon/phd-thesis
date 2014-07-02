struct timeval tv;
struct timeval* ptv = &tv;
int z = gettimeofday(ptv, NULL);
