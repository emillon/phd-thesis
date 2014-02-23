#define FIX 0

#include "kconf.h"
#define __user
#define __rcu
#define PTRACE_PEEKTEXT            1
#define PTRACE_PEEKDATA            2
#define PTRACE_PEEKUSR             3
#define PTRACE_POKETEXT            4
#define PTRACE_POKEDATA            5
#define PTRACE_POKEUSR             6
#define PTRACE_CONT                7
#define PTRACE_KILL                8
#define PTRACE_SINGLESTEP          9
#define PTRACE_GETREGS            12
#define PTRACE_SETREGS            13
#define PTRACE_SYSCALL            24

#define PT_SYSCFG 216
#define SYSCFG_MASK 0x0007      /* SYSCFG reg */
#define TIF_SYSCALL_TRACE       0       /* syscall trace active */

#define EXIT_ZOMBIE             16

#define SIGKILL          9

#define EIO              5      /* I/O error */

#define L1_CODE_LENGTH      0x14000
#define L1_DATA_A_START     0xFF800000
#define L1_DATA_B_START     0xFF900000
#define L1_DATA_A_LENGTH      (0x8000 - 0x4000)
#define L1_DATA_B_LENGTH      0x8000
#define CONFIG_PHY_RAM_BASE_ADDRESS     0x0
#define FIXED_CODE_START        (CONFIG_PHY_RAM_BASE_ADDRESS + 0x400)
#define FIXED_CODE_END          (CONFIG_PHY_RAM_BASE_ADDRESS + 0x490)
#define TEXT_OFFSET 0

#define KERN_SOH        "\001"          /* ASCII Start Of Header */
#define KERN_WARNING    KERN_SOH "4"    /* warning conditions */

typedef unsigned long size_t;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef unsigned long pid_t;
typedef u64 cputime_t;
typedef long            __kernel_long_t;
typedef __kernel_long_t __kernel_time_t;
typedef unsigned int    __kernel_uid32_t;
typedef __kernel_uid32_t        uid_t;
typedef uid_t kuid_t;
typedef int bool;

void *memcpy(void *dest, const void *src, size_t n);
struct task_struct;
struct pt_regs {
        long orig_pc; long ipend; long seqstat; long rete;
        long retn; long retx; long pc; long rets;
        long reserved; long astat; long lb1; long lb0;
        long lt1; long lt0; long lc1; long lc0;
        long a1w; long a1x; long a0w; long a0x;
        long b3; long b2; long b1; long b0;
        long l3; long l2; long l1; long l0;
        long m3; long m2; long m1; long m0;
        long i3; long i2; long i1; long i0;
        long usp; long fp; long p5; long p4;
        long p3; long p2; long p1; long p0;
        long r7; long r6; long r5; long r4;
        long r3; long r2; long r1; long r0;
        long orig_r0; long orig_p0; long syscfg;
};

typedef struct {
    int counter;
} atomic_t;

struct llist_node {
    struct llist_node *next;
};

struct rb_node {
        unsigned long  __rb_parent_color;
        struct rb_node *rb_right;
        struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));

struct list_head {
        struct list_head *next, *prev;
};

struct hlist_head {
         struct hlist_node *first;
};

struct hlist_node {
        struct hlist_node *next, **pprev;
};

struct plist_node {
        int                     prio;
        struct list_head        prio_list;
        struct list_head        node_list;
};

struct plist_head {
        struct list_head node_list;
};

// No def..
#define NODEF(T) typedef struct {} T
#define NOSTR(T) struct T {}
NODEF(siginfo_t);
NOSTR(task_io_accounting);
NODEF(nodemask_t);
NODEF(seqcount_t);
NOSTR(rcu_head);
NOSTR(page_frag);
NOSTR(rb_root);
NODEF(pgd_t);
NODEF(atomic_long_t);
NOSTR(rw_semaphore);
struct file;
NOSTR(mm_rss_stat);
NODEF(cpumask_var_t);
NODEF(mm_context_t);
NOSTR(uprobes_state);

#define BITS_PER_BYTE           8
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)       DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
/* Places which use this should consider cpumask_var_t. */
#define NR_CPUS         CONFIG_NR_CPUS
#define DECLARE_BITMAP(name,bits) \
         unsigned long name[BITS_TO_LONGS(bits)]

typedef struct cpumask { DECLARE_BITMAP(bits, NR_CPUS); } cpumask_t;

struct seccomp { };

#include "spinlock.h" 
#include "task.h" 
#include "mm.h" 

#define pr_debug(m, ...) do{}while(0)
#define printk(m, ...) do{}while(0)

