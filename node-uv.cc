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

    static void Runner2(uv_async_t* handle) {
        printf("Got async send!\n");
    }

    void Start(const FunctionCallbackInfo<Value>& args)
    {
        printf("In run async\n");

        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);

        uv_work_t *req = (uv_work_t*)malloc(sizeof(uv_work_t));

        /// Example using uv_queue_work (working fine)
        printf("Queue work\n");
        uv_queue_work(uv_default_loop(), req, &Runner, &RunDone);

        uv_async_t *handle = (uv_async_t*)malloc(sizeof(uv_async_t));
        uv_async_init(uv_default_loop(), handle, &Runner2);

        /// Example using uv_async_send (node does not terminate)
        printf("Async send\n");
        uv_async_send(handle);
    }

    void Init(Handle<Object> exports, Handle<Object> module)
    {
        NODE_SET_METHOD(exports, "start", Start);
    }

    NODE_MODULE(node_uv, Init)