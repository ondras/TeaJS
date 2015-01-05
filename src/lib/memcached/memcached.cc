#include <v8.h>
#include "macros.h"
#include "gc.h"

#include <libmemcached/memcached.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#define MEMCACHED_PTR memcached_st * memc = LOAD_PTR(0, memcached_st *)
#define JS_MEMCACHED_CAS_ERROR JS_TYPE_ERROR("Invalid arguments. Use cas(key{String}, value{String}, expiration{Int}, flags{Int}, cas{[Int,Int]})")

namespace {

void finalize(v8::Handle<v8::Object> obj) {
  memcached_st * memc = LOAD_PTR_FROM(obj, 0, memcached_st *);
  if (memc) {
    memcached_free(memc);
  }
}

/**
 * Memcached constructor does basically nothing. It just adds "this.close()"
 * method to global GC
 */
JS_METHOD(_memcached) {
  ASSERT_CONSTRUCTOR;
  if (args.Length() != 0) {
    JS_TYPE_ERROR("Invalid arguments. Use 'new Memcached()'");
    return;
  }
  memcached_st *memc = memcached_create(NULL);
  SAVE_PTR(0, memc);
  GC * gc = GC_PTR;
  gc->add(args.This(), finalize);
  args.GetReturnValue().Set(args.This());
}

/**
 * Re-initializes the underlying memcached connection and clears all state
 * previously matained. Note that this does not effect the actual memcached
 * servers but does clear the list of servers used by this connection.
 */
JS_METHOD(_reset) {
  MEMCACHED_PTR;

  if (args.Length() != 0) {
    JS_TYPE_ERROR("Invalid arguments. Use 'reset()'");
    return;
  }

  memcached_free(memc);
  SAVE_PTR(0, memcached_create(NULL));

  args.GetReturnValue().Set(args.This());
}

/**
 * Sets the prefix key. The prefix key will be used to create a domain for your
 * keys. The value specified here will be prefixed to each of your keys. The
 * value can not be greater then MEMCACHED_PREFIX_KEY_MAX_SIZE - 1 and will
 * reduce MEMCACHED_MAX_KEY by the value of your key. The prefix key is only
 * applied to the primary key, not the master key.
 */
JS_METHOD(_setPrefixKey) {
  MEMCACHED_PTR;

  if (args.Length() != 1 ||
      !args[0]->IsString()) {
    JS_TYPE_ERROR("Invalid arguments. Use 'setPrefixKey(key{String})'");
    return;
  }

  v8::String::Utf8Value key(args[0]);

  memcached_return rc =
      memcached_callback_set(memc, MEMCACHED_CALLBACK_PREFIX_KEY, *key);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Returns the current prefix key used.
 */
JS_METHOD(_getPrefixKey) {
  MEMCACHED_PTR;

  if (args.Length() > 0) {
    JS_TYPE_ERROR("Invalid arguments. Use 'getPrefixKey()'");
    return;
  }

  memcached_return rc;
  char *value = (char *)memcached_callback_get(memc, MEMCACHED_CALLBACK_PREFIX_KEY, &rc);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  v8::HandleScope handle_scope(JS_ISOLATE);

  v8::Handle<v8::String> result = JS_STR_LEN(value, strlen(value));

  args.GetReturnValue().Set(result);
}

/**
 * Clears the prefix key so that no prefix key will be used.
 */
JS_METHOD(_clearPrefixKey) {
  MEMCACHED_PTR;

  if (args.Length() > 0) {
    JS_TYPE_ERROR("Invalid arguments. Use 'clearPrefixKey()'");
    return;
  }

  memcached_return rc =
      memcached_callback_set(memc, MEMCACHED_CALLBACK_PREFIX_KEY, NULL);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}


/**
 * Adds a server by host, port and weight to the list of servers that will
 * handle requests.
 */
JS_METHOD(_addServerWithWeight) {
  MEMCACHED_PTR;

  if (args.Length() != 3 ||
      !args[0]->IsString() ||
      !args[1]->IsInt32() ||
      !args[2]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use addServerWithWeight(host{String}, port{Integer}, weight{Integer}).'");
    return;
  }

  v8::String::Utf8Value host(args[0]);
  int port = args[1]->Int32Value();
  uint32_t weight = args[2]->Uint32Value();

  memcached_return rc =
      memcached_server_add_with_weight(memc, *host, port, weight);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Wipes the contents of memcached servers. It will either do this immediately
 * or expire the content based on the expiration time passed to the method. An
 * expiration time of 0 causes an immediate flush. The operation is not atomic
 * to multiple servers, just atomic to a single server. That is, it will flush
 * the servers in the order that they were added.
 */
JS_METHOD(_flush) {
  MEMCACHED_PTR;

  if (args.Length() != 1 || !args[0]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use flush(expiration{Integer}).");
    return;
  }

  uint32_t expiration = args[0]->Uint32Value();

  memcached_return rc = memcached_flush(memc, expiration);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Writes an object to the server. If an object already exists it will
 * overwrite what is in the server. If the object does not exist it will be
 * written.
 */
JS_METHOD(_set) {
  MEMCACHED_PTR;

  if (args.Length() != 4 ||
      !args[0]->IsString() ||
      !args[1]->IsString() ||
      !args[2]->IsInt32() ||
      !args[3]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use set(key{String}, value{String}, expiration{Integer}, flags{Integer})");
    return;
  }

  v8::String::Utf8Value key(args[0]);
  v8::String::Utf8Value value(args[1]);
  uint32_t expiration = args[2]->Uint32Value();
  uint32_t flags = args[3]->Uint32Value();

  memcached_return rc = memcached_set(
      memc,
      *key, key.length(),
      *value, value.length(),
      expiration,
      flags);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Replaces an object on the server. If the object is not found on the server an
 * error occurs.
 */
JS_METHOD(_replace) {
  MEMCACHED_PTR;

  if (args.Length() != 4 ||
      !args[0]->IsString() ||
      !args[1]->IsString() ||
      !args[2]->IsInt32() ||
      !args[3]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use replace(key{String}, value{String}, expiration{Integer}, flags{Integer})");
    return;
  }

  v8::String::Utf8Value key(args[0]);
  v8::String::Utf8Value value(args[1]);
  uint32_t expiration = args[2]->Uint32Value();
  uint32_t flags = args[3]->Uint32Value();

  memcached_return rc = memcached_replace(
      memc,
      *key, key.length(),
      *value, value.length(),
      expiration,
      flags);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Adds an object on the server. If the object is found on the server an error
 * occurs, otherwise the value is stored.
 */
JS_METHOD(_add) {
  MEMCACHED_PTR;

  if (args.Length() != 4 ||
      !args[0]->IsString() ||
      !args[1]->IsString() ||
      !args[2]->IsInt32() ||
      !args[3]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use add(key{String}, value{String}, expiration{Integer}, flags{Integer})");
    return;
  }

  v8::String::Utf8Value key(args[0]);
  v8::String::Utf8Value value(args[1]);
  uint32_t expiration = args[2]->Uint32Value();
  uint32_t flags = args[3]->Uint32Value();

  memcached_return rc = memcached_add(
      memc,
      *key, key.length(),
      *value, value.length(),
      expiration,
      flags);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Deletes a particular key. Expiration works by placing the item into a delete
 * queue, which means that it won't possible to retrieve it by the "get"
 * command, but "add" and "replace" command with this key will also fail (the
 * "set" command will succeed, however). After the time passes, the item is
 * finally deleted from server memory.
 *
 * Please note the the Danga memcached server removed support for expiration in
 * the 1.4 version.
 */
JS_METHOD(_remove) {
  MEMCACHED_PTR;

  if (args.Length() != 2 ||
      !args[0]->IsString() ||
      !args[1]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use delete(key{String}, expiration{Integer})");
    return;
  }

  v8::String::Utf8Value key(args[0]);
  uint32_t expiration = args[1]->Uint32Value();

  memcached_return rc = memcached_delete(memc, *key, key.length(), expiration);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Fetches an individual value from the server by key. Returns undefined if no
 * value was set for the key. Note that there is currently no way of getting the
 * CAS value of the result with get in libmemcached so we do not return it here.
 *
 * If you need the CAS value you can use mget.
 */
JS_METHOD(_get) {
  MEMCACHED_PTR;

  if (args.Length() != 1 ||
      !args[0]->IsString()) {
    JS_TYPE_ERROR("Invalid arguments. Use get(key{String})");
    return;
  }

  v8::String::Utf8Value key(args[0]);
  size_t rlength;
  uint32_t rflags;

  memcached_return rc;
  char *rvalue = memcached_get(memc, *key, key.length(), &rlength, &rflags, &rc);
  if (rc == MEMCACHED_NOTFOUND) {
    args.GetReturnValue().SetUndefined();
    return;
  } else if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  v8::HandleScope handle_scope(JS_ISOLATE);
  v8::Handle<v8::Array> js_array = v8::Array::New(JS_ISOLATE, 2);
  js_array->Set(JS_INT(0), JS_STR_LEN(rvalue, rlength));
  js_array->Set(JS_INT(1), JS_INT(rflags));

  free(rvalue);

  args.GetReturnValue().Set(js_array);
}

/**
 * Check and set operation. Like set, but will only update the value, flags, and
 * expiration if the CAS value passed in matches that which is still associated
 * with the key. This can be used to ensure that no other clients have modified
 * a value since you read it with mget.
 */
JS_METHOD(_cas) {
  MEMCACHED_PTR;

  if (args.Length() != 5 ||
      !args[0]->IsString() ||
      !args[1]->IsString() ||
      !args[2]->IsInt32() ||
      !args[3]->IsInt32() ||
      !args[4]->IsArray()) {
    JS_MEMCACHED_CAS_ERROR;
    return;
  }

  v8::String::Utf8Value key(args[0]);
  v8::String::Utf8Value value(args[1]);
  uint32_t expiration = args[2]->Uint32Value();
  uint32_t flags = args[3]->Uint32Value();
  v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[4]);
  if (arr->Length() != 2) {
    JS_MEMCACHED_CAS_ERROR;
    return;
  }
  v8::Local<v8::Value> arr0 = arr->Get(JS_INT(0));
  v8::Local<v8::Value> arr1 = arr->Get(JS_INT(1));
  if (!arr0->IsInt32() ||
      !arr1->IsInt32()) {
    JS_MEMCACHED_CAS_ERROR;
    return;
  }
  uint64_t cas =
      (((uint64_t)arr0->Uint32Value()) << 32) + ((uint64_t)arr1->Uint32Value());

  memcached_return_t rc = memcached_cas(
      memc, *key, key.length(), *value, value.length(), expiration, flags, cas);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

/**
 * Fetches multiple keys at once by key. Returns an array of arrays where each
 * nested array is a [key, value, flags, cas] tuple. If a given key was found
 * then there will be a tuple for it, otherwise no tuple will exist for the key.
 */
JS_METHOD(_mget) {
  MEMCACHED_PTR;

  if (args.Length() != 1 ||
      !args[0]->IsArray()) {
    JS_TYPE_ERROR("Invalid arguments. Use mget(keys{Array<String>})");
    return;
  }

  v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
  uint32_t key_count = arr->Length();
  char* keys[key_count];
  size_t key_lengths[key_count];
  for (unsigned int i = 0; i < key_count; i++) {
    v8::Local<v8::Value> value = arr->Get(JS_INT(i));
    if (!value->IsString()) {
      JS_TYPE_ERROR("Invalid arguments. All keys must be Strings.");
      return;
    }
    // Copying the strings was the only way I could figure out how to get
    // an array of string pointers for the memcached_mget call. There may be
    // a more efficient way of doing this that does not require new memory
    // allocation.
    v8::Local<v8::String> string = value->ToString();
    keys[i] = new char[string->Utf8Length()];
    string->WriteUtf8(keys[i], string->Utf8Length());
    key_lengths[i] = (size_t)string->Utf8Length();
  }

  memcached_return_t rc;
  rc = memcached_mget(memc, keys, key_lengths, key_count);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  for (unsigned int i = 0; i < key_count; i++) {
    delete[] keys[i];
  }

  uint32_t flags;
  uint64_t cas;
  const char *return_key;
  size_t return_key_length;
  const char *return_value;
  size_t return_value_length;

  memcached_result_st results;

  // Prepare result structure.
  memcached_result_create(memc, &results);

  // In binary mode, libmemcached adds the prefix to each key returned so
  // we strip it if necessary to make binary and text mode more similar.
  size_t prefix_key_offset = 0;
  if (memcached_behavior_get(memc, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL) == 1) {
    char *prefix_key = (char *)memcached_callback_get(
        memc, MEMCACHED_CALLBACK_PREFIX_KEY, &rc);
    if (rc == MEMCACHED_SUCCESS) {
      prefix_key_offset = strlen(prefix_key);
    }
  }

  v8::HandleScope handle_scope(JS_ISOLATE);
  v8::Handle<v8::Array> js_array = v8::Array::New(JS_ISOLATE);

  // It is more efficient to use memcached_fetch_result than memcached_fetch
  // because you can re-use the memory between invocations according to the
  // libmemcached docs. It is also the only way to get the CAS value of the
  // result.
  unsigned int i = 0;
  while ((memcached_fetch_result(memc, &results, &rc)) != NULL) {
    if (rc != MEMCACHED_SUCCESS) {
      JS_ERROR(memcached_strerror(memc, rc));
      return;
    }
    return_key = memcached_result_key_value(&results) + prefix_key_offset;
    return_key_length = memcached_result_key_length(&results) - prefix_key_offset;
    return_value = memcached_result_value(&results);
    return_value_length = memcached_result_length(&results);
    flags = memcached_result_flags(&results);
    cas = memcached_result_cas(&results);

    v8::Handle<v8::Array> js_return_value = v8::Array::New(JS_ISOLATE, 4);

    // Encode 64bit CAS value into two 32bit integers so they do not
    // exceed the 52bit integer range of Javascript integers.
    v8::Handle<v8::Array> js_cas = v8::Array::New(JS_ISOLATE, 2);
    js_cas->Set(JS_INT(0), JS_INT(cas >> 32));
    js_cas->Set(JS_INT(1), JS_INT(cas & 0xFFFFFFFF));

    js_return_value->Set(JS_INT(0), JS_STR_LEN(return_key, return_key_length));
    js_return_value->Set(JS_INT(1), JS_STR_LEN(return_value, return_value_length));
    js_return_value->Set(JS_INT(2), JS_INT(flags));
    js_return_value->Set(JS_INT(3), js_cas);
    js_array->Set(JS_INT(i), js_return_value);
    i++;
  }
  // According to examples in the memcached tests, and my interpretation of
  // the documentation - it is only necessary to free the memcached results
  // after you are done using, and not on each iteratation of
  // memcached_fetch_result. This implies that memcached is re-using the memory
  // allocated to the string value and freeing it at the end.
  memcached_result_free(&results);

  // Does this ensure that all the members of the array are also 'Close'd to the
  // parent handle_scope? It seems to based on similar usage in list_items of
  // fs.cc
  args.GetReturnValue().Set(js_array);
}

JS_METHOD(_behaviorSet) {
  MEMCACHED_PTR;

  if (args.Length() != 2 ||
      !args[0]->IsInt32() ||
      !args[1]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use behaviorSet(behavior{Int}, data{Int}).");
    return;
  }

  memcached_behavior_t behavior = (memcached_behavior_t)args[0]->Uint32Value();
  uint32_t data = args[1]->Uint32Value();

  memcached_return_t rc = memcached_behavior_set(memc, behavior, data);
  if (rc != MEMCACHED_SUCCESS) {
    JS_ERROR(memcached_strerror(memc, rc));
    return;
  }

  args.GetReturnValue().Set(args.This());
}

JS_METHOD(_behaviorGet) {
  MEMCACHED_PTR;

  if (args.Length() != 1 ||
      !args[0]->IsInt32()) {
    JS_TYPE_ERROR("Invalid arguments. Use behaviorGet(behavior{Int})");
    return;
  }

  memcached_behavior_t behavior = (memcached_behavior_t)args[0]->Uint32Value();

  uint64_t data = memcached_behavior_get(memc, behavior);
  args.GetReturnValue().Set(JS_INT(data));
}

} /* end namespace */

SHARED_INIT() {
  v8::HandleScope handle_scope(JS_ISOLATE);
  v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(JS_ISOLATE, _memcached);
  ft->SetClassName(JS_STR("Memcached"));

  v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(1); /* connection */

  v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();

  /**
   * Memcached prototype methods (new Memcached().*)
   */
  pt->Set(JS_STR("reset"), v8::FunctionTemplate::New(JS_ISOLATE, _reset));
  pt->Set(JS_STR("getPrefixKey"), v8::FunctionTemplate::New(JS_ISOLATE, _getPrefixKey));
  pt->Set(JS_STR("setPrefixKey"), v8::FunctionTemplate::New(JS_ISOLATE, _setPrefixKey));
  pt->Set(JS_STR("clearPrefixKey"), v8::FunctionTemplate::New(JS_ISOLATE, _clearPrefixKey));
  pt->Set(JS_STR("addServerWithWeight"), v8::FunctionTemplate::New(JS_ISOLATE, _addServerWithWeight));
  pt->Set(JS_STR("flush"), v8::FunctionTemplate::New(JS_ISOLATE, _flush));
  pt->Set(JS_STR("set"), v8::FunctionTemplate::New(JS_ISOLATE, _set));
  pt->Set(JS_STR("replace"), v8::FunctionTemplate::New(JS_ISOLATE, _replace));
  pt->Set(JS_STR("add"), v8::FunctionTemplate::New(JS_ISOLATE, _add));
  pt->Set(JS_STR("remove"), v8::FunctionTemplate::New(JS_ISOLATE, _remove));
  pt->Set(JS_STR("get"), v8::FunctionTemplate::New(JS_ISOLATE, _get));
  pt->Set(JS_STR("cas"), v8::FunctionTemplate::New(JS_ISOLATE, _cas));
  pt->Set(JS_STR("mget"), v8::FunctionTemplate::New(JS_ISOLATE, _mget));
  pt->Set(JS_STR("behaviorSet"), v8::FunctionTemplate::New(JS_ISOLATE, _behaviorSet));
  pt->Set(JS_STR("behaviorGet"), v8::FunctionTemplate::New(JS_ISOLATE, _behaviorGet));

  /**
   * Memcached behavior values. These are copied from the
   * memcached_behavior_t enum in constants.h of libmemcached.
   */
  ft->Set(JS_STR("BEHAVIOR_NO_BLOCK"), JS_INT(MEMCACHED_BEHAVIOR_NO_BLOCK));
  ft->Set(JS_STR("BEHAVIOR_TCP_NODELAY"), JS_INT(MEMCACHED_BEHAVIOR_TCP_NODELAY));
  ft->Set(JS_STR("BEHAVIOR_HASH"), JS_INT(MEMCACHED_BEHAVIOR_HASH));
  ft->Set(JS_STR("BEHAVIOR_KETAMA"), JS_INT(MEMCACHED_BEHAVIOR_KETAMA));
  ft->Set(JS_STR("BEHAVIOR_SOCKET_SEND_SIZE"), JS_INT(MEMCACHED_BEHAVIOR_SOCKET_SEND_SIZE));
  ft->Set(JS_STR("BEHAVIOR_SOCKET_RECV_SIZE"), JS_INT(MEMCACHED_BEHAVIOR_SOCKET_RECV_SIZE));
  ft->Set(JS_STR("BEHAVIOR_CACHE_LOOKUPS"), JS_INT(MEMCACHED_BEHAVIOR_CACHE_LOOKUPS));
  ft->Set(JS_STR("BEHAVIOR_SUPPORT_CAS"), JS_INT(MEMCACHED_BEHAVIOR_SUPPORT_CAS));
  ft->Set(JS_STR("BEHAVIOR_POLL_TIMEOUT"), JS_INT(MEMCACHED_BEHAVIOR_POLL_TIMEOUT));
  ft->Set(JS_STR("BEHAVIOR_DISTRIBUTION"), JS_INT(MEMCACHED_BEHAVIOR_DISTRIBUTION));
  ft->Set(JS_STR("BEHAVIOR_BUFFER_REQUESTS"), JS_INT(MEMCACHED_BEHAVIOR_BUFFER_REQUESTS));
  ft->Set(JS_STR("BEHAVIOR_USER_DATA"), JS_INT(MEMCACHED_BEHAVIOR_USER_DATA));
  ft->Set(JS_STR("BEHAVIOR_SORT_HOSTS"), JS_INT(MEMCACHED_BEHAVIOR_SORT_HOSTS));
  ft->Set(JS_STR("BEHAVIOR_VERIFY_KEY"), JS_INT(MEMCACHED_BEHAVIOR_VERIFY_KEY));
  ft->Set(JS_STR("BEHAVIOR_CONNECT_TIMEOUT"), JS_INT(MEMCACHED_BEHAVIOR_CONNECT_TIMEOUT));
  ft->Set(JS_STR("BEHAVIOR_RETRY_TIMEOUT"), JS_INT(MEMCACHED_BEHAVIOR_RETRY_TIMEOUT));
  ft->Set(JS_STR("BEHAVIOR_KETAMA_WEIGHTED"), JS_INT(MEMCACHED_BEHAVIOR_KETAMA_WEIGHTED));
  ft->Set(JS_STR("BEHAVIOR_KETAMA_HASH"), JS_INT(MEMCACHED_BEHAVIOR_KETAMA_HASH));
  ft->Set(JS_STR("BEHAVIOR_BINARY_PROTOCOL"), JS_INT(MEMCACHED_BEHAVIOR_BINARY_PROTOCOL));
  ft->Set(JS_STR("BEHAVIOR_SND_TIMEOUT"), JS_INT(MEMCACHED_BEHAVIOR_SND_TIMEOUT));
  ft->Set(JS_STR("BEHAVIOR_RCV_TIMEOUT"), JS_INT(MEMCACHED_BEHAVIOR_RCV_TIMEOUT));
  ft->Set(JS_STR("BEHAVIOR_SERVER_FAILURE_LIMIT"), JS_INT(MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT));
  ft->Set(JS_STR("BEHAVIOR_IO_MSG_WATERMARK"), JS_INT(MEMCACHED_BEHAVIOR_IO_MSG_WATERMARK));
  ft->Set(JS_STR("BEHAVIOR_IO_BYTES_WATERMARK"), JS_INT(MEMCACHED_BEHAVIOR_IO_BYTES_WATERMARK));
  ft->Set(JS_STR("BEHAVIOR_IO_KEY_PREFETCH"), JS_INT(MEMCACHED_BEHAVIOR_IO_KEY_PREFETCH));
  ft->Set(JS_STR("BEHAVIOR_HASH_WITH_PREFIX_KEY"), JS_INT(MEMCACHED_BEHAVIOR_HASH_WITH_PREFIX_KEY));
  ft->Set(JS_STR("BEHAVIOR_NOREPLY"), JS_INT(MEMCACHED_BEHAVIOR_NOREPLY));
  ft->Set(JS_STR("BEHAVIOR_USE_UDP"), JS_INT(MEMCACHED_BEHAVIOR_USE_UDP));
  ft->Set(JS_STR("BEHAVIOR_AUTO_EJECT_HOSTS"), JS_INT(MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS));
  ft->Set(JS_STR("BEHAVIOR_NUMBER_OF_REPLICAS"), JS_INT(MEMCACHED_BEHAVIOR_NUMBER_OF_REPLICAS));
  ft->Set(JS_STR("BEHAVIOR_RANDOMIZE_REPLICA_READ"), JS_INT(MEMCACHED_BEHAVIOR_RANDOMIZE_REPLICA_READ));
  ft->Set(JS_STR("BEHAVIOR_CORK"), JS_INT(MEMCACHED_BEHAVIOR_CORK));
  ft->Set(JS_STR("BEHAVIOR_TCP_KEEPALIVE"), JS_INT(MEMCACHED_BEHAVIOR_TCP_KEEPALIVE));
  ft->Set(JS_STR("BEHAVIOR_TCP_KEEPIDLE"), JS_INT(MEMCACHED_BEHAVIOR_TCP_KEEPIDLE));
  ft->Set(JS_STR("BEHAVIOR_MAX"), JS_INT(MEMCACHED_BEHAVIOR_MAX));

  exports->Set(JS_STR("Memcached"), ft->GetFunction());
}
