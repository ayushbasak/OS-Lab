#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #defualts
char * info, * temp;
char *  get_info_from_file(char * filepath, char * search){
	FILE * fp = fopen(filepath, "r");
	char * line;
	size_t len = 0;
	char * temp;
	while(getline(&line, &len, fp) != -1){
		temp = strstr(line, search);
		if(temp){
			fclose(fp);
			return temp;
		}
	}
}

// Struct to store data for Part 2
struct user_statistics{
	float user_time, system_time, idle_time;
};
struct memory_statistics{
	float free_memory;
};
struct context_statistics{
	float context_switches;
};
typedef struct user_statistics USER;
typedef struct memory_statistics MEMORY;
typedef struct context_statistics CONTEXT; 
struct usage_statistics{
	USER user;
	MEMORY memory;
	CONTEXT context;
};
typedef struct usage_statistics USAGE;

// Helper Functions (Printer)

void display(USAGE u){
	printf("\nUser: %.2lf %c\tSystem: %.2lf %c\tIdle: %.2lf %c\n",u.user.user_time,'%',u.user.system_time,'%',u.user.idle_time,'%');
	printf("Free Memory\t: %.2f %c\n",u.memory.free_memory,'%');
	printf("Context Switches\t: %.0f\n",u.context.context_switches);
}

// These 4 functions are a of PART 1
void get_cpuinfo(){
	info = get_info_from_file("/proc/cpuinfo", "model name");
	temp = strstr(info, ":");
	printf("Processor Type\t: %s",temp+2);

}
void get_kernel_version_info(){
	info = get_info_from_file("/proc/version", "version");
	temp = strstr(info, " ");
	printf("Kernel Version\t: %s", temp);
}
void get_total_memory(){
	info = get_info_from_file("/proc/meminfo", "MemTotal");
	temp = strstr(info, ":");
	printf("Total Memory\t: %s", temp+2);
}
void get_uptime(){
	info = get_info_from_file("/proc/uptime", "");
	double time;
	sscanf(info, "%lf",&time);
	printf("CPU Uptime\t: %lf", time);
}

// PART 2 (Continous Kernel Info)
USER get_usage_times(){
	USER temp_user;
	info = get_info_from_file("/proc/stat", "cpu");
	temp = strstr(info, " ");
	int user, nice, system, idle, iowait, irq, softirq;
	sscanf(temp, "%d %d %d %d %d %d %d", &user, &nice, &system, &idle, &iowait, &irq, &softirq);
	int total = user + nice + system + idle + iowait;
	double user_mode, system_mode, idle_mode;
	user_mode = (user*100.0)/total;
	system_mode = (system*100.0)/total;
	idle_mode = (idle*100.0)/total;
	char c = '%';
	temp_user.user_time = user_mode;
	temp_user.system_time = system_mode;
	temp_user.idle_time = idle_mode;
	return temp_user;
}
MEMORY get_available_memory(){
	MEMORY memory;
	int total_mem, free_mem;
	temp = get_info_from_file("/proc/meminfo", "MemTotal") + 9;
	sscanf(temp, "%d", &total_mem);
	temp = get_info_from_file("/proc/meminfo", "MemFree") + 9;
	sscanf(temp, "%d", &free_mem);
	float free_perc = (free_mem*100.0)/total_mem;
	memory.free_memory = free_perc;
	return memory;
}
CONTEXT get_context_switches(){
	CONTEXT context;
	int ctxt;
	info = get_info_from_file("/proc/stat", "ctxt");
	sscanf(info, "%f", &ctxt);
	context.context_switches = ctxt;
	return context;
}

int main(int argc, char ** argv){
	if(argc == 1){
		printf("\n\t\t======================\n");
		get_cpuinfo();
		get_kernel_version_info();
		get_total_memory();
		get_uptime();
		printf("\n\t\t======================\n");
	}
	else if(argc == 3){
		int read_rate, printout_rate;
		sscanf(argv[1],"%d",&read_rate);
		sscanf(argv[2],"%d",&printout_rate);
		clock_t  begin = clock(), diff;
		int time_passed;
		USAGE u, final_u;
		final_u.user.user_time = final_u.user.system_time = final_u.user.idle_time = 0;
		final_u.memory.free_memory = 0;
		final_u.context.context_switches = 0;
		int iterations = 0;
		while(1){
			diff = clock() - begin;
			time_passed = diff/CLOCKS_PER_SEC;
			if(time_passed > read_rate){
				begin = clock();
				USER user = get_usage_times(u);
				MEMORY memory = get_available_memory(u);
				CONTEXT context = get_context_switches(u);
				u.user = user;
				u.memory = memory;
				u.context = context;
				display(u);
				final_u.user.user_time += u.user.user_time;
				final_u.user.system_time += u.user.system_time;
				final_u.user.idle_time += u.user.idle_time;
				++iterations;
				final_u.memory.free_memory += u.memory.free_memory;
				final_u.context.context_switches += u.context.context_switches;
			}
			if(iterations > printout_rate/read_rate){
				final_u.user.user_time /= iterations;
				final_u.user.system_time /= iterations;
				final_u.user.idle_time /= iterations;
				final_u.memory.free_memory /= iterations;
				final_u.context.context_switches /= iterations;
				printf("\n\n=========FINAL RESULTS========\n\n");
				display(final_u);
				break;
			}
		}

	}
	return 0;
}
