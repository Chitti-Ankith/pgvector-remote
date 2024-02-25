#ifndef PINECONE_API_H
#define PINECONE_API_H

#include <curl/curl.h>
#include "cJSON.h"

typedef CURL** CURLHandleList;


typedef struct {
    // todo: we could use this to pass info from the caller to the writefunction callback
    // e.g. we might want the writefunction callback to log the caller's function name
    char *data;
    size_t length;
} ResponseData;

struct curl_slist *create_common_headers(const char *api_key);
void set_curl_options(CURL *hnd, const char *api_key, const char *url, const char *method, ResponseData *response_data);
cJSON* describe_index(const char *api_key, const char *index_name);
cJSON* list_indexes(const char *api_key);
cJSON* pinecone_create_index(const char *api_key, const char *index_name, const int dimension, const char *metric, cJSON *spec);
cJSON* pinecone_api_query_index(const char *api_key, const char *index_host, const int topK, cJSON *query_vector_values, cJSON *filter);
// void pinecone_upsert_one(const char *api_key, const char *index_host, cJSON *vector);
// void pinecone_upsert(const char *api_key, const char *index_host, cJSON *vectors);

// bulk insertion
CURL* get_pinecone_upsert_handle(const char *api_key, const char *index_host, cJSON *vectors, ResponseData *response_data);
cJSON* batch_vectors(cJSON *vectors, int batch_size);
void pinecone_bulk_upsert(const char *api_key, const char *index_host, cJSON *vectors, int batch_size);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
cJSON* pinecone_list_vectors(const char *api_key, const char *index_host, int limit, char* pagination_token);
cJSON* generic_pinecone_request(const char *api_key, const char *url, const char *method, cJSON *body);
cJSON* pinecone_delete_vectors(const char *api_key, const char *index_host, cJSON *ids);
cJSON* pinecone_delete_index(const char *api_key, const char *index_name);

#endif // PINECONE_API_H