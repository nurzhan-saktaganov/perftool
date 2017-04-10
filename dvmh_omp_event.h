#ifndef DVMH_OMP_EVENT_H
#define DVMH_OMP_EVENT_H

#include <omp.h>
#include "list.h"
#include "context_types.h"

typedef enum {
	DVMH_OMP_EVENT_INIT,
	DVMH_OMP_EVENT_BEFORE_PARALLEL,
	DVMH_OMP_EVENT_PARALLEL_EVENT,
	DVMH_OMP_EVENT_BEFORE_INTERVAL,
	DVMH_OMP_EVENT_BEFORE_OMP_LOOP,
	DVMH_OMP_EVENT_OMP_ITER, // событие нужно закрыть руками
	DVMH_OMP_EVENT_BEFORE_SECTIONS,
	DVMH_OMP_EVENT_SECTION_EVENT,
	DVMH_OMP_EVENT_BEFORE_SINGLE,
	DVMH_OMP_EVENT_SINGLE_EVENT,
	DVMH_OMP_EVENT_BEFORE_WORKSHARE,
	DVMH_OMP_EVENT_MASTER_BEGIN,
	DVMH_OMP_EVENT_BEFORE_CRITICAL,
	DVMH_OMP_EVENT_CRITICAL_EVENT,
	DVMH_OMP_EVENT_BEFORE_BARRIER,
	DVMH_OMP_EVENT_FLUSH_EVENT,
	DVMH_OMP_EVENT_BEFORE_ORDERED,
	DVMH_OMP_EVENT_BEG_SL,
	DVMH_OMP_EVENT_S_ITER, // событие нужно закрыть руками
	DVMH_OMP_EVENT_BEFORE_FUNC_CAL,
	DVMH_OMP_EVENT_FUNC_BEGIN,
	DVMH_OMP_EVENT_S_IF_ITER, // событие нужно закрыть руками
	DVMH_OMP_EVENT_OMP_IF_ITER, // событие нужно закрыть руками
	DVMH_OMP_EVENT_BEFORE_OI,
} dvmh_omp_event_type;

typedef struct _dvmh_omp_event {
	dvmh_omp_event_type type;
	omp_lock_t *mutex;
	double begin_time;
	double end_time;
	long thread_id;
	list *subevents;
	context_descriptor *descriptor;
} dvmh_omp_event;

typedef struct _dvmh_omp_subevent_iterator {
	list_iterator *li;
} dvmh_omp_subevent_iterator;

dvmh_omp_event *dvmh_omp_event_create(dvmh_omp_event_type event_type);
void dvmh_omp_event_destroy(dvmh_omp_event *event_p);
void dvmh_omp_event_add_subevent(dvmh_omp_event *event_p, dvmh_omp_event *subevent_p);
void dvmh_omp_event_set_begin_time(dvmh_omp_event *event_p, double begin_time);
double dvmh_omp_event_get_begin_time(dvmh_omp_event *event_p);
void dvmh_omp_event_set_end_time(dvmh_omp_event *event_p, double end_time);
double dvmh_omp_event_get_end_time(dvmh_omp_event *event_p);
double dvmh_omp_event_duration(dvmh_omp_event *e);
void dvmh_omp_event_set_thread_id(dvmh_omp_event *event_p, long thread_id);
long dvmh_omp_event_get_thread_id(dvmh_omp_event *event_p);
dvmh_omp_event_type dvmh_omp_event_get_type(dvmh_omp_event *e);
int dvmh_omp_event_has_subevent(dvmh_omp_event *e);
void dvmh_omp_event_set_context_descriptor(dvmh_omp_event *e, context_descriptor *d);
context_descriptor * dvmh_omp_event_get_context_descriptor(dvmh_omp_event *e);

dvmh_omp_subevent_iterator * dvmh_omp_subevent_iterator_new(dvmh_omp_event *e);
int dvmh_omp_subevent_iterator_has_next(dvmh_omp_subevent_iterator *it);
dvmh_omp_event *dvmh_omp_subevent_iterator_next(dvmh_omp_subevent_iterator *it);
void dvmh_omp_subevent_iterator_destroy(dvmh_omp_subevent_iterator *it);

#endif
