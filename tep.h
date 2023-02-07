#ifndef __TEP_H
#define __TEP_H

#include <event-parse.h>
#include <expr.h>

struct tep_handle *tep__ref(void);
void tep__unref(void);
int tep__event_id(const char *sys, const char *name);
void tep__update_comm(const char *comm, int pid);
const char *tep__pid_to_comm(int pid);
void tep__print_event(unsigned long long ts, int cpu, void *data, int size);
bool tep__event_has_field(int id, const char *field);
bool tep__event_field_size(int id, const char *field);

typedef struct global_var_declare event_fields;
event_fields *tep__event_fields(int id);

void monitor_tep__comm(union perf_event *event, int instance);

struct tp {
    struct perf_evsel *evsel;
    int id;
    char *sys;
    char *name;
    char *filter;
    int stack;
    int max_stack;
    char *alias;
    unsigned long *counters; // Counter per instance

    // top profiler
    struct {
        char *field;
        bool event;
        bool top_by;
    } *top_add;
    int nr_top;
    const char *comm;

    // kmemleak profiler
    const char *mem_ptr;
    const char *mem_size;

    // num-dist profiler
    const char *num;

    //multi-trace profiler
    const char *key;
    bool untraced;
    bool trigger;
};

struct tp_list {
    int nr_tp;
    int nr_need_stack;
    bool need_stream_id;
    int nr_top;
    int nr_comm;
    int nr_mem_size;
    int nr_num;
    int nr_untraced;
    struct tp tp[0];
};

struct tp_list *tp_list_new(char *event_str);
void tp_list_free(struct tp_list *tp_list);




#endif

