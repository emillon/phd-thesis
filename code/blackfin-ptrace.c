/* kernel/ptrace.c */
SYSCALL_DEFINE4(ptrace, long, request, long, pid, unsigned long, addr,
		unsigned long, data)
{
	struct task_struct *child = ptrace_get_task_struct(pid);
        /* ... */
	long ret = arch_ptrace(child, request, addr, data);
        /* ... */
	return ret;
}

/* arch/blackfin/kernel/ptrace.c */
long arch_ptrace(struct task_struct *child, long request,
                 long addr, long data)
{
	int ret;
	unsigned long __user *datap = (unsigned long __user *)data;

	switch (request) {
        /* ... */
	case PTRACE_PEEKTEXT: {
		unsigned long tmp = 0;
		int copied;

		ret = -EIO;

                /* ... */
                if (addr >= FIXED_CODE_START
		    && addr + sizeof(tmp) <= FIXED_CODE_END) {
			memcpy(&tmp, (const void *)(addr), sizeof(tmp));
			copied = sizeof(tmp);
		}
                /* ... */
		ret = put_user(tmp, datap);
		break;
        /* ... */
	}

	return ret;
}
