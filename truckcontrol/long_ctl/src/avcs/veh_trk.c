/* \file 
 *
 * 	Copyright (c) 2008   Regents of the University of California
 *
 *	This process creates all the "db" data server variables
 *	needed by interacting processes on the Truck Control 2009
 *	project (FHWA BAA), except for the J1939 database variable,
 *	which are created independently in the J1939 read/write processes so
 *	that they can be run stand-alone for testing.
 * 
 *	When the "db" data server is used with only a small number
 *	of interacting processes, it is convenient for the write
 *	processes to create the variables in the data server.
 *	However, when many processes are interacting, and it is
 *	desirable to test different subsets of them for partial
 *	functionality, it is more convenient for one process to
 *	create all the "db" variables that represent shared data
 *	between the processes.
 *
 *	With the verbose option, this option can also be used to
 *	use the data gathering routines from long_ctl/src/common
 *	to print a trace file to stdout. This is redundant if
 *	the controller is also using these utitilies (as in, e.g.,
 *	long_ctl/src/template) but useful for gathering data
 *	when drivers are running without a controller, or when
 *	the controller itself is not gathering data.
 *
 */

#include <sys_os.h>
#include <timestamp.h>
#include <path_gps_lib.h>
#include <sys_rt.h>
#include <sys_list.h>
#include <db_clt.h>
#include <clt_vars.h>	
#include <db_utils.h>
#include <jbus_vars.h>
#include <path_gps_lib.h>
#include <long_ctl.h>
#include <evt300.h>
#include <mdl.h>
#include <densolidar.h>
#include <long_comm.h>
#include <veh_trk.h>

static int sig_list[] = 
{
	SIGINT,
	SIGQUIT,
	SIGTERM,
	SIGALRM,
	ERROR,
};

static jmp_buf exit_env;

static void sig_hand(int code)
{
	if (code == SIGALRM)
		return;
	else
		longjmp(exit_env, code);
}

/** All variables used by veh_comm, radar and longitudinal control
 * processes are created.
 */
static db_id_t db_vars_list[] = {
	{DB_LONG_OUTPUT_VAR, sizeof( long_output_typ )},
	{DB_LONG_DIG_OUT_VAR, sizeof( long_dig_out_typ )},
	{DB_COMM_TX_VAR, sizeof( veh_comm_packet_t )},
};

#define NUM_DB_VARS	sizeof(db_vars_list)/sizeof(db_id_t)

/** uses long_ctrl type from long_ctl/src/common directory,
 * as the structure for keeping cbuff_typ,
 * but constructs buffer_item differently than in
 * long_ctl/src/template/tasks.h
 * long_vehicle_state includes all inputs to the long_trk process
 * the long_output_typ, long_dig_out_typ and veh_comm_packet_t fields
 * are the outputs from that process 
 */
typedef struct {
	double process_time;
	timestamp_t ts;
	long_vehicle_state state;
	long_output_typ cmd;
	long_dig_out_typ dig_out;
	veh_comm_packet_t comm_tx;
} buffer_item;

static void gather_data(long_ctrl *pctrl, long_output_typ *pout,
		long_dig_out_typ *pdig_out, veh_comm_packet_t *pcomm_tx)
{
        long_vehicle_state *pv = &pctrl->vehicle_state;
        cbuff_typ *pbuff = &pctrl->buff;
        buffer_item *pdata = (buffer_item *) pbuff->data_array;
        struct timeb current_time;
        buffer_item current_item;
	int index = get_circular_index(pbuff);
	struct timeb start_time = pctrl->start_time;

	ftime(&current_time);
	current_item.state = *pv;
	current_item.cmd = *pout;
	current_item.dig_out= *pdig_out;
	current_item.comm_tx= *pcomm_tx;
	current_item.process_time =
		TIMEB_SUBTRACT(&start_time, &current_time);
	get_current_timestamp(&current_item.ts);
	pdata[index] = current_item;
}

/**
 *	 Prints out stored data to stdout.
 *	 (Take care of file names in script.)
 */
