/**\file
 *
 *  can_man.c 
 *
 * Resource manager for the SSV CAN board.
 *
 * To use both 82527 controllers of the SSV board, two instances of this
 * process must be executed.
 *
 * Digital I/O on the board is also supported by the same devctls used
 * by PATH DAS (Data Acquisition System) drivers.
 *   
 */

#include <sys_os.h>
#include <sys/dispatch.h>
#include "sys_rt.h"
#include "can_defs.h"
#include "can_man.h"

#undef DO_TRACE

static resmgr_connect_funcs_t  connect_func;
static resmgr_io_funcs_t	   io_func;
static IOFUNC_ATTR_T		   attr;
static iofunc_mount_t can_mount;
static iofunc_funcs_t can_mount_funcs;

static int sig_list[]=
{
        SIGINT,
        SIGQUIT,
        SIGTERM,
        SIGALRM,        // for timer
        ERROR
};
static jmp_buf exit_env;
static void sig_hand(int code)
{
        if (code == SIGALRM)
                return;
        else
                longjmp(exit_env, code);
}

/** External variables in ca_if.c, to be printed on exit
 */
int can_timeout_count = 0;
int tx_buffer_flush = 0;

IOFUNC_OCB_T *can_ocb_calloc(resmgr_context_t *ctp, IOFUNC_ATTR_T *attr)
{
	return ((IOFUNC_OCB_T *) calloc(1, sizeof(IOFUNC_OCB_T)));
}

void can_ocb_free(IOFUNC_OCB_T *pocb)
{
	free(pocb);
}

int main (int argc, char **argv)
{
	dispatch_t *dpp;
	resmgr_attr_t resmgr_attr;
	dispatch_context_t *ctp;
	can_info_t *pinfo = &attr.can_info;

	ThreadCtl(_NTO_TCTL_IO, NULL); //required to access I/O ports

	/// create the dispatch structure
	if ((dpp = dispatch_create ()) == NULL) {
		perror ("Unable to dispatch_create\n");
		exit (EXIT_FAILURE);
	}

	/// initialize the various data structures
	memset (&resmgr_attr, 0, sizeof (resmgr_attr));
	resmgr_attr.nparts_max = 2;
	resmgr_attr.msg_max_size = DAS_MSG_BUF;

	/// bind default functions into the outcall tables
	iofunc_func_init (_RESMGR_CONNECT_NFUNCS, &connect_func,
			 _RESMGR_IO_NFUNCS, &io_func);
	iofunc_attr_init (&attr.io_attr, S_IFNAM | 0666, 0, 0);

	/// add allocation and deallocation for extended OCB
	can_mount_funcs.nfuncs = _IOFUNC_NFUNCS;
	can_mount_funcs.ocb_calloc = can_ocb_calloc;
	can_mount_funcs.ocb_free = can_ocb_free;
	memset(&can_mount, 0, sizeof(can_mount));
	can_mount.funcs = &can_mount_funcs;
	attr.io_attr.mount = &can_mount;
	
	/// read configuration files and bind device-specific functions
	can_init(argc, argv, &connect_func, &io_func, &attr); 

	/// establish a name in the pathname space
	if (resmgr_attach (dpp, &resmgr_attr, attr.devname, _FTYPE_ANY,
		 0, &connect_func, &io_func, &attr) == -1) {
		perror ("Unable to resmgr_attach\n");
		exit (EXIT_FAILURE);
	}

#ifdef DO_TRACE
	printf("Calling can_dev_init: base address 0x%x speed %d extended %d\n",
		pinfo->port, pinfo->bit_speed, pinfo->use_extended_frame);
	fflush(stdout);
#endif

	/// initialize device 
	can_dev_init(pinfo->port, pinfo->bit_speed, pinfo->use_extended_frame);


#ifdef DO_TRACE
	printf("Attaching pulses\n");
	fflush(stdout);
#endif
	/// attach pulses and interrupt event
	pulse_init(dpp, &attr);

	/// alloc dispatch context
	ctp = dispatch_context_alloc (dpp);

	if(setjmp(exit_env) != 0) {
		printf("%s exiting\n", argv[0]);
		printf("can_notify_client_err %d\n", can_notify_client_err);
		printf("mask_count_non_zero %d\n", mask_count_non_zero);
		printf("shadow_buffer_count %d\n", shadow_buffer_count);
		printf("intr_in_handler_count %d\n", intr_in_handler_count);
		printf("rx_interrupt_count %d\n", rx_interrupt_count);
		printf("rx_message_lost_count %d\n", rx_message_lost_count);
		printf("tx_interrupt_count %d\n", tx_interrupt_count);
		printf("tx_buffer_flush %d\n", tx_buffer_flush);
		printf("can_timeout_count %d\n", can_timeout_count);
		fflush(stdout);
		exit(EXIT_SUCCESS);
	} else
		sig_ign(sig_list, sig_hand);

	/// wait here forever, handling messages
	while (1) {
		if ((ctp = dispatch_block (ctp)) == NULL) {
			perror ("Unable to dispatch_block\n");
			exit (EXIT_FAILURE);
		}
		dispatch_handler (ctp);
	}
}
