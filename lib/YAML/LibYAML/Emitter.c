#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <yaml.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define BUFFER_SIZE 65536

bool get_line(FILE *input, char *line);
char *get_anchor(char sigil, char *line, char *anchor);
char *get_tag(char *line, char *tag);
void get_value(char *line, char *value, int *style);

SV* test() {
    int ok;
    yaml_event_t event;
    yaml_emitter_t emitter;
    int implicit;
    char anchor[256];
    char tag[256];
    size_t written = 0;

    unsigned char buffer[BUFFER_SIZE+1];
    unsigned char* buffer_ptr = buffer;
    int canonical = 0;
    int unicode = 0;

    if (!yaml_emitter_initialize(&emitter)) {
      fprintf(stderr, "Could not initalize the emitter object\n");
      exit(1);
    }
    yaml_emitter_set_output_string(&emitter, buffer, BUFFER_SIZE, &written);
    yaml_emitter_set_canonical(&emitter, canonical);
    yaml_emitter_set_unicode(&emitter, unicode);
    ok = yaml_stream_start_event_initialize(
      &event,
      YAML_UTF8_ENCODING
    );
    if (!ok) exit(1);
    if (!yaml_emitter_emit(&emitter, &event)) exit(1);

    implicit = 0;
    ok = yaml_document_start_event_initialize(
      &event,
      NULL,
      NULL,
      NULL,
      implicit
    );
    if (!ok) exit(1);
    if (!yaml_emitter_emit(&emitter, &event)) exit(1);


    ok = yaml_mapping_start_event_initialize(
      &event,
      NULL,
      NULL,
      0,
      YAML_BLOCK_MAPPING_STYLE
    );
    if (!ok) exit(1);
    if (!yaml_emitter_emit(&emitter, &event)) exit(1);
    ok = yaml_mapping_end_event_initialize(&event);
    if (!ok) exit(1);
    if (!yaml_emitter_emit(&emitter, &event)) exit(1);


    ok = yaml_document_end_event_initialize(
      &event,
      implicit
    );
    if (!ok) exit(1);
    if (!yaml_emitter_emit(&emitter, &event)) exit(1);
    ok = yaml_stream_end_event_initialize(&event);
    if (!ok) exit(1);
    if (!yaml_emitter_emit(&emitter, &event)) exit(1);

    yaml_emitter_delete(&emitter);
    return newSVpvf("%s", buffer);
}
