/**\file
 *	veh_rcv.c 
 *		Receives a message from another vehicle and
 *		writes it to the appropriate database variable,
 *		depending on vehicle ID in the message. 
 *
 *		On initialization reads a config file that specifies
 *		the current vehicle ID, the lead vehicle ID,
 *		and the preceding vehicle ID.
 *
 * Copyright (c) 2008   Regents of the University of California
 *
 */
#include <sys_os.h>
#include <db_clt.h>
#include <db_utils.h>
#include <timestamp.h>
#include "path_gps_lib.h"
#include "long_comm.h"
#include <local.h>
#include <sys_rt.h>
#include <sys_ini.h>
#include <udp_utils.h>

static int sig_list[]=
{
	SIGINT,
	SIGQUIT,
	SIGTERM,
	SIGALRM,	// for timer
	(-1)
};

static jmp_buf exit_env;

static void sig_hand(int code)
{
        if (code == SIGALRM)
                return;
        else
                longjmp(exit_env, code);
}

// Sets up a UDP socket for reception on a port from any address
static int udp_init(short port)
{
        int sockfd;                      // listen on sock_fd
        struct sockaddr_in addr;       // IP info for socket calsl

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
                perror("socket");
                return -1;
        }
        set_inet_addr(&addr, INADDR_ANY, port);

        if (bind(sockfd, (struct sockaddr *)&addr,
                                         sizeof(struct sockaddr)) == -1) {
                perror("bind");
                return -2;
        }
        return sockfd;
}

/**  By default (if no ini file entry) sets up as head car
 */
static int get_ids(FILE *fpin, int *pself, int *plead, int *psecond, int *pthird) 
{
	*plead = get_ini_long(fpin, "LeadVehicleID", 1);   
	*pself = get_ini_long(fpin, "PositionInPlatoon", 1);   
	*psecond = get_ini_long(fpin, "SecondVehicleID", 0);   
	*pthird = get_ini_long(fpin, "ThirdVehicleID", 0);   
	printf("lead %d self %d second %d third %d\n", *plead, *pself, *psecond, *pthird);
	fflush(stdout);
        return 1;
}

int main( int argc, char *argv[] )
{
	int ch;		
        db_clt_typ *pclt;  		/// data bucket pointer	
        char *domain=DEFAULT_SERVICE;
        char hostname[MAXHOSTNAMELEN+1];
        int xport = COMM_OS_XPORT;
	int self_vehicle_id;
	int lead_vehicle_id;
	int second_vehicle_id;
	int third_vehicle_id;
        struct sockaddr_in src_addr;
	int sd;				/// socket descriptor
	int udp_port;
	veh_comm_packet_t comm_pkt;
        int bytes_received;     // received from a call to recv
	FILE *fpin;			/// file pointer for ini file
	char *vehicle_str="Blue";		/// e.g., Blue, Gold, Silver
	int verbose = 0;
	short msg_count = 0;
	char *ini_fname = "realtime.ini";
	int socklen = sizeof(src_addr);

        short rcvd_sn = 0;////////////////////////////////
printf("VEH_RCV.C: sizeof veh_comm_packet_t %d\n", sizeof(veh_comm_packet_t));
        while ((ch = getopt(argc, argv, "t:u:vf:")) != EOF) {
                switch (ch) {
		case 't': vehicle_str = strdup(optarg);
			  break;
		case 'f': ini_fname = strdup(optarg);
			  break;
		case 'u': udp_port = atoi(optarg); 
			  break;
		case 'v': verbose = 1; 
			  break;
                default:  printf( "Usage: %s [-v (verbose)]", argv[0]);
			  exit(EXIT_FAILURE);
                          break;
                }
        }
        if ((fpin = get_ini_section(ini_fname, vehicle_str)) == NULL) {
                printf("%s: can't get ini file %s, section %s\n",
			   argv[0], ini_fname, vehicle_str);
                fflush(stdout);
                exit(EXIT_FAILURE);
        }

	/**  Read in .ini file and set vehicle IDs
	 */

	printf("vehicle_str %s:", vehicle_str);
	get_ids(fpin, &self_vehicle_id, &lead_vehicle_id, 
			&second_vehicle_id, &third_vehicle_id); 

        get_local_name(hostname, MAXHOSTNAMELEN);

	/**  assumes DB_COMM variables were aleady created by another process
	 */
	pclt = db_list_init(argv[0], hostname, domain, xport, NULL, 0, NULL, 0); 
	if( setjmp( exit_env ) != 0 ) {
		printf("Received %d messages\n", msg_count);
		db_list_done(pclt, NULL, 0, NULL, 0);		
		exit( EXIT_SUCCESS );
	} else
		sig_ign( sig_list, sig_hand );

	sd = udp_init(udp_port);

	while (1) {
		/// recvfrom
                if ((bytes_received = recvfrom(sd, &comm_pkt,
			 sizeof(long_comm_pkt), 0,
                        (struct sockaddr *) &src_addr,
                                (socklen_t *) &socklen))
                                 <= 0) {
                        perror("recvfrom failed\n");
                        break;
                }
		get_current_timestamp(&comm_pkt.ts);
 
////////////////////Make sure the comm_pkt is received from other trucks/////

                if (comm_pkt.object_id[0] != *vehicle_str) { 
                   msg_count++;

                 if (msg_count == 1)
                      rcvd_sn = comm_pkt.sequence_no; //initial value

                 if ((comm_pkt.sequence_no - rcvd_sn) == 1 )
                      rcvd_sn++;

                   else {
                     //  printf( "%hd packets lost.", (comm_pkt.sequence_no - rcvd_sn - 1) );
                       rcvd_sn = comm_pkt.sequence_no;
                    }

                 //  printf( "\nrcvd_sn: %hd.\n",rcvd_sn ); 
                 } 
////////////////////////////////////////////////////////////////////////////


		/** Check "my_pip" field in packet and write to 
		 *  DB_COMM_LEAD_TRK, DB_COMM_TRK_SECOND, and DB_COMM_TRK_THIRD if relevant 
		 * For second and third vehicles, both may be written from same packet
		 */
		if (comm_pkt.my_pip == lead_vehicle_id)  
			db_clt_write(pclt, DB_COMM_LEAD_TRK_VAR,
				sizeof(comm_pkt), &comm_pkt);
		if (comm_pkt.my_pip == second_vehicle_id)  
			db_clt_write(pclt, DB_COMM_SECOND_TRK_VAR,
				sizeof(comm_pkt), &comm_pkt);
		if (comm_pkt.my_pip == third_vehicle_id)  
			db_clt_write(pclt, DB_COMM_THIRD_TRK_VAR,
				sizeof(comm_pkt), &comm_pkt);
		if (verbose) {
			printf("Vehicle %d received packet from vehicle %d\n",
				self_vehicle_id, comm_pkt.my_pip);
                        printf("%s: %f\n", comm_pkt.object_id,
                               comm_pkt.global_time);
                        fflush(stdout);
                }

	}
		
	longjmp(exit_env,1);	/* go to exit code when loop terminates */
}
