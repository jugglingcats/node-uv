#include <node.h>
#include <uv.h>

using namespace v8;

static void Runner(uv_work_t *req)
{
	printf("Async work running!\n");
}

static void RunDone(uv_work_t *req, int status)
{
	delete req;
	printf("Async work done!\n");
}

int n = 1;

static void Runner2(uv_async_t* handle) {
	printf("Got async send! %d\n", n++);
	
	v8::Isolate *isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	v8::Persistent<v8::Function> *func = (v8::Persistent<v8::Function> *) handle->data;
	func->Get(isolate)->Call(isolate->GetCurrentContext()->Global(), 0, NULL);

	delete func;
	uv_close((uv_handle_t *)handle, NULL);
}

void Start(const FunctionCallbackInfo<Value>& args)
{
	printf("In run async\n");

	printf("Size of uv_async_t: %zd\n", sizeof(uv_async_t));
	printf("Size of void *: %zd\n", sizeof(void *));

	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	uv_work_t *req = (uv_work_t*)malloc(sizeof(uv_work_t));

	/// Example using uv_queue_work (working fine)
	printf("Queue work\n");
	uv_queue_work(uv_default_loop(), req, &Runner, &RunDone);

	uv_async_t *handle = (uv_async_t*)malloc(sizeof(uv_async_t));
	uv_async_init(uv_default_loop(), handle, &Runner2);

	v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[0]);
	auto savedFunc = new v8::Persistent<v8::Function>();
	savedFunc->Reset(isolate, func);
	handle->data = savedFunc;

	//printf("Async send\n");
	uv_async_send(handle);
}

void Init(Handle<Object> exports, Handle<Object> module)
{
	NODE_SET_METHOD(exports, "start", Start);
}

NODE_MODULE(node_uv, Init)
