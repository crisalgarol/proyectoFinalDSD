// Copyright (c) 2015 Cesanta Software Limited // All rights reserved
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
struct mg_str cb(struct mg_connection *c, struct mg_str file_name)
MG_ENABLE_HTTP_STREAMING_MULTIPART = true;
{
  // Return the same filename. Do not actually do this except in test!
  // fname is user-controlled and needs to be sanitized.
  return file_name;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data)
{
  switch (ev){
    case MG_EV_HTTP_REQUEST:
      mg_serve_http(nc, (struct http_message *)ev_data, s_http_server_opts);
      break;
    case MG_EV_HTTP_PART_BEGIN:
    case MG_EV_HTTP_PART_DATA:
    case MG_EV_HTTP_PART_END:
      printf("subiendo archivo...");
      mg_file_upload_handler(nc, ev, ev_data, cb);
      break;
    default:
      break;
  }
}
int main(void)
{
  struct mg_mgr mgr;
  struct mg_connection *nc;
  mg_mgr_init(&mgr, NULL);
  printf("Starting web server on port %s\n", s_http_port);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL)
  {
    printf("Failed to create listener\n");
    return 1;
  }
  // Set up HTTP server parameters 
  mg_set_protocol_http_websocket(nc); 
  s_http_server_opts.document_root = "."; // Serve current directory 
  s_http_server_opts.enable_directory_listing = "yes";
  for (;;)
  {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);
  return 0;
}