static void print_data(FILE *fp, long_ctrl *pctrl)
{
	cbuff_typ *pbuff = &pctrl->buff;
	buffer_item *pdata = (buffer_item *) pbuff->data_array;
	int i, j;
	int current_index;

	if ((pdata == NULL) || (pbuff->data_count == 0))
		return;

	current_index = pbuff->data_start;
	
	for (i = 0; i < pbuff->data_count; i++) {
		buffer_item *p = &pdata[current_index]; 
		long_vehicle_state *pv = &p->state;
		long_output_typ *pcmd = &p->cmd;
		long_dig_out_typ *pdig_out = &p->dig_out;
		veh_comm_packet_t *pcomm_tx = &p->comm_tx;
		print_timestamp(fp, &p->ts);
		fprintf(fp, " %.3f ", p->process_time);
		///EEC1
		fprintf(fp, "%.3f ", pv->engine_speed);
		fprintf(fp, "%.3f ", pv->engine_torque);
		fprintf(fp, "%d ", pv->engine_mode);

		///EEC2
		fprintf(fp, "%.3f ", pv->accelerator_pedal_position);
		fprintf(fp, "%.3f ", pv->percent_load_current_speed);

		///EEC3
		fprintf(fp, "%.3f ", pv->nominal_friction_torque);

		///ERC1
		fprintf(fp, "%.3f ", pv->retarder_torque);
		fprintf(fp, "%d ", pv->retarder_mode);

		///EBC1
		fprintf(fp, "%.3f ", pv->brake_pedal_position);
		fprintf(fp, "%d ", pv->ebs_brake_switch_status);
		fprintf(fp, "%d ", pv->abs_ebs_amber_warning_state);
		fprintf(fp, "%.3f ", pv->brake_demand);

		///EBC2
		fprintf(fp, "%.3f ", pv->front_axle_speed);
		fprintf(fp, "%.3f ", pv->front_left_wheel_relative);
		fprintf(fp, "%.3f ", pv->front_right_wheel_relative);
		fprintf(fp, "%.3f ", pv->rear1_left_wheel_relative);
		fprintf(fp, "%.3f ", pv->rear1_right_wheel_relative);

		///CCVS
		fprintf(fp, "%.3f ", pv->vehicle_speed);

		///ETC1
		fprintf(fp, "%d ", pv->shift_in_progress);
		fprintf(fp, "%.3f ", pv->input_shaft_speed);
		fprintf(fp, "%.3f ", pv->output_shaft_speed);
		fprintf(fp, "%d ", pv->lockup_engaged);
		fprintf(fp, "%d ", pv->driveline_engaged);

		///ETC2
		fprintf(fp, "%d ", pv->current_gear);
		fprintf(fp, "%d ", pv->selected_gear);
		fprintf(fp, "%.3f ", pv->actual_gear_ratio);

		///LFE
		fprintf(fp, "%.3f ", pv->fuel_rate);

		///FD
		fprintf(fp, "%d ", pv->fan_drive_state);
		fprintf(fp, "%.3f ", pv->estimated_percent_fan_speed);

		///ERC1 (TRANS)
		fprintf(fp, "%.3f ", pv->trans_retarder_value);
		fprintf(fp, "%.3f ", pv->trans_retarder_mode);
		fprintf(fp, "%hhd ", pv->trans_retarder_source);
		fprintf(fp, "%.3f ", pv->coolant_load_increase);
		

		/// long_output_typ
                fprintf(fp, "%.3f ", pcmd->engine_speed);
                fprintf(fp, "%.3f ", pcmd->engine_torque);
                fprintf(fp, "%d ", pcmd->engine_command_mode);
                fprintf(fp, "%.3f ", pcmd->engine_retarder_torque);
                fprintf(fp, "%d ", pcmd->engine_retarder_command_mode);
                fprintf(fp, "%.3f ", pcmd->ebs_deceleration);
                fprintf(fp, "%d ", pcmd->brake_command_mode);
                fprintf(fp, "%.3f ", pcmd->trans_retarder_value);
                fprintf(fp, "%d ", pcmd->trans_retarder_command_mode);

		/// GPS and COMM
		fprintf(fp, "%.7lf ", pv->self_gps.latitude);
		fprintf(fp, "%.7lf ", pv->self_gps.longitude);
		fprintf(fp, "%.3lf ", pv->self_gps.speed);
		fprintf(fp, "%.3lf ", pv->lead.global_time);
		fprintf(fp, "%.7lf ", pv->lead.gps.latitude);
		fprintf(fp, "%.7lf ", pv->lead.gps.longitude);
		fprintf(fp, "%.3lf ", pv->lead.gps.speed);
		fprintf(fp, "%.3f ", pv->lead.velocity);
		fprintf(fp, "%.3lf ", pv->preceding.global_time);
		fprintf(fp, "%.7lf ", pv->preceding.gps.latitude);
		fprintf(fp, "%.7lf ", pv->preceding.gps.longitude);
		fprintf(fp, "%.3lf ", pv->preceding.gps.speed);
		fprintf(fp, "%.3f ", pv->preceding.velocity);


                for (j = 0; j < EVT300_MAX_TARGETS; j++)
                    fprintf(fp, " %d %d %d %d %d %d ",
                        pv->evt300.target[j].id,
                        pv->evt300.target[j].range,
                        pv->evt300.target[j].rate,
                        pv->evt300.target[j].azimuth,
                        pv->evt300.target[j].mag,
                        pv->evt300.target[j].lock);

		// Formerly used for MDL lidar
		fprintf(fp, "%.3f ", 0.0);

		// Denso lidar
		fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",
                        pv->lidarA.h_latpos_1,pv->lidarA.l_latpos_1,
                        pv->lidarA.vert_pos_1, pv->lidarA.h_dist_1,
                        pv->lidarA.l_dist_1,pv->lidarA.lanerate_1,
                        pv->lidarA.veh_rate_1,pv->lidarA.targ_stat_1,
                        pv->lidarA.lat_vel_1, pv->lidarA.h_velocity_1,
                        pv->lidarA.l_velocity_1,pv->lidarA.h_width_1,
                        pv->lidarA.l_width_1,pv->lidarA.height_1,
                        pv->lidarA.h_depth_1, pv->lidarA.l_depth_1,
                        pv->lidarA.rel_acc_1);

		// Brake pressure, from DMM32 A/D scan
		fprintf(fp, "%.3f %.3f %.3f ", 
			pv->fb_axle,
			pv->mb_axle,
			pv->rb_axle);

		// Digital inputs and outputs
		fprintf(fp, "%02hhx %02hhx %02hhx %02hhx %02hhx ", 
			pv->dig_in.manualctl,
			pv->dig_in.autoctl,
			pv->dig_in.brakesw,
			p->dig_out.outchar,
			p->dig_out.amber_flash);

		// Platoon communication; add remaining fields later
		fprintf(fp, "%.3lf ", pcomm_tx->global_time);
		fprintf(fp, "%hd ", pcomm_tx->user_ushort_1);
		fprintf(fp, "%hd ", pcomm_tx->user_ushort_2);
		fprintf(fp, "%.3lf ", pcomm_tx->user_float);
		fprintf(fp, "%.3lf ", pv->lead.global_time);
		fprintf(fp, "%hd ", pv->lead.user_ushort_1);
		fprintf(fp, "%hd ", pv->lead.user_ushort_2);
		fprintf(fp, "%.3lf ", pv->lead.user_float);
		fprintf(fp, "%.3lf ", pv->preceding.global_time);
		fprintf(fp, "%hd ", pv->preceding.user_ushort_1);
		fprintf(fp, "%hd ", pv->preceding.user_ushort_2);
		fprintf(fp, "%.3lf", pv->preceding.user_float);

		fprintf(fp, "\n");

		current_index++;
		if (current_index == pbuff->data_size)
			current_index = 0;
	}
	return;
}

