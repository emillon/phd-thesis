long arch_ptrace(struct task_struct *child, long request,
        long addr, long data)
{
    /* ... */
        if (addr >= FIXED_CODE_START
            && addr + sizeof(tmp) <= FIXED_CODE_END) {
#if FIX
        copy_from_user_page(0, 0, 0, &tmp,
                (const void *)(addr), sizeof(tmp));
#else
        memcpy(&tmp, (const void *)(addr), sizeof(tmp));
#endif
        copied = sizeof(tmp);
    /* ... */
        if (addr >= FIXED_CODE_START
            && addr + sizeof(data) <= FIXED_CODE_END) {
#if FIX
        copy_to_user_page(0, 0, 0,
                (void *)(addr), &data, sizeof(data));
#else
        memcpy((void *)(addr), &data, sizeof(data));
#endif
        copied = sizeof(data);
    /* ... */
}
