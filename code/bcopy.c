#ifndef HAVE_MEMMOVE
#ifdef HAVE_BCOPY
#define memmove(d, s, l) bcopy((s), (d), (l))
#else
#error memmove does not exist on this platform, nor is a substitute available
#endif /* HAVE_BCOPY */
#endif /* HAVE_MEMMOVE */