int main(int argc, char *argv[])
{
	db_clt_typ *pclt;              /* Database client pointer */
	char hostname[MAXHOSTNAMELEN+1];
	int option;
	char *domain = DEFAULT_SERVICE;
	char dummy[MAX_DATA_SIZE];
	posix_timer_typ *ptimer;
	int delay_ms = 1000;	// wake up once a second
	int i;
	int verbose = 0;
	int veryverbose = 0;
	timestamp_t current_ts;
	int ksize = 1000;	// maximum size stored data in kilobytes
	long_ctrl control_state;	// read and store this data

        while ((option = getopt(argc, argv, "d:s:t:vw")) != EOF) {
                switch(option) {
		case 'd':
			domain = strdup(optarg);
			break;
		case 's':
			ksize = atoi(optarg);
			break;
		case 't':
			delay_ms = atoi(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
		case 'w':
			veryverbose = 1;
			break;
		default:
			fprintf(stderr, "option not recognized\n");
			exit(1);
			break;
                }
	}

	get_local_name(hostname, MAXHOSTNAMELEN);

	/** Call long_database_init to login in to database, initialize 
	 * jbus variables and otherinput variables to long_ctl process 
	 * Initialize control structure first to set vehicle type
	 */

	memset(&control_state, 0, sizeof(control_state));
	ftime(&control_state.start_time);
	init_circular_buffer(&control_state.buff, ksize*100, sizeof(buffer_item));	
	control_state.params.vehicle_type = VEH_TYPE_TRUCK_SILVR;

	if ((pclt = long_database_init(hostname, argv[0], &control_state)) 
			 == NULL) {
		printf("Database initialization error in %s.\n", argv[0]);
		exit(EXIT_FAILURE);
	}


	/* Catch the signals SIGINT, SIGQUIT, and SIGTERM.  If signal occurs,
	 * log out from database and exit. */
	if (setjmp(exit_env) != 0) {
		print_data(stdout, &control_state);
		/* Log out from the database. */
		if (pclt != NULL)
			db_list_done(pclt, db_vars_list, NUM_DB_VARS, NULL, 0);

		exit(EXIT_SUCCESS);
	} else
		sig_ign(sig_list, sig_hand);

        if ((ptimer = timer_init( delay_ms, ChannelCreate(0) )) == NULL)
        {
                fprintf(stderr, "Unable to initialize delay timer\n");
                exit(EXIT_FAILURE);
        }

	// Create and initialize additional variables  to 0
        for (i = 0; i < NUM_DB_VARS; i++) {
                int id = db_vars_list[i].id;
		int size = db_vars_list[i].size;
		clt_create(pclt, id, id, size);
        }
	memset(dummy, 0, MAX_DATA_SIZE);

        for (i = 0; i < NUM_DB_VARS; i++) {
                int id = db_vars_list[i].id;
		int size = db_vars_list[i].size;
		db_clt_write(pclt, id, size, (void *) dummy); 
        }

	// Loop forever doing nothing until terminated with signal

	// In verbose mode print files for plotting
	// Very verbose is in case you doubt the process is alive at all!
	while (TRUE) {
		if (veryverbose) {
                       get_current_timestamp(&current_ts);
                       print_timestamp(stdout,&current_ts);
                       printf("%s \n", argv[0]);
		}
		if (verbose) { 
			long_output_typ long_out;
			long_dig_out_typ dig_out;
			veh_comm_packet_t comm_tx;
			long_read_vehicle_state(pclt, &control_state);
			db_clt_read(pclt, DB_LONG_OUTPUT_VAR,
				sizeof(long_output_typ), &long_out);
			db_clt_read(pclt, DB_LONG_DIG_OUT_VAR,
				sizeof(long_dig_out_typ), &dig_out);
			db_clt_read(pclt, DB_COMM_TX_VAR,
				sizeof(veh_comm_packet_t), &comm_tx);
			gather_data(&control_state, &long_out, &dig_out, 
				&comm_tx);
		}
		TIMER_WAIT (ptimer);
	}
}