/* stubs */
int is_user_addr_valid(struct task_struct *ts, long addr, size_t sz)
{
    return 1;
}

int get_l1_code_start(void)
{
    return 0;
}


void* safe_dma_memcpy(void* dest, const void* src, size_t n)
{
}

int access_process_vm(struct task_struct *tsk, unsigned long addr,
        void *buf, int len, int write)
{
    return 0;
}

long get_reg(struct task_struct *tsk, unsigned long addr)
{
    return 0;
}

long put_reg(struct task_struct *tsk, unsigned long regno, unsigned long data)
{
    return 0;
}

int valid_signal(long data)
{
    return 1;
}

void set_tsk_thread_flag (struct task_struct *tsk, int f)
{
}

void clear_tsk_thread_flag (struct task_struct *tsk, int f)
{
}

void ptrace_disable(struct task_struct *tsk)
{
}

void ptrace_enable(struct task_struct *tsk)
{
}

void wake_up_process(struct task_struct *tsk)
{
}

int ptrace_getregs(struct task_struct *child, unsigned long *data)
{
    return 1;
}

int ptrace_request(struct task_struct *child, long request,
        unsigned long addr, unsigned long data)
{
    return 0;
}
/* end stubs */

long arch_ptrace(struct task_struct *child, long request, long addr, long data)
{
	int ret;
	unsigned long __user *datap = (unsigned long __user *)data;

	switch (request) {
		/* when I and D space are separate, these will need to be fixed. */
	case PTRACE_PEEKDATA:
		pr_debug("ptrace: PEEKDATA\n");
		/* fall through */
	case PTRACE_PEEKTEXT:	/* read word at location addr. */
		{
			unsigned long tmp = 0;
			int copied;

			ret = -EIO;
			pr_debug("ptrace: PEEKTEXT at addr 0x%08lx + %ld\n", addr, sizeof(data));
			if (is_user_addr_valid(child, addr, sizeof(tmp)) < 0)
				break;
			pr_debug("ptrace: user address is valid\n");

# if 0
			if (L1_CODE_LENGTH != 0 && addr >= get_l1_code_start()
			    && addr + sizeof(tmp) <= get_l1_code_start() + L1_CODE_LENGTH) {
				safe_dma_memcpy (&tmp, (const void *)(addr), sizeof(tmp));
				copied = sizeof(tmp);

			} else if (L1_DATA_A_LENGTH != 0 && addr >= L1_DATA_A_START
			    && addr + sizeof(tmp) <= L1_DATA_A_START + L1_DATA_A_LENGTH) {
				memcpy(&tmp, (const void *)(addr), sizeof(tmp));
				copied = sizeof(tmp);

			} else if (L1_DATA_B_LENGTH != 0 && addr >= L1_DATA_B_START
			    && addr + sizeof(tmp) <= L1_DATA_B_START + L1_DATA_B_LENGTH) {
				memcpy(&tmp, (const void *)(addr), sizeof(tmp));
				copied = sizeof(tmp);
                        else
#endif
			if (addr >= FIXED_CODE_START
			    && addr + sizeof(tmp) <= FIXED_CODE_END) {
#if FIX
                                copy_from_user_page(0, 0, 0, &tmp, (const void *)(addr), sizeof(tmp));
#else
                                memcpy(&tmp, (const void *)(addr), sizeof(tmp));
#endif
				copied = sizeof(tmp);

			} else
				copied = access_process_vm(child, addr, &tmp,
							   sizeof(tmp), 0);

			pr_debug("ptrace: copied size %d [0x%08lx]\n", copied, tmp);
			if (copied != sizeof(tmp))
				break;
			ret = put_user(tmp, datap);
			break;
		}

		/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR:
		{
			unsigned long tmp;
			ret = -EIO;
			tmp = 0;
			if ((addr & 3) || (addr > (sizeof(struct pt_regs) + 16))) {
				printk(KERN_WARNING "ptrace error : PEEKUSR : temporarily returning "
				                    "0 - %x sizeof(pt_regs) is %lx\n",
				     (int)addr, sizeof(struct pt_regs));
				break;
			}
			if (addr == sizeof(struct pt_regs)) {
				/* PT_TEXT_ADDR */
				tmp = child->mm->start_code + TEXT_OFFSET;
			} else if (addr == (sizeof(struct pt_regs) + 4)) {
				/* PT_TEXT_END_ADDR */
				tmp = child->mm->end_code;
			} else if (addr == (sizeof(struct pt_regs) + 8)) {
				/* PT_DATA_ADDR */
				tmp = child->mm->start_data;
#ifdef CONFIG_BINFMT_ELF_FDPIC
			} else if (addr == (sizeof(struct pt_regs) + 12)) {
				tmp = child->mm->context.exec_fdpic_loadmap;
			} else if (addr == (sizeof(struct pt_regs) + 16)) {
				tmp = child->mm->context.interp_fdpic_loadmap;
#endif
			} else {
				tmp = get_reg(child, addr);
			}
			ret = put_user(tmp, datap);
			break;
		}

		/* when I and D space are separate, this will have to be fixed. */
	case PTRACE_POKEDATA:
		pr_debug("ptrace: PTRACE_PEEKDATA\n");
		/* fall through */
	case PTRACE_POKETEXT:	/* write the word at location addr. */
		{
			int copied;

			ret = -EIO;
			pr_debug("ptrace: POKETEXT at addr 0x%08lx + %ld bytes %lx\n",
			         addr, sizeof(data), data);
			if (is_user_addr_valid(child, addr, sizeof(data)) < 0)
				break;
			pr_debug("ptrace: user address is valid\n");

#if 0
			if (L1_CODE_LENGTH != 0 && addr >= get_l1_code_start()
			    && addr + sizeof(data) <= get_l1_code_start() + L1_CODE_LENGTH) {
				safe_dma_memcpy ((void *)(addr), &data, sizeof(data));
				copied = sizeof(data);

			} else if (L1_DATA_A_LENGTH != 0 && addr >= L1_DATA_A_START
			    && addr + sizeof(data) <= L1_DATA_A_START + L1_DATA_A_LENGTH) {
				memcpy((void *)(addr), &data, sizeof(data));
				copied = sizeof(data);

			} else if (L1_DATA_B_LENGTH != 0 && addr >= L1_DATA_B_START
			    && addr + sizeof(data) <= L1_DATA_B_START + L1_DATA_B_LENGTH) {
				memcpy((void *)(addr), &data, sizeof(data));
				copied = sizeof(data);

			} else
#endif
                            if (addr >= FIXED_CODE_START
			    && addr + sizeof(data) <= FIXED_CODE_END) {
#if FIX
                                copy_to_user_page(0, 0, 0, (void *)(addr), &data, sizeof(data));
#else
                                memcpy((void *)(addr), &data, sizeof(data));
#endif
				copied = sizeof(data);

			} else
				copied = access_process_vm(child, addr, &data,
							   sizeof(data), 1);

			pr_debug("ptrace: copied size %d\n", copied);
			if (copied != sizeof(data))
				break;
			ret = 0;
			break;
		}

	case PTRACE_POKEUSR:	/* write the word at location addr in the USER area */
		ret = -EIO;
		if ((addr & 3) || (addr > (sizeof(struct pt_regs) + 16))) {
			printk(KERN_WARNING "ptrace error : POKEUSR: temporarily returning 0\n");
			break;
		}

		if (addr >= (sizeof(struct pt_regs))) {
			ret = 0;
			break;
		}
		if (addr == PT_SYSCFG) {
			data &= SYSCFG_MASK;
			data |= get_reg(child, PT_SYSCFG);
		}
		ret = put_reg(child, addr, data);
		break;

	case PTRACE_SYSCALL:	/* continue and stop at next (return from) syscall */
	case PTRACE_CONT:	/* restart after signal. */
		pr_debug("ptrace: syscall/cont\n");

		ret = -EIO;
		if (!valid_signal(data))
			break;
		if (request == PTRACE_SYSCALL)
			set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		else
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		child->exit_code = data;
		ptrace_disable(child);
		pr_debug("ptrace: before wake_up_process\n");
		wake_up_process(child);
		ret = 0;
		break;

	/*
	 * make the child exit.  Best I can do is send it a sigkill.
	 * perhaps it should be put in the status that it wants to
	 * exit.
	 */
	case PTRACE_KILL:
		ret = 0;
		if (child->exit_state == EXIT_ZOMBIE)	/* already dead */
			break;
		child->exit_code = SIGKILL;
		ptrace_disable(child);
		wake_up_process(child);
		break;

	case PTRACE_SINGLESTEP:	/* set the trap flag. */
		pr_debug("ptrace: single step\n");
		ret = -EIO;
		if (!valid_signal(data))
			break;
		clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		ptrace_enable(child);
		child->exit_code = data;
		wake_up_process(child);
		ret = 0;
		break;

	case PTRACE_GETREGS:
		/* Get all gp regs from the child. */
		ret = ptrace_getregs(child, datap);
		break;

	case PTRACE_SETREGS:
		printk(KERN_WARNING "ptrace: SETREGS: **** NOT IMPLEMENTED ***\n");
		/* Set all gp regs in the child. */
		ret = 0;
		break;

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}

	return ret;
}